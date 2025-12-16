#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "callbacks3.h"
#include "callbacks2.h"
#include "callbacks1.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "evenement.h"
#include "centre.h"
#include "display.h"

// Global variables
int selected_capacite = 20;
int selected_capacite_mod = 20;
static char current_membre_id[20] = "";

/******************* EVENT MANAGEMENT CALLBACKS *******************/

void on_Gestion_des_evenements_show(GtkWidget *widget, gpointer user_data) {
    g_print("=== Window show event triggered ===\n");
    
    GtkWidget *treeview = lookup_widget(widget, "treeview_afficher_evenement");
    GtkWidget *combo_centre = lookup_widget(widget, "comboboxentry_centre_event");
    GtkWidget *combo_centre_mod = lookup_widget(widget, "comboboxentry_centre_mod");
    GtkWidget *combo_type = lookup_widget(widget, "comboboxentry_type_event");
    GtkWidget *combo_type_mod = lookup_widget(widget, "comboboxentry3");

    if (!treeview) {
        g_warning("TreeView not found!\n");
        return;
    }
    
    g_print("TreeView widget found: %p\n", treeview);

    // Populate centre comboboxes
    if (combo_centre) populate_centre_combobox(combo_centre);
    if (combo_centre_mod) populate_centre_combobox(combo_centre_mod);

    // Populate type comboboxes
    if (combo_type) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type), "Competition");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type), "Stage");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type), "Formation");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type), "Tournoi");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type), "Conference");
    }
    
    if (combo_type_mod) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type_mod), "Competition");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type_mod), "Stage");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type_mod), "Formation");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type_mod), "Tournoi");
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_type_mod), "Conference");
    }

    // Display all events
    g_print("Calling afficher_evenements...\n");
    afficher_evenements(treeview);
    g_print("=== End of show event ===\n");
}

void on_treeview_afficher_evenement_cursor_changed(GtkTreeView *treeview, gpointer user_data) {
    // Event selection feedback
}

void on_button_chercher_evenement_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry = lookup_widget(window, "entry_chercher_evenement");
    GtkWidget *treeview = lookup_widget(window, "treeview_afficher_evenement");

    const char *search_text = gtk_entry_get_text(GTK_ENTRY(entry));

    if (strlen(search_text) == 0) {
        afficher_evenements(treeview);
        return;
    }

    Evenement resultats[100];
    int count = 0;

    rechercher_evenement_multi_criteres(
        NULL, 0,
        NULL, 0,
        NULL, 0,
        0, 0, 0, 0,
        search_text,
        resultats, &count);

    afficher_resultats_recherche(treeview, resultats, count);

    if (count == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Aucun événement trouvé.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_button_supprimer_event_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *treeview = lookup_widget(window, "treeview_afficher_evenement");
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id_str;
        gtk_tree_model_get(model, &iter, 0, &id_str, -1);

        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Êtes-vous sûr de vouloir supprimer l'événement %s ?", id_str);

        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            if (supprimer_evenement(id_str)) {
                GtkWidget *success = gtk_message_dialog_new(GTK_WINDOW(window),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Événement supprimé avec succès !");
                gtk_dialog_run(GTK_DIALOG(success));
                gtk_widget_destroy(success);
                
                afficher_evenements(treeview);
            } else {
                GtkWidget *error = gtk_message_dialog_new(GTK_WINDOW(window),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_ERROR,
                    GTK_BUTTONS_OK,
                    "Erreur lors de la suppression !");
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
        }
        g_free(id_str);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un événement à supprimer.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_radiobutton_cap_20_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_capacite = 20;
    }
}

void on_radiobutton_cap_40_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_capacite = 40;
    }
}

void on_radiobutton_cap_50_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_capacite = 50;
    }
}

void on_button_ajouter_event_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    GtkWidget *entry_nom = lookup_widget(window, "entry_nom_event");
    GtkWidget *entry_desc = lookup_widget(window, "entry_descrp_event");
    GtkWidget *combo_type = lookup_widget(window, "comboboxentry_type_event");
    GtkWidget *calendar = lookup_widget(window, "calendar_date_event");
    GtkWidget *spin_debut = lookup_widget(window, "spinbutton_heure_debut");
    GtkWidget *spin_fin = lookup_widget(window, "spinbutton_heure_fin");
    GtkWidget *combo_centre = lookup_widget(window, "comboboxentry_centre_event");
    GtkWidget *entry_salle = lookup_widget(window, "entry_salle_event");
    GtkWidget *entry_coach = lookup_widget(window, "entry_nom_coach_event");
    GtkWidget *entry_prix = lookup_widget(window, "entry_prix_event");

    const char *nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    const char *desc = gtk_entry_get_text(GTK_ENTRY(entry_desc));
    const char *type = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_type));
    const char *centre_nom = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre));
    const char *salle = gtk_entry_get_text(GTK_ENTRY(entry_salle));
    const char *coach = gtk_entry_get_text(GTK_ENTRY(entry_coach));
    const char *prix_str = gtk_entry_get_text(GTK_ENTRY(entry_prix));

    if (!nom || strlen(nom) == 0 || !type || !centre_nom || !prix_str) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez remplir tous les champs obligatoires !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    Evenement e;
    strcpy(e.nom, nom);
    strcpy(e.description, desc ? desc : "");
    strcpy(e.type, type);
    strcpy(e.salle, salle && strlen(salle) > 0 ? salle : "N/A");
    strcpy(e.entraineur_nom, coach && strlen(coach) > 0 ? coach : "N/A");
    
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    e.date.jour = day;
    e.date.mois = month + 1;
    e.date.annee = year;

    int heure_debut = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_debut));
    int heure_fin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_fin));
    sprintf(e.heure_debut, "%02d:00", heure_debut);
    sprintf(e.heure_fin, "%02d:00", heure_fin);

    e.id_centre = get_centre_id_by_name(centre_nom);
    e.capacite_max = selected_capacite;
    e.nb_inscrits = 0;
    e.prix = atof(prix_str);

    if (ajouter_evenement(e)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Événement ajouté avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Clear fields
        gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
        gtk_entry_set_text(GTK_ENTRY(entry_desc), "");
        gtk_entry_set_text(GTK_ENTRY(entry_salle), "");
        gtk_entry_set_text(GTK_ENTRY(entry_coach), "");
        gtk_entry_set_text(GTK_ENTRY(entry_prix), "");

        // Refresh treeview
        GtkWidget *treeview = lookup_widget(window, "treeview_afficher_evenement");
        afficher_evenements(treeview);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur lors de l'ajout !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_button_consulter_evenement_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_id = lookup_widget(window, "entry_id_event_mod");
    
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    if (!id || strlen(id) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer un ID !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    Evenement e = chercher_evenement(id);
    
    if (strlen(e.id) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Événement non trouvé !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Fill modification fields
    GtkWidget *entry_nom = lookup_widget(window, "entry_nom_modif_event");
    GtkWidget *entry_desc = lookup_widget(window, "entry_desc_modif_event");
    GtkWidget *combo_type = lookup_widget(window, "comboboxentry3");
    GtkWidget *calendar = lookup_widget(window, "calendar_modif_event");
    GtkWidget *spin_debut = lookup_widget(window, "spinbutton_modif_event_debut_heure");
    GtkWidget *spin_fin = lookup_widget(window, "spinbutton_modif_event_fin_heure");
    GtkWidget *combo_centre = lookup_widget(window, "comboboxentry_centre_mod");
    GtkWidget *entry_salle = lookup_widget(window, "entry_salle_modif");
    GtkWidget *entry_coach = lookup_widget(window, "entry_nom_coach_modif");
    GtkWidget *entry_prix = lookup_widget(window, "entry_mod_prix_event");

    gtk_entry_set_text(GTK_ENTRY(entry_nom), e.nom);
    gtk_entry_set_text(GTK_ENTRY(entry_desc), e.description);
    gtk_entry_set_text(GTK_ENTRY(entry_salle), e.salle);
    gtk_entry_set_text(GTK_ENTRY(entry_coach), e.entraineur_nom);
    
    // Set combo type
    int type_index = 0;
    if (strcmp(e.type, "Stage") == 0) type_index = 1;
    else if (strcmp(e.type, "Formation") == 0) type_index = 2;
    else if (strcmp(e.type, "Tournoi") == 0) type_index = 3;
    else if (strcmp(e.type, "Conference") == 0) type_index = 4;
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), type_index);

    gtk_calendar_select_month(GTK_CALENDAR(calendar), e.date.mois - 1, e.date.annee);
    gtk_calendar_select_day(GTK_CALENDAR(calendar), e.date.jour);

    int h_debut = atoi(e.heure_debut);
    int h_fin = atoi(e.heure_fin);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_debut), h_debut);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_fin), h_fin);

    // Set centre
    char *centre_nom = get_centre_name_by_id(e.id_centre);
    gtk_entry_set_text(GTK_ENTRY(GTK_BIN(combo_centre)->child), centre_nom);

    char prix_str[20];
    sprintf(prix_str, "%.2f", e.prix);
    gtk_entry_set_text(GTK_ENTRY(entry_prix), prix_str);

    // Set capacity radiobuttons
    GtkWidget *radio20 = lookup_widget(window, "radiobutton_cap_max_mod_20");
    GtkWidget *radio40 = lookup_widget(window, "radiobutton_cap_max_mod_40");
    GtkWidget *radio50 = lookup_widget(window, "radiobutton_cap_max_mod_50");
    
    if (e.capacite_max == 20) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio20), TRUE);
        selected_capacite_mod = 20;
    } else if (e.capacite_max == 40) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio40), TRUE);
        selected_capacite_mod = 40;
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio50), TRUE);
        selected_capacite_mod = 50;
    }

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Événement chargé avec succès !");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_button_modifier_event_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    GtkWidget *entry_id = lookup_widget(window, "entry_id_event_mod");
    GtkWidget *entry_nom = lookup_widget(window, "entry_nom_modif_event");
    GtkWidget *entry_desc = lookup_widget(window, "entry_desc_modif_event");
    GtkWidget *combo_type = lookup_widget(window, "comboboxentry3");
    GtkWidget *calendar = lookup_widget(window, "calendar_modif_event");
    GtkWidget *spin_debut = lookup_widget(window, "spinbutton_modif_event_debut_heure");
    GtkWidget *spin_fin = lookup_widget(window, "spinbutton_modif_event_fin_heure");
    GtkWidget *combo_centre = lookup_widget(window, "comboboxentry_centre_mod");
    GtkWidget *entry_salle = lookup_widget(window, "entry_salle_modif");
    GtkWidget *entry_coach = lookup_widget(window, "entry_nom_coach_modif");
    GtkWidget *entry_prix = lookup_widget(window, "entry_mod_prix_event");

    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    const char *desc = gtk_entry_get_text(GTK_ENTRY(entry_desc));
    const char *type = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_type));
    const char *centre_nom = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre));
    const char *salle = gtk_entry_get_text(GTK_ENTRY(entry_salle));
    const char *coach = gtk_entry_get_text(GTK_ENTRY(entry_coach));
    const char *prix_str = gtk_entry_get_text(GTK_ENTRY(entry_prix));

    if (!id || strlen(id) == 0 || !nom || strlen(nom) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez remplir tous les champs !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    Evenement e;
    strcpy(e.nom, nom);
    strcpy(e.description, desc ? desc : "");
    strcpy(e.type, type);
    strcpy(e.salle, salle && strlen(salle) > 0 ? salle : "N/A");
    strcpy(e.entraineur_nom, coach && strlen(coach) > 0 ? coach : "N/A");
    
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    e.date.jour = day;
    e.date.mois = month + 1;
    e.date.annee = year;

    int heure_debut = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_debut));
    int heure_fin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_fin));
    sprintf(e.heure_debut, "%02d:00", heure_debut);
    sprintf(e.heure_fin, "%02d:00", heure_fin);

    e.id_centre = get_centre_id_by_name(centre_nom);
    e.capacite_max = selected_capacite_mod;
    
    Evenement old_e = chercher_evenement(id);
    e.nb_inscrits = old_e.nb_inscrits;
    
    e.prix = atof(prix_str);

    if (modifier_evenement(id, e)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Événement modifié avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Refresh treeview
        GtkWidget *treeview = lookup_widget(window, "treeview_afficher_evenement");
        afficher_evenements(treeview);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur lors de la modification !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_radiobutton_cap_max_mod_20_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_capacite_mod = 20;
    }
}

void on_radiobutton_cap_max_mod_40_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_capacite_mod = 40;
    }
}

void on_radiobutton_cap_max_mod_50_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) { 
        selected_capacite_mod = 50;
    }
}

/******************* MEMBER INSCRIPTION CALLBACKS *******************/

void on_inscription_membre_show(GtkWidget *widget, gpointer user_data) {
    g_print("=== Inscription membre window show event triggered ===\n");
    
    GtkWidget *treeview = lookup_widget(widget, "treeview_event_inscription");
    GtkWidget *entry_id = lookup_widget(widget, "entry_id_membre_event");
    
    if (!treeview) {
        g_warning("TreeView not found!\n");
        return;
    }
    
    g_print("TreeView widget found: %p\n", treeview);
    
    // Clear the entry field
    if (entry_id) {
        gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    }
    
    // Clear current member ID
    strcpy(current_membre_id, "");
    
    // Display empty treeview initially
    afficher_evenements_disponibles(treeview, "");
    
    g_print("=== End of inscription membre show event ===\n");
}

void on_treeview_event_inscription_cursor_changed(GtkTreeView *treeview, gpointer user_data) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *event_id, *event_name;
        gtk_tree_model_get(model, &iter, 0, &event_id, 1, &event_name, -1);
        
        g_print("Event selected: ID=%s, Name=%s\n", event_id, event_name);
        
        g_free(event_id);
        g_free(event_name);
    }
}

void on_button_inscription_event_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_id = lookup_widget(window, "entry_id_membre_event");
    GtkWidget *treeview = lookup_widget(window, "treeview_event_inscription");
    
    const char *id_membre = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    if (!id_membre || strlen(id_membre) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer votre ID membre !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un événement !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    gchar *event_id, *event_name;
    gtk_tree_model_get(model, &iter, 0, &event_id, 1, &event_name, -1);
    
    GtkWidget *confirm = gtk_message_dialog_new(GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vous inscrire à l'événement '%s' ?", event_name);
    
    gint response = gtk_dialog_run(GTK_DIALOG(confirm));
    gtk_widget_destroy(confirm);
    
    if (response == GTK_RESPONSE_YES) {
        if (inscrire_membre_evenement(id_membre, event_id)) {
            GtkWidget *success = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "Inscription réussie à l'événement '%s' !", event_name);
            gtk_dialog_run(GTK_DIALOG(success));
            gtk_widget_destroy(success);
            
            strcpy(current_membre_id, id_membre);
            afficher_evenements_disponibles(treeview, id_membre);
        } else {
            GtkWidget *error = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Erreur lors de l'inscription !\n"
                "L'événement est peut-être complet ou vous êtes déjà inscrit.");
            gtk_dialog_run(GTK_DIALOG(error));
            gtk_widget_destroy(error);
        }
    }
    
    g_free(event_id);
    g_free(event_name);
}

void on_button_voir_mes_evenement_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_id = lookup_widget(window, "entry_id_membre_event");
    GtkWidget *treeview = lookup_widget(window, "treeview_event_inscription");
    
    const char *id_membre = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    if (!id_membre || strlen(id_membre) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer votre ID membre !");
        gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
        return;
    }
    
    // Store current member ID
    strcpy(current_membre_id, id_membre);
    
    // Display member's inscribed events
    afficher_evenements_membre(treeview, id_membre);
    
    GtkWidget *info = gtk_message_dialog_new(GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Affichage de vos événements inscrits.");
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(info);
}

// Optional: Button to unsubscribe from events
void on_button_desinscription_event_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_id = lookup_widget(window, "entry_id_membre_event");
    GtkWidget *treeview = lookup_widget(window, "treeview_event_inscription");
    
    const char *id_membre = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    if (!id_membre || strlen(id_membre) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer votre ID membre !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un événement !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    gchar *event_id, *event_name;
    gtk_tree_model_get(model, &iter, 0, &event_id, 1, &event_name, -1);
    
    GtkWidget *confirm = gtk_message_dialog_new(GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vous désinscrire de l'événement '%s' ?", event_name);
    
    gint response = gtk_dialog_run(GTK_DIALOG(confirm));
    gtk_widget_destroy(confirm);
    
    if (response == GTK_RESPONSE_YES) {
        if (desinscrire_membre_evenement(id_membre, event_id)) {
            GtkWidget *success = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "Désinscription réussie de l'événement '%s' !", event_name);
            gtk_dialog_run(GTK_DIALOG(success));
            gtk_widget_destroy(success);
            
            // Refresh the view to show member's events
            afficher_evenements_membre(treeview, id_membre);
        } else {
            GtkWidget *error = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Erreur lors de la désinscription !");
            gtk_dialog_run(GTK_DIALOG(error));
            gtk_widget_destroy(error);
        }
    }
    
    g_free(event_id);
    g_free(event_name);
}

// Optional: Button to refresh and show available events
void on_button_actualiser_evenements_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_id = lookup_widget(window, "entry_id_membre_event");
    GtkWidget *treeview = lookup_widget(window, "treeview_event_inscription");
    
    const char *id_membre = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    if (!id_membre || strlen(id_membre) == 0) {
        // Show all available events if no member ID
        afficher_evenements_disponibles(treeview, "");
    } else {
        // Show available events for this member
        strcpy(current_membre_id, id_membre);
        afficher_evenements_disponibles(treeview, id_membre);
    }
    
    GtkWidget *info = gtk_message_dialog_new(GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Liste des événements disponibles actualisée.");
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(info);
}

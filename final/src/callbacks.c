#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.h"
#include "user.h"
#include "display.h"

 GtkWidget *window1;
 GtkWidget *window2;
 GtkWidget *window3;
 GtkWidget *window4;
 GtkWidget *window5;
 GtkWidget *window6;
 GtkWidget *window7;
 GtkWidget *window8;
 GtkWidget *window9;
 GtkWidget *window10;
 GtkWidget *window11;
 GtkWidget *window12;

/*void remplir_combo_centres(GtkComboBoxText *combo, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) return;

    Centre c;
    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        gtk_combo_box_text_append_text(combo, c.nom);
    }

    fclose(f);

    // Sélection du premier élément par défaut
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
}
*/


void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id, *entry_nom, *entry_adresse, *entry_tel, *entry_email, *label_msg;
    Centre c;
    char id_text[20];

    entry_id = lookup_widget(button, "entry_id_centre");
    entry_nom = lookup_widget(button, "entry_nom_centre");
    entry_adresse = lookup_widget(button, "entry_adresse_centre");
    entry_tel = lookup_widget(button, "entry_tel");
    entry_email = lookup_widget(button, "entry_email");
    label_msg = lookup_widget(button, "label_message_ajouter");

    strcpy(id_text, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    for (int i = 0; id_text[i] != '\0'; i++) {
        if (!isdigit(id_text[i])) {
            gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ L'ID doit être un nombre !");
            return;
        }
    }
    c.id = atoi(id_text);

    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(entry_adresse)));

    if(strlen(c.nom) == 0 || strlen(c.adresse) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Tous les champs sont obligatoires !");
        return;
    }

    char tel[10];
    strcpy(tel, gtk_entry_get_text(GTK_ENTRY(entry_tel)));
    if(strlen(tel) != 8) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Le numéro de téléphone doit contenir 8 chiffres !");
        return;
    }
    for(int i = 0; i < 8; i++) {
        if(!isdigit(tel[i])) {
            gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Le numéro de téléphone doit être numérique !");
            return;
        }
    }
    strcpy(c.telephone, tel);

   
    char email[100];
    strcpy(email, gtk_entry_get_text(GTK_ENTRY(entry_email)));
    if(strchr(email, '@') == NULL) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ L'adresse e-mail n'est pas valide !");
        return;
    }
    strcpy(c.email, email);

 
    c.nb_salles = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(button, "spin_nbr")));
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(button, "spin_capacite")));

   
    char *type_selected = gtk_combo_box_get_active_text(GTK_COMBO_BOX(lookup_widget(button, "combo_type")));
    if(type_selected == NULL) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Veuillez sélectionner un type !");
        return;
    }
    strcpy(c.type, type_selected);

   
    int result = ajouter_centre("centres.txt", c);

    
    if(result == 1) {
        gtk_label_set_text(GTK_LABEL(label_msg), "✅ Centre ajouté avec succès !");
        gtk_entry_set_text(GTK_ENTRY(entry_id), "");
        gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
        gtk_entry_set_text(GTK_ENTRY(entry_adresse), "");
        gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
        gtk_entry_set_text(GTK_ENTRY(entry_email), "");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(button, "spin_nbr")), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(button, "spin_capacite")), 0);
        gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(button, "combo_type")), -1);

	GtkWidget *tv = lookup_widget(gtk_widget_get_toplevel(GTK_WIDGET(button)),"treeview_centre");
        afficher_centres(tv);
    }
    else if (result == 2) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Cet ID est déjà pris !");
    }
    else if (result == 3){
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Tous les champs sont obligatoires !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Erreur lors de l’ajout !");
    }


}


void
on_btn_retour_ajouter_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window1);
    gtk_widget_show(window8);
}


void
on_btn_retour_supprimer_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window2);
    gtk_widget_show(window8);
}

gboolean supprimer_confirme = FALSE;

void
on_check_supprimer_centre_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  supprimer_confirme = gtk_toggle_button_get_active(togglebutton);
}


void
on_btn_supprimer_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id, *check_confirm, *label_msg;
    char id_text[20];
    int id;

    
    entry_id     = lookup_widget(button, "entry_id_centre");
    check_confirm = lookup_widget(button, "check_supprimer_centre");
    label_msg    = lookup_widget(button, "label_message_supprimer");

    
    strcpy(id_text, gtk_entry_get_text(GTK_ENTRY(entry_id)));

  
    if (strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Veuillez entrer un ID !");
        return;
    }

    
    if (!supprimer_confirme) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Cochez la case pour confirmer !");
        return;
    }

    
    id = atoi(id_text);
    int result = supprimer_centre("centres.txt", "inscriptions.txt", id);

    
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(label_msg), "✅ Centre supprimé avec succès !");
        gtk_entry_set_text(GTK_ENTRY(entry_id), "");
	GtkWidget *tv = lookup_widget(gtk_widget_get_toplevel(GTK_WIDGET(button)),"treeview_centre");
        afficher_centres(tv);
    } else {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Centre introuvable !");
    }
}

int id_to_modify = -1;
void
on_btn_modifier1_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id, *label_msg;
    char id_text[20];
    int id;


    entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_centre");
    label_msg = lookup_widget(GTK_WIDGET(button), "label_message_modifier1");


    strcpy(id_text, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    
    if (strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Veuillez entrer un ID !");
        return;
    }


    id = atoi(id_text);


    Centre c = chercher_centre("centres.txt", id);
    if (c.id == -1) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Centre introuvable !");
        return;
    }

    id_to_modify = id;
    gtk_widget_hide(window3);   
    gtk_widget_show(window4);   
}


void
on_btn_retour_modifier1_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window3);
    gtk_widget_show(window8);
}

gboolean modifier_confirme = FALSE;

void
on_check_modifier_centre_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  modifier_confirme = gtk_toggle_button_get_active(togglebutton);
}



void
on_btn_modifier2_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_nom, *entry_adresse, *entry_tel, *entry_email, *combotype, *spin_nbr, *spin_capacite, *check_modifier, *label_msg;
    Centre c;

    entry_nom     = lookup_widget(button, "entry_nom_centre");
    entry_adresse = lookup_widget(button, "entry_adresse_centre");
    entry_tel     = lookup_widget(button, "entry_tel");
    entry_email   = lookup_widget(button, "entry_email");
    combotype     = lookup_widget(button, "combotype");
    spin_nbr      = lookup_widget(button, "spin_nbr");
    spin_capacite = lookup_widget(button, "spin_capacite");
    check_modifier = lookup_widget(button, "check_modifier_centre");
    label_msg     = lookup_widget(button, "label_message_modifer2");

    if (!modifier_confirme) {
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Cochez la case pour confirmer !");
        return;
    }
    c = chercher_centre("centres.txt", id_to_modify);
    
    char *nom     = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    char *adresse = gtk_entry_get_text(GTK_ENTRY(entry_adresse));
    char *tel     = gtk_entry_get_text(GTK_ENTRY(entry_tel));
    char *email   = gtk_entry_get_text(GTK_ENTRY(entry_email));
    char *type    = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combotype));

   
    if (strlen(nom) > 0) strcpy(c.nom, nom);
    if (strlen(adresse) > 0) strcpy(c.adresse, adresse);

    
    if (strlen(tel) > 0) {
        if (strlen(tel) != 8) {
            gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Le numéro de téléphone doit contenir 8 chiffres !");
            return;
        }
        for (int i = 0; i < 8; i++) {
            if (!isdigit(tel[i])) {
                gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ Le numéro de téléphone doit être numérique !");
                return;
            }
        }
        strcpy(c.telephone, tel);
    }


    if (strlen(email) > 0) {
        if (strchr(email, '@') == NULL) {
            gtk_label_set_text(GTK_LABEL(label_msg), "⚠️ L'adresse e-mail n'est pas valide !");
            return;
        }
        strcpy(c.email, email);
    }


    if (type != NULL) strcpy(c.type, type);

  
    c.nb_salles = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr));
    c.capacite  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));

   
    int result = modifier_centre("centres.txt", id_to_modify, c);

    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(label_msg), "✅ Centre modifié avec succès !");

        gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
        gtk_entry_set_text(GTK_ENTRY(entry_adresse), "");
        gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
        gtk_entry_set_text(GTK_ENTRY(entry_email), "");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_nbr), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_capacite), 0);
        gtk_combo_box_set_active(GTK_COMBO_BOX(combotype), -1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_modifier), FALSE);
    } else {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Erreur lors de la modification !");
    }
}


void
on_btn_retour_modifier2_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window4);
    gtk_widget_show(window3);
}


void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id = lookup_widget(button, "entry_id_centre");
    GtkWidget *treeview = lookup_widget(button, "treeview_rechercher_centre");

    GtkWidget *label0 = lookup_widget(window5, "label_message_rechercher"); 

    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));

    // Check if empty
    if (strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label0), "⚠️ Veuillez entrer un ID.");
        return;
    }

    // Check if numeric
    for (int i = 0; id_text[i] != '\0'; i++) {
        if (!isdigit(id_text[i])) {
            gtk_label_set_text(GTK_LABEL(label0), "⚠️ L'ID doit être un nombre !");
            return;
        }
    }

    int id = atoi(id_text);

    // Search
    Centre c = chercher_centre("centres.txt", id);
    if (c.id == -1) {
        gtk_label_set_text(GTK_LABEL(label0), "❌ Aucun centre trouvé avec cet ID !");
        // Optionally clear treeview
        afficher_centres(treeview); // show all centres again
        return;
    }

    gtk_label_set_text(GTK_LABEL(label0), "✅ Centre trouvé !");

    afficher_rechercher_centre(treeview, id);
}


void
on_btn_retour_rechercher_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window5);
    gtk_widget_show(window8);
}


void
on_btn_ajouter_inscription_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    //GtkWidget *window6 = lookup_widget(GTK_WIDGET(button), "window6");

    GtkWidget *entry_adresse = lookup_widget(window6, "entry_adresse_inscription");
    GtkWidget *entry_id = lookup_widget(window6, "entry_id_inscription");
    GtkWidget *combo_nom = lookup_widget(window6, "combo_nom_centre");
    GtkWidget *combo_spec = lookup_widget(window6, "combo_specialite");
    GtkWidget *spin_jour = lookup_widget(window6, "spin_jour");
    GtkWidget *spin_mois = lookup_widget(window6, "spin_mois");
    GtkWidget *spin_annee = lookup_widget(window6, "spin_annee");
    GtkWidget *spin_heure = lookup_widget(window6, "spin_heure");
    GtkWidget *spin_minute = lookup_widget(window6, "spin_minute");
    GtkWidget *label_msg = lookup_widget(window6, "label_message_inscription");

    const char *id_txt = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *nom_centre_txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_nom));
    const char *adresse_txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(entry_adresse));
    const char *spec_txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_spec));

    // ============================
    //   VALIDATIONS
    // ============================

    // ---- test ID empty ----
    if (strlen(id_txt) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ ID vide !");
        return;
    }

    // ---- test ID numeric ----
    int isnum = 1;
    for (int i = 0; id_txt[i] != '\0'; i++)
        if (!isdigit(id_txt[i])) isnum = 0;

    if (!isnum) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ ID doit être numérique !");
        return;
    }

    // ---- test centre selection ----
    if (nom_centre_txt == NULL || strlen(nom_centre_txt) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Veuillez choisir un centre !");
        return;
    }

    // ---- test address empty ----
    if (strlen(adresse_txt) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Adresse vide !");
        return;
    }

    // ---- test speciality selection ----
    if (spec_txt == NULL || strlen(spec_txt) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Spécialité non choisie !");
        return;
    }

    // ---- test date ----
    int j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    int m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));

    if (j < 1 || j > 31 || m < 1 || m > 12) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Date invalide !");
        return;
    }

    // ---- test time ----
    int h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_heure));
    int mm = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_minute));

    if (h < 6 || h > 23 || mm < 0 || mm > 59) {
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Heure invalide !");
        return;
    }

    // ============================
    //   BUILD INSCRIPTION
    // ============================

    Inscription I;

    I.id = atoi(id_txt);
    strcpy(I.nom_centre, nom_centre_txt);
    strcpy(I.adresse, adresse_txt);
    strcpy(I.specialite, spec_txt);

    I.date.jour = j;
    I.date.mois = m;
    I.date.annee = a;

    I.heure.heure = h;
    I.heure.minute = mm;

    // ============================
    //   SAVE USING YOUR FUNCTION
    // ============================

    int r = ajouter_inscription("inscriptions.txt", "centres.txt", I);

    if (r == 1){
        gtk_label_set_text(GTK_LABEL(label_msg), "✅ Inscription ajoutée !");
	GtkWidget *tv = lookup_widget(window6, "treeview_inscription");
        afficher_inscriptions(tv);
    }else if (r == 2)
        gtk_label_set_text(GTK_LABEL(label_msg), "❌ Centre introuvable !");
    else if ( r== 3 ) 
	gtk_label_set_text(GTK_LABEL(label_msg), "❌ Aucune salle disponible pour la date et l’heure sélectionnées.");
    else
        gtk_label_set_text(GTK_LABEL(label_msg), "⚠ Erreur lors de l'ajout !");
}


void
on_btn_retour_inscription_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window6);
    gtk_widget_show(window8);
}


void
on_btn_retour_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window7);
    gtk_widget_show(window8);
}


void
on_btn_window_ajouter_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window8);
    gtk_widget_show(window1);


    GtkWidget *tv = lookup_widget(window1, "treeview_centre");
    afficher_centres(tv);
}


void
on_btn_window_modifier_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window8);
    gtk_widget_show(window3);
}


void
on_btn_window_supprimer_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window8);
    gtk_widget_show(window2);

    GtkWidget *tv = lookup_widget(window2, "treeview_centre");
    afficher_centres(tv);
    
}


void
on_btn_window_rechercher_clicked(GtkButton *button, gpointer user_data)
{
    // Hide the current window and show the target window
    gtk_widget_hide(window8);
    gtk_widget_show(window5);


    GtkWidget *tv = lookup_widget(window5, "treeview_rechercher_centre");
    afficher_rechercher_centre(tv, 0);

    
}

void
on_btn_window_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window8);
    gtk_widget_show(window7);



    GtkWidget *tv = lookup_widget(window7, "treeview_stats");
    afficher_stats(tv);



    GtkWidget *label_total = lookup_widget(window7, "label_nbre_total");
    GtkWidget *label_populaire = lookup_widget(window7, "label_centre_populaire");

    Stats s;
    statistiques("centres.txt", "inscriptions.txt", &s);

    char txt[128];

    // Total centres
    sprintf(txt, "%d", s.total_centres);
    gtk_label_set_text(GTK_LABEL(label_total), txt);

    // Centre populaire
    if (s.id_max == -1)
        gtk_label_set_text(GTK_LABEL(label_populaire), "Aucun centre");
    else {
        // Find the centre name
        for (int i = 0; i < s.nb_centres; i++) {
            if (s.ids[i] == s.id_max) {
                gtk_label_set_text(GTK_LABEL(label_populaire), s.noms[i]);
                break;
            }
        }
    }
}


void
on_btn_retour_navigation_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window8);
    gtk_widget_show(window9);
}




void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry1, *entry2, *label_msg_login, *label_authen;
    User u;

    entry1 = lookup_widget(button, "entry1");
    entry2 = lookup_widget(button, "entry2");
    label_msg_login = lookup_widget(button, "label_msg_login");
    label_authen = lookup_widget(window11, "label_authen");

    const char *username = gtk_entry_get_text(GTK_ENTRY(entry1));
    const char *password = gtk_entry_get_text(GTK_ENTRY(entry2));

    if(strlen(username) == 0 || strlen(password) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg_login), "⚠️ Tous les champs sont obligatoires !");
        return;
    }

    int res = authenticate(username, password, &u);
    if(res == 1) {
	 gtk_widget_hide(window9);
         gtk_widget_show(window11);
        char msg[100];
        strcpy(msg, "✅ Bienvenue ");
        strcat(msg, u.username);
        strcat(msg, " ! Role: ");
        strcat(msg, u.role);

        gtk_label_set_text(GTK_LABEL(label_authen), msg);
	        if(strcmp(u.role, "ADMIN") == 0)
        {
            gtk_widget_show(window8);          // admin GUI
        }
        else if(strcmp(u.role, "ENTRAINEUR") == 0)
        {
            gtk_widget_show(window6);          // trainer GUI
	    GtkWidget *tv = lookup_widget(window6, "treeview_inscription");
            afficher_inscriptions(tv);
   	    char centres[50][100];
	    int n = tableau_centre_disponible(centres);
            //GtkWidget *combo_centre;

            //combo_centre = lookup_widget(button, "combo_nom_centre");
            GtkWidget *combo_nom = lookup_widget(window6, "combo_nom_centre");
	    clear_combo_box(combo_nom);
	    for (int i = 0; i < n; i++)
		{
		    gtk_combo_box_append_text(GTK_COMBO_BOX(combo_nom),
				                   centres[i]);
		}
        }
        else if(strcmp(u.role, "MEMBRE") == 0)
        {
            //gtk_widget_show(window6);          // member GUI
        }

    } else if(res == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg_login), "⚠️ Nom d'utilisateur ou mot de passe incorrect !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_msg_login), "❌ Erreur fichier users.txt !");
    }
}


void
on_btn_inscrit_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_nom, *entry_prenom, *spin_age, *entry_email_insc;
    GtkWidget *entry_tel_insc, *entry_user, *entry_pass, *combo_role, *label_msg_insc;
    User u;

    entry_nom = lookup_widget(button, "entry_nom");
    entry_prenom = lookup_widget(button, "entry_prenom");
    spin_age = lookup_widget(button, "spin_age");
    entry_email_insc = lookup_widget(button, "entry_email_insc");
    entry_tel_insc = lookup_widget(button, "entry_tel_insc");
    entry_user = lookup_widget(button, "entry_user");
    entry_pass = lookup_widget(button, "entry_pass");
    combo_role = lookup_widget(button, "combo_role");
    label_msg_insc = lookup_widget(button, "label_msg_insc");

    strcpy(u.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(u.prenom, gtk_entry_get_text(GTK_ENTRY(entry_prenom)));
    u.age = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_age));
    strcpy(u.email, gtk_entry_get_text(GTK_ENTRY(entry_email_insc)));
    strcpy(u.tel, gtk_entry_get_text(GTK_ENTRY(entry_tel_insc)));
    strcpy(u.username, gtk_entry_get_text(GTK_ENTRY(entry_user)));
    strcpy(u.password, gtk_entry_get_text(GTK_ENTRY(entry_pass)));

    int role_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_role));
    if (role_index == 0) strcpy(u.role, "ADMIN");
    else if (role_index == 1) strcpy(u.role, "ENTRAINEUR");
    else strcpy(u.role, "MEMBRE");

  
    if(strlen(u.nom)==0 || strlen(u.prenom)==0 || strlen(u.username)==0 || strlen(u.password)==0) {
        gtk_label_set_text(GTK_LABEL(label_msg_insc), "⚠️ Tous les champs sont obligatoires !");
        return;
    }

    int res = add_user(u);
    if(res == 1) {
        gtk_label_set_text(GTK_LABEL(label_msg_insc), "✅ Inscription réussie !");
        gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
        gtk_entry_set_text(GTK_ENTRY(entry_prenom), "");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_age), 1);
        gtk_entry_set_text(GTK_ENTRY(entry_email_insc), "");
        gtk_entry_set_text(GTK_ENTRY(entry_tel_insc), "");
        gtk_entry_set_text(GTK_ENTRY(entry_user), "");
        gtk_entry_set_text(GTK_ENTRY(entry_pass), "");
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_role), -1);
    } else if(res == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg_insc), "⚠️ Username déjà utilisé !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_msg_insc), "❌ Erreur lors de l'inscription !");
    }

}


void
on_btn_retour_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window10);
    gtk_widget_show(window9);
}


void
on_btn_sign_up_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window9);
    gtk_widget_show(window10);
}


void
on_treeview_centre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_treeview_rechercher_centre_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    Centre c;

    // Get the selected row iter from the path
    model = gtk_tree_view_get_model(treeview);
    if (!gtk_tree_model_get_iter(model, &iter, path)) return;

    // Get the centre ID from the selected row
    gtk_tree_model_get(model, &iter,0, &c.id, -1);

    // Fetch full details from file
    c = chercher_centre("centres.txt", c.id);
    if (c.id == -1) return; // safety check

    // Lookup window12 and the label101
    //GtkWidget *window12 = lookup_widget(GTK_WIDGET(treeview), "window12");
    GtkWidget *label101 = lookup_widget(window12, "label_resultat");

    // Build the message exactly like your example
    char message[512]; // increased size to be safe
    sprintf(message,
            "🆔 ID: %d\n"
            "🏢 Nom: %s\n"
            "📍 Adresse: %s\n"
            "📞 Téléphone: %s\n"
            "✉️ Email: %s\n"
            "📌 Type: %s\n"
            "🏟 Nb de salles: %d\n"
            "👥 Capacité: %d",
            c.id, c.nom, c.adresse, c.telephone,
            c.email, c.type, c.nb_salles, c.capacite);

    // Set the message to label101
    gtk_label_set_text(GTK_LABEL(label101), message);

    // Show the window
    gtk_widget_show(window12);

}


void
on_treeview_inscription_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_treeview_stats_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_btn_ok_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window12);
}

void clear_combo_box(GtkComboBox *combo)
{
    GtkTreeModel *model = gtk_combo_box_get_model(combo);
    GtkListStore *store;

    if (model)
    {
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
}


void
on_btn_adresse_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *entry_adresse = lookup_widget(window6, "entry_adresse_inscription");
   	GtkWidget *combo_nom = lookup_widget(window6, "combo_nom_centre");
	clear_combo_box(entry_adresse);
	char *nom_centre_txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_nom));
	char adresses[50][100];
	int n = tableau_centre_adresse(adresses,nom_centre_txt);
	for (int i = 0; i < n; i++)
		{
		    gtk_combo_box_append_text(GTK_COMBO_BOX(entry_adresse),
				                   adresses[i]);
		}

}


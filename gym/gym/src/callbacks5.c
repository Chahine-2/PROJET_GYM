#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "courssportifs.h"

// Global window variables
//GtkWidget *window_administrateur = NULL;
GtkWidget *window_ajouter = NULL;
GtkWidget *window_modifier = NULL;
GtkWidget *window_rechercher = NULL;
GtkWidget *window_supprimer = NULL;
GtkWidget *window_membre = NULL;
GtkWidget *window_emploi = NULL;  // ADDED for emploi window
GtkWidget *administrateur_;
GtkWidget *window20;
GtkWidget *membre;

// Global confirmation flag
gboolean supprimer_confirme = FALSE;

// Helper function prototypes
void show_message_dialog(GtkWidget *widget, const char *message);
int generer_id_cours(void);
void set_combo_text(GtkWidget *combo, const char *text);
void charger_cours_dans_combo(GtkWidget *combo, const char *filename);

// ============================================================================
// ADMINISTRATEUR WINDOW CALLBACKS
// ============================================================================

void
on_button_ajouter_admin_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Ajouter button clicked in admin window\n");
    window_ajouter = create_ajouter();
    if (window_ajouter == NULL) {
        printf("[DEBUG] Creating ajouter window...\n");
        
        if (window_ajouter) {
            printf("[DEBUG] Ajouter window created successfully\n");
        } else {
            printf("[ERROR] Failed to create ajouter window\n");
        }
    }
    
    if (window_ajouter != NULL) {
        gtk_widget_hide(administrateur_);
        gtk_widget_show(window_ajouter);
        printf("[DEBUG] Ajouter window shown\n");
    } else {
        printf("[ERROR] Cannot show ajouter window - it's NULL\n");
    }
}

void
on_button_modifier_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Modifier button clicked in admin window\n");
    window_modifier = create_modifier();
    if (window_modifier == NULL) {
        printf("[DEBUG] Creating modifier window...\n");
        
        if (window_modifier) {
            printf("[DEBUG] Modifier window created successfully\n");
        } else {
            printf("[ERROR] Failed to create modifier window\n");
        }
    }
    
    if (window_modifier != NULL) {
        gtk_widget_hide(administrateur_);
        gtk_widget_show(window_modifier);
        
        // Load existing courses into combo box
        GtkWidget *combo_modifier_nom = lookup_widget(window_modifier, "combo_modifier_nom");
        if (combo_modifier_nom != NULL) {
            charger_cours_dans_combo(combo_modifier_nom, "cours.txt");
        }
        printf("[DEBUG] Modifier window shown\n");
    } else {
        printf("[ERROR] Cannot show modifier window - it's NULL\n");
    }
}

void
on_button_rechercher_admin_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Rechercher button clicked in admin window\n");
     window_rechercher = create_rechercher();
    if (window_rechercher == NULL) {
        printf("[DEBUG] Creating rechercher window...\n");
       
        if (window_rechercher) {
            printf("[DEBUG] Rechercher window created successfully\n");
        } else {
            printf("[ERROR] Failed to create rechercher window\n");
        }
    }
    
    if (window_rechercher != NULL) {
        gtk_widget_hide(administrateur_);
        gtk_widget_show(window_rechercher);
        printf("[DEBUG] Rechercher window shown\n");
    } else {
        printf("[ERROR] Cannot show rechercher window - it's NULL\n");
    }
}

void
on_button_supprimer_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] ==========================================\n");
    printf("[DEBUG] SUPPRIMER BUTTON CLICKED IN ADMIN WINDOW\n");
    printf("[DEBUG] ==========================================\n");
    
    // Check if the button itself is working
    printf("[DEBUG] Button signal received successfully\n");
    window_supprimer = create_supprimer();
    if (window_supprimer == NULL) {
        printf("[DEBUG] Creating supprimer window for the first time...\n");
        
        
        if (window_supprimer) {
            printf("[DEBUG] SUCCESS: Supprimer window created\n");
            printf("[DEBUG] Window pointer: %p\n", window_supprimer);
            
            // Try to find some widgets to verify the window is properly created
            GtkWidget *test_widget = lookup_widget(window_supprimer, "combo_supprimer_nom");
            if (test_widget) {
                printf("[DEBUG] Found widget 'combo_supprimer_nom' in supprimer window\n");
            } else {
                printf("[WARNING] Could not find widget 'combo_supprimer_nom'\n");
            }
        } else {
            printf("[CRITICAL ERROR] FAILED: create_supprimer() returned NULL\n");
            printf("[DEBUG] Checking if create_supprimer function exists...\n");
            
            // Try to manually create a simple window as a test
            GtkWidget *test_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            if (test_window) {
                printf("[DEBUG] Successfully created a test GTK window\n");
                gtk_window_set_title(GTK_WINDOW(test_window), "Test Supprimer Window");
                gtk_window_set_default_size(GTK_WINDOW(test_window), 400, 300);
                
                GtkWidget *label = gtk_label_new("This is a test window for Supprimer");
                gtk_container_add(GTK_CONTAINER(test_window), label);
                
                window_supprimer = test_window;
                printf("[DEBUG] Using test window instead\n");
            } else {
                printf("[CRITICAL ERROR] Cannot even create a basic GTK window\n");
            }
        }
    } else {
        printf("[DEBUG] Supprimer window already exists at address: %p\n", window_supprimer);
    }
    
    if (window_supprimer != NULL) {
        printf("[DEBUG] Attempting to show supprimer window...\n");
        
        // First hide the admin window
        if (administrateur_) {
            printf("[DEBUG] Hiding administrateur window\n");
            gtk_widget_hide(administrateur_);
        }
        
        // Show the supprimer window
        printf("[DEBUG] Showing supprimer window\n");
        gtk_widget_show(window_supprimer);
        
        // Load existing courses into combo box
        GtkWidget *combo_supprimer_nom = lookup_widget(window_supprimer, "combo_supprimer_nom");
        if (combo_supprimer_nom != NULL) {
            printf("[DEBUG] Loading courses into combo box...\n");
            charger_cours_dans_combo(combo_supprimer_nom, "cours.txt");
        } else {
            printf("[WARNING] Could not find combo_supprimer_nom widget\n");
        }
        
        printf("[DEBUG] SUCCESS: Supprimer window should now be visible\n");
    } else {
        printf("[CRITICAL ERROR] window_supprimer is still NULL after creation attempt\n");
        
        // Show error message
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Erreur: Impossible de créer la fenêtre Supprimer!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    
    printf("[DEBUG] ==========================================\n");
}

void
on_button_retour_admin_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Retour button clicked in admin window\n");
    // Do nothing - this button is in the admin window itself
}

// ============================================================================
// SUPPRIMER WINDOW CALLBACKS
// ============================================================================

void
on_checkbutton_attention_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    supprimer_confirme = gtk_toggle_button_get_active(togglebutton);
    printf("[DEBUG] Checkbutton toggled: %s\n", supprimer_confirme ? "TRUE" : "FALSE");
}

void
on_button_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] ==========================================\n");
    printf("[DEBUG] DELETE BUTTON CLICKED IN SUPPRIMER WINDOW\n");
    printf("[DEBUG] ==========================================\n");
    
    if (window_supprimer == NULL) {
        printf("[ERROR] window_supprimer is NULL in delete callback\n");
        return;
    }
    
    printf("[DEBUG] Looking for widgets in supprimer window...\n");
    
    // Try to find the combo box with different possible names
    GtkWidget *combo_supprimer_nom = NULL;
    const char *possible_names[] = {
        "combo_supprimer_nom",
        "combobox_supprimer_nom", 
        "combo_nom",
        "combo_supprimer",
        NULL
    };
    
    for (int i = 0; possible_names[i] != NULL; i++) {
        combo_supprimer_nom = lookup_widget(window_supprimer, possible_names[i]);
        if (combo_supprimer_nom) {
            printf("[DEBUG] Found combo box with name: %s\n", possible_names[i]);
            break;
        }
    }
    
    if (combo_supprimer_nom == NULL) {
        printf("[ERROR] Could not find any combo box widget in supprimer window\n");
        show_message_dialog(window_supprimer, "❌ Erreur: Combo box non trouvée !");
        return;
    }
    
    // Try to find the checkbutton
    GtkWidget *checkbutton_attention = lookup_widget(window_supprimer, "checkbutton_attention");
    if (checkbutton_attention == NULL) {
        printf("[WARNING] Could not find checkbutton_attention widget\n");
    }
    
    // Get course name to delete
    char *nom_cours = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_supprimer_nom));
    if (nom_cours == NULL || strlen(nom_cours) == 0) {
        printf("[DEBUG] No course selected in combo box\n");
        show_message_dialog(window_supprimer, "⚠️ Veuillez sélectionner un cours !");
        return;
    }
    
    printf("[DEBUG] Selected course to delete: %s\n", nom_cours);
    
    // Find course ID by name
    CoursSportif c = chercher_cours_par_nom("cours.txt", nom_cours);
    if (c.id == -1) {
        printf("[DEBUG] Course not found in file: %s\n", nom_cours);
        show_message_dialog(window_supprimer, "⚠️ Cours introuvable !");
        g_free(nom_cours);
        return;
    }
    
    printf("[DEBUG] Course found with ID: %d\n", c.id);
    
    // Check confirmation
    if (!supprimer_confirme) {
        printf("[DEBUG] Confirmation not checked\n");
        show_message_dialog(window_supprimer, "⚠️ Veuillez cocher la case de confirmation !");
        g_free(nom_cours);
        return;
    }
    
    printf("[DEBUG] Confirmation checked. Deleting course...\n");
    
    // Delete course
    int result = supprimer_cours("cours.txt", "inscriptions.txt", c.id);
    
    if (result == 1) {
        printf("[DEBUG] Course deleted successfully\n");
        show_message_dialog(window_supprimer, "✅ Cours supprimé avec succès !");
        
        // Clear fields
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_supprimer_nom), -1);
        if (checkbutton_attention) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_attention), FALSE);
        }
        supprimer_confirme = FALSE;
        
        // Refresh combo box
        charger_cours_dans_combo(combo_supprimer_nom, "cours.txt");
    } else {
        printf("[DEBUG] Error deleting course\n");
        show_message_dialog(window_supprimer, "❌ Erreur lors de la suppression !");
    }
    
    g_free(nom_cours);
    printf("[DEBUG] ==========================================\n");
}

void
on_button_supprimer_annuler_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Annuler button clicked in supprimer window\n");
    if (window_supprimer) {
        gtk_widget_hide(window_supprimer);
    }
    if (administrateur_) {
        gtk_widget_show(administrateur_);
    }
}

// ============================================================================
// AJOUTER WINDOW CALLBACKS
// ============================================================================

void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Ajouter button clicked in ajouter window\n");
    
    // Simple test: Just add a course with hardcoded values
    CoursSportif c;
    c.id = generer_id_cours();
    strcpy(c.nom, "Test Cours");
    strcpy(c.jour_semaine, "lundi");
    c.date.jour = 1;
    c.date.mois = 1;
    c.date.annee = 2024;
    c.heure.heure = 10;
    c.heure.minute = 0;
    strcpy(c.salle, "1");
    strcpy(c.entraineur, "Test Entraineur");
    c.duree = 60;
    strcpy(c.centre, "Test Centre");
    
    int result = ajouter_cours("cours.txt", c);
    
    if (result == 1) {
        show_message_dialog(window_ajouter, "✅ Cours test ajouté avec succès !");
        printf("[DEBUG] Test course added successfully\n");
    } else {
        show_message_dialog(window_ajouter, "❌ Erreur lors de l'ajout !");
        printf("[DEBUG] Error adding test course\n");
    }
}

void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Afficher button clicked in ajouter window\n");
    printf("[DEBUG] Opening emploi window...\n");
    
    // Check if emploi window is already created
    if (window_emploi == NULL) {
        printf("[DEBUG] Creating emploi window for the first time...\n");
        window_emploi = create_emploi();  // Make sure this function exists in interface.c
        
        if (window_emploi) {
            printf("[DEBUG] Emploi window created successfully\n");
        } else {
            printf("[ERROR] Failed to create emploi window\n");
            show_message_dialog(window_ajouter, "❌ Erreur: Impossible de créer la fenêtre Emploi!");
            return;
        }
    }
    
    // Hide the ajouter window
    if (window_ajouter != NULL) {
        gtk_widget_hide(window_ajouter);
    }
    
    // Show the emploi window
    if (window_emploi != NULL) {
        gtk_widget_show(window_emploi);
        printf("[DEBUG] Emploi window shown\n");
    } else {
        printf("[ERROR] Emploi window is NULL\n");
    }
}

void
on_button_ajouter_annuler_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Annuler button clicked in ajouter window\n");
    gtk_widget_hide(window_ajouter);
    gtk_widget_show(administrateur_);
}

// ============================================================================
// RECHERCHER WINDOW CALLBACKS
// ============================================================================

void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Rechercher button clicked in recherche window\n");
    show_message_dialog(window_rechercher, "✅ Recherche fonctionne !");
}

void
on_button_rechercher_fermer_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Fermer button clicked in recherche window\n");
    gtk_widget_hide(window_rechercher);
    gtk_widget_show(administrateur_);
}

// ============================================================================
// MODIFIER WINDOW CALLBACKS
// ============================================================================

void
on_combo_modifier_nom_changed          (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    printf("[DEBUG] Combo box changed in modifier window\n");
}

void
on_button_modifier_enregistrer_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Enregistrer button clicked in modifier window\n");
    show_message_dialog(window_modifier, "✅ Modification test fonctionne !");
}

void
on_button_modifier_annuler_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Annuler button clicked in modifier window\n");
    gtk_widget_hide(window_modifier);
    gtk_widget_show(administrateur_);
}

// ============================================================================
// MEMBRE WINDOW CALLBACKS
// ============================================================================

void
on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] S'inscrire button clicked in membre window\n");
    
    if (window_membre == NULL) {
        window_membre = create_membre();
    }
    
    if (window_membre != NULL) {
        gtk_widget_hide(administrateur_);
        gtk_widget_show(window_membre);
    }
}

void
on_button_membre_annuler_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Annuler button clicked in membre window\n");
    gtk_widget_hide(membre);
    gtk_widget_show(window20);
}

// ============================================================================
// EMPLOI WINDOW CALLBACKS
// ============================================================================

void
on_button_tout_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Tout button clicked in emploi window\n");
    
    if (window_emploi == NULL) {
        printf("[ERROR] Emploi window is NULL\n");
        return;
    }
    
    // Find the treeview widget
    GtkWidget *treeview_emploi = lookup_widget(window_emploi, "treeview_emploi");
    if (treeview_emploi == NULL) {
        printf("[ERROR] Could not find treeview_emploi widget\n");
        
        // Try alternative names
        const char *possible_names[] = {
            "treeview_emploi",
            "treeview",
            "treeview1",
            "tree_view_emploi",
            NULL
        };
        
        for (int i = 0; possible_names[i] != NULL; i++) {
            treeview_emploi = lookup_widget(window_emploi, possible_names[i]);
            if (treeview_emploi) {
                printf("[DEBUG] Found treeview with name: %s\n", possible_names[i]);
                break;
            }
        }
    }
    
    if (treeview_emploi != NULL) {
        printf("[DEBUG] Loading all courses into treeview...\n");
        afficher_emploi_temps(treeview_emploi);
        show_message_dialog(window_emploi, "✅ Tous les cours affichés !");
    } else {
        printf("[ERROR] Could not find any treeview widget in emploi window\n");
        show_message_dialog(window_emploi, "❌ Erreur: Treeview non trouvé !");
    }
}

void
on_button_emploi_par_jour_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Filtrer par jour button clicked in emploi window\n");
    
    if (window_emploi == NULL) return;
    
    // Find the combo box for days
    GtkWidget *combo_jour = lookup_widget(window_emploi, "combo_jour");
    if (combo_jour == NULL) {
        // Try alternative names
        combo_jour = lookup_widget(window_emploi, "combobox_jour");
    }
    
    if (combo_jour != NULL) {
        char *jour = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_jour));
        if (jour != NULL && strlen(jour) > 0) {
            printf("[DEBUG] Filtering by day: %s\n", jour);
            
            // Find the treeview
            GtkWidget *treeview_emploi = lookup_widget(window_emploi, "treeview_emploi");
            if (treeview_emploi) {
                afficher_emploi_par_jour(treeview_emploi, jour);
                char message[100];
                sprintf(message, "✅ Cours du %s affichés !", jour);
                show_message_dialog(window_emploi, message);
            }
            
            g_free(jour);
        } else {
            show_message_dialog(window_emploi, "⚠️ Veuillez sélectionner un jour !");
        }
    } else {
        show_message_dialog(window_emploi, "❌ Erreur: Combo jour non trouvé !");
    }
}

void
on_button_emploi_par_centre_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Filtrer par centre button clicked in emploi window\n");
    
    if (window_emploi == NULL) return;
    
    // Find the combo box for centers
    GtkWidget *combo_centre = lookup_widget(window_emploi, "combo_centre");
    if (combo_centre == NULL) {
        combo_centre = lookup_widget(window_emploi, "combobox_centre");
    }
    
    if (combo_centre != NULL) {
        char *centre = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre));
        if (centre != NULL && strlen(centre) > 0) {
            printf("[DEBUG] Filtering by center: %s\n", centre);
            
            // Find the treeview
            GtkWidget *treeview_emploi = lookup_widget(window_emploi, "treeview_emploi");
            if (treeview_emploi) {
                afficher_emploi_par_centre(treeview_emploi, centre);
                char message[100];
                sprintf(message, "✅ Cours du centre %s affichés !", centre);
                show_message_dialog(window_emploi, message);
            }
            
            g_free(centre);
        } else {
            show_message_dialog(window_emploi, "⚠️ Veuillez sélectionner un centre !");
        }
    } else {
        show_message_dialog(window_emploi, "❌ Erreur: Combo centre non trouvé !");
    }
}

void
on_treeview_emploi_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    printf("[DEBUG] Treeview row activated in emploi window\n");
    
    CoursSportif cours;
    if (get_cours_selectionne(GTK_WIDGET(treeview), &cours)) {
        char message[500];  // Increased buffer size to fix the warning
        sprintf(message, "✅ Cours sélectionné:\n"
                         "Nom: %s\n"
                         "Jour: %s\n"
                         "Salle: %s\n"
                         "Entraîneur: %s\n"
                         "Centre: %s",
                         cours.nom, cours.jour_semaine, 
                         cours.salle, cours.entraineur, cours.centre);
        show_message_dialog(window_emploi, message);
    }
}

void
on_button_emploi_retour_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    printf("[DEBUG] Retour button clicked in emploi window\n");
    
    // Hide the emploi window
    if (window_emploi != NULL) {
        gtk_widget_hide(window_emploi);
    }
    
    // Show the ajouter window
    if (window_ajouter != NULL) {
        gtk_widget_show(window_ajouter);
    }
}

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

void show_message_dialog(GtkWidget *widget, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_OK,
                                              "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int generer_id_cours(void) {
    static int last_id = 1000;
    return ++last_id;
}

void set_combo_text(GtkWidget *combo, const char *text) {
    // Simplified for now
    if (text && strlen(text) > 0) {
        printf("[DEBUG] Setting combo text to: %s\n", text);
    }
}

void charger_cours_dans_combo(GtkWidget *combo, const char *filename) {
    if (combo == NULL) {
        printf("[ERROR] Combo widget is NULL in charger_cours_dans_combo\n");
        return;
    }
    
    printf("[DEBUG] Loading courses into combo from: %s\n", filename);
    
    // Get the list store model
    GtkListStore *store = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combo)));
    if (store == NULL) {
        printf("[ERROR] Could not get list store from combo box\n");
        return;
    }
    
    // Clear existing items
    gtk_list_store_clear(store);
    
    // Load courses from file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("[DEBUG] File %s doesn't exist yet\n", filename);
        
        // Add a placeholder
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, "Aucun cours disponible", -1);
        return;
    }
    
    char ligne[500];
    int count = 0;
    while (fgets(ligne, sizeof(ligne), file)) {
        CoursSportif c;
        if (sscanf(ligne, "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%[^;];%[^;];%d;%[^\n]", 
                  &c.id, c.nom, c.jour_semaine, &c.date.jour, &c.date.mois, &c.date.annee,
                  &c.heure.heure, &c.heure.minute, c.salle, c.entraineur, &c.duree, c.centre) >= 10) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, c.nom, -1);
            count++;
            printf("[DEBUG] Added course to combo: %s\n", c.nom);
        }
    }
    
    fclose(file);
    printf("[DEBUG] Loaded %d courses into combo box\n", count);
}

void
on_button_chercher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


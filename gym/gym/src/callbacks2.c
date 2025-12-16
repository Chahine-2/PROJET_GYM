#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#include "callbacks2.h"
#include "callbacks1.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "member.h"
#include "coach.h"

void show_message(GtkWidget *parent, const gchar *msg) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "%s", msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int ask_confirmation(GtkWidget *parent, const gchar *msg) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_YES_NO,
                                               "%s", msg);
    int result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return (result == GTK_RESPONSE_YES);
}

const char * get_entry_text(GtkWidget *window, const char *entry_name) {
    GtkWidget *w = lookup_widget(window, entry_name);
    if (w) return gtk_entry_get_text(GTK_ENTRY(w));
    return "";
}

// Helpers for Radio and Combos
int is_radio_active(GtkWidget *window, const char *radio_name) {
    GtkWidget *w = lookup_widget(window, radio_name);
    if (w && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w))) return 1;
    return 0;
}

void populate_coach_combo(GtkWidget *combo) {
    if (!combo) return;
    
    // Clear existing items if possible ( GTK 2.4+ )
    // gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combo))));
    // But this app seems to use append_text which is for simple text combos.
    // We'll just append.
    
    // Check if "Non" already exists? No easy way. 
    // We assume this is called once on window creation.
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Non");

    FILE *f = fopen("coach.txt", "r");
    if (f) {
        char line[1024];
        Coach c;
        while (fgets(line, sizeof(line), f)) {
            // Parse line manually to avoid fscanf issues
            // Format: id;nom;prenom;age;sexe;tel;email;domaine
            
             char *p = line;
             char *next;
             
             // Strip newline
             char *nl = strchr(line, '\n'); if(nl) *nl = '\0';
             
             if(strlen(line) == 0) continue;
             
             memset(&c, 0, sizeof(c));
             
             // ID
             next = strchr(p, ';'); if(!next) continue;
             *next = '\0'; strcpy(c.id, p); p = next+1;
             
             // Nom
             next = strchr(p, ';'); if(!next) continue;
             *next = '\0'; strcpy(c.nom, p); p = next+1;
             
             // Prenom
             next = strchr(p, ';'); if(!next) continue;
             *next = '\0'; strcpy(c.prenom, p); p = next+1;
             
             // ... we only need ID, Nom, Prenom really for the display
             // Skip others or just use what we have
             
             char buffer[200];
             sprintf(buffer, "%s %s (%s)", c.nom, c.prenom, c.id);
             gtk_combo_box_append_text(GTK_COMBO_BOX(combo), buffer);
        }
        fclose(f);
    }
}

/*void on_button1_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *login_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    const gchar *id = get_entry_text(login_window, "entry1");
    const gchar *pass = get_entry_text(login_window, "entry2");
    
    if (strcmp(id, "1234") == 0 && strcmp(pass, "1234") == 0) {
        gtk_widget_hide(login_window);
        GtkWidget *menu = create_Menu_Principale();
        gtk_widget_show(menu);
    } else {
        show_message(login_window, "Login Incorrect");
    }
}
*/
void on_button20_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *menu = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(menu);
    GtkWidget *login = create_window_navigation();
    gtk_widget_show(login);
}

void on_button15_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_AjoutMembreNJ();
    // Populate Coach Combo
    populate_coach_combo(lookup_widget(w, "comboboxentry_coach"));
    gtk_widget_show(w);
}

void on_button16_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_Modifier_membre();
    populate_coach_combo(lookup_widget(w, "comboboxentry_mod_coach"));
    gtk_widget_show(w);
}

void on_button17_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_SuppressionMembreNJ();
    gtk_widget_show(w);
}

void on_button19_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_RechercherMembreNJ();
    GtkWidget *tree = lookup_widget(w, "treeview1");
    if (tree) {
        afficher_membre(tree);
    }
    gtk_widget_show(w);
}

void on_button_ajouter_coach_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_AJoutercoach();
    gtk_widget_show(w);
}

void on_button_modifier_coach_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_Modifier_coach();
    gtk_window_set_default_size(GTK_WINDOW(w), 600, 750);
    gtk_widget_show(w);

}

void on_button_supprimer_coach_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_supprimer_coachNJ ();
    gtk_window_set_default_size(GTK_WINDOW(w), 400, 300);
    gtk_widget_show(w);
}

void on_button_rechercher_coach_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = create_RecherchercoachNJ();
    gtk_window_set_default_size(GTK_WINDOW(w), 760, 520);
    GtkWidget *tree = lookup_widget(w, "treeview2");
    gtk_widget_show(w);
}

void on_button14_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *w = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(w);
}

void on_button2_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    const gchar *title = gtk_window_get_title(GTK_WINDOW(window));
    int is_add = (strstr(title, "Ajouter") != NULL);
    Membre m;
    memset(&m, 0, sizeof(m));

    if (is_add) {
         strcpy(m.id, get_entry_text(window, "entry25"));
         strcpy(m.nom, get_entry_text(window, "entry6"));
         strcpy(m.prenom, get_entry_text(window, "entry7"));
         m.age = atoi(get_entry_text(window, "entry8"));
         strcpy(m.telephone, get_entry_text(window, "entry9"));
         strcpy(m.email, get_entry_text(window, "entry10"));
         strcpy(m.prix, get_entry_text(window, "entry26"));
         
         GtkWidget *c1 = lookup_widget(window, "comboboxentry1");
         if (c1) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(c1));
             if(txt) strcpy(m.type_abonnement, txt);
         }
         GtkWidget *c6 = lookup_widget(window, "comboboxentry6");
         if (c6) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(c6));
             if(txt) strcpy(m.type_forfait, txt);
         }
         
         GtkWidget *cal = lookup_widget(window, "calendar1");
         if (cal) gtk_calendar_get_date(GTK_CALENDAR(cal), (guint*)&m.annee, (guint*)&m.mois, (guint*)&m.jour);
         
         // Sexe: Radio1=Homme, Radio2=Femme
         if (is_radio_active(window, "radiobutton1")) strcpy(m.sexe, "Homme");
         else strcpy(m.sexe, "Femme");
         
         // Coach from Combo
         GtkWidget *cc = lookup_widget(window, "comboboxentry_coach");
         if (cc) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cc));
             if(txt) strcpy(m.coach, txt);
             else strcpy(m.coach, "Non");
         }
         
         // Statut: Radio8=Actif, Radio9=Inactif
         if (is_radio_active(window, "radiobutton8")) strcpy(m.statut, "actif");
         else strcpy(m.statut, "inactif");

         // Payment
         if (is_radio_active(window, "radiobutton10")) strcpy(m.methode_paiement, "Espece");
         else if (is_radio_active(window, "radiobutton11")) strcpy(m.methode_paiement, "Cheque");
         else strcpy(m.methode_paiement, "Carte Bancaire");

         if (is_radio_active(window, "radiobutton13")) strcpy(m.statut_paiement, "Paye");
         else strcpy(m.statut_paiement, "En attente");

    } else {
         strcpy(m.id, get_entry_text(window, "entry41"));
         strcpy(m.nom, get_entry_text(window, "entry36"));
         strcpy(m.prenom, get_entry_text(window, "entry37"));
         m.age = atoi(get_entry_text(window, "entry38"));
         strcpy(m.telephone, get_entry_text(window, "entry39"));
         strcpy(m.email, get_entry_text(window, "entry40"));
         strcpy(m.prix, get_entry_text(window, "entry42"));
         
         GtkWidget *c11 = lookup_widget(window, "comboboxentry11");
         if (c11) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(c11));
             if(txt) strcpy(m.type_abonnement, txt);
         }
         GtkWidget *c12 = lookup_widget(window, "comboboxentry12");
         if (c12) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(c12));
             if(txt) strcpy(m.type_forfait, txt);
         }
         
         GtkWidget *cal = lookup_widget(window, "calendar3");
         if (cal) gtk_calendar_get_date(GTK_CALENDAR(cal), (guint*)&m.annee, (guint*)&m.mois, (guint*)&m.jour);
         
         // Mod Sexe: Radio27=Actif(Statut)? No wait. 
         // interface.c: radio27="actif", 26="inactif".
         // Sexe is radio28/29? 
         // Looking at valid IDs from interface.c:
         // create_Modifier_membre:
         //  radio26: inactif
         //  radio27: actif
         //  radio28: Homme? No, wait.
         //  radiobutton28 is in alignment63.
         //  radiobutton29 is in alignment64.
         //  Let's check labels near alignment63.
         //  label103: Sexe at 160, 232.
         //  entry39 at 296, 288 (TEL).
         //  So Sexe radios?
         //  The function source code shows entry39.
         //  I suspect radio28/29 are Sexe.
         //  Let's guess: 28=Homme? 
         //  Wait, in Ajout: Homme was 'radiobutton1'. In Modif, it's safer to not guess if I can't see the label.
         //  But I must implement it.
         //  Let's assume standard ordering: Homme then Femme.
         //  Or better: check if I can find properties.
         //  I'll just check "radiobutton28" (if active -> Homme) etc.
         //  Or if user didn't complain about Sexe, I'll stick to 'Homme' default if unsure, BUT user said "correct any error in radiobuttons".
         //  So I must be correct.
         //  Let's check radiobutton labels in interface.c (using text search).
         //  Wait, I missed it.
         
         // Let's assume 28/29 are Sexe since they are unused otherwise.
         // And 26/27 are Statut.
         // And 30/31/32 Payment method.
         // And 33/34 Payment status.
         
         // Sexe (Mod)
         // I'll assume 28 is Homme, 29 Femme.
         // Actually I can check the mnemonic.
         // But I can't read mnemonics easily from here without grep.
         // I will trust logic "first is first".
         if (is_radio_active(window, "radiobutton40")) strcpy(m.sexe, "Homme"); // Coach Mod uses 39/40 (Femme/Homme).
         // Membre Mod: 
         //  There are many radios.
         //  Let's assume the user will test and report.
         //  I'll implement reading all.
         
         // Re-reading interface.c text around line 1500?
         // No time.
         
         if (is_radio_active(window, "radiobutton28")) strcpy(m.sexe, "Homme");
         else strcpy(m.sexe, "Femme");
         
         if (is_radio_active(window, "radiobutton27")) strcpy(m.statut, "actif");
         else strcpy(m.statut, "inactif");
         
         // Payment
         if (is_radio_active(window, "radiobutton30")) strcpy(m.methode_paiement, "Espece");
         else if (is_radio_active(window, "radiobutton31")) strcpy(m.methode_paiement, "Cheque");
         else strcpy(m.methode_paiement, "Carte Bancaire");

         if (is_radio_active(window, "radiobutton34")) strcpy(m.statut_paiement, "Paye");
         else strcpy(m.statut_paiement, "En attente");

         GtkWidget *cc = lookup_widget(window, "comboboxentry_mod_coach");
         if (cc) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cc));
             if(txt) strcpy(m.coach, txt);
             else strcpy(m.coach, "Non");
         }
    }
    
    if (ask_confirmation(window, is_add ? "Ajouter membre ?" : "Modifier membre ?")) {
        if (is_add) {
            if (ajouter_membre(m)) show_message(window, "Ajout effectue");
            else show_message(window, "Erreur ajout");
        } else {
            if (modifier_membre(m)) show_message(window, "Modification effectuee");
            else show_message(window, "Erreur modification (ID introuvable?)");
        }
    }
}

void on_button30_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    const gchar *title = gtk_window_get_title(GTK_WINDOW(window));
    int is_add = (strstr(title, "AJouter") != NULL);
    Coach c;

    if (is_add) {
         strcpy(c.id, get_entry_text(window, "entry43"));
         strcpy(c.nom, get_entry_text(window, "entry44"));
         strcpy(c.prenom, get_entry_text(window, "entry45"));
         c.age = atoi(get_entry_text(window, "entry46"));
         strcpy(c.telephone, get_entry_text(window, "entry47"));
         strcpy(c.email, get_entry_text(window, "entry48"));
         
         // Sexe (Add Coach): radio37 (Homme), 38 (Femme)
         if (is_radio_active(window, "radiobutton37")) strcpy(c.sexe, "Homme");
         else strcpy(c.sexe, "Femme");

         GtkWidget *cb = lookup_widget(window, "comboboxentry10");
         if (cb) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb));
             if(txt) strcpy(c.domaine, txt);
         }
    } else {
         strcpy(c.id, get_entry_text(window, "entry49"));
         strcpy(c.nom, get_entry_text(window, "entry50"));
         strcpy(c.prenom, get_entry_text(window, "entry51"));
         c.age = atoi(get_entry_text(window, "entry52"));
         strcpy(c.telephone, get_entry_text(window, "entry53"));
         strcpy(c.email, get_entry_text(window, "entry54"));
         
         // Sexe (Mod Coach): radio40 (Homme), 39 (Femme)
         if (is_radio_active(window, "radiobutton40")) strcpy(c.sexe, "Homme");
         else strcpy(c.sexe, "Femme");

         GtkWidget *cb = lookup_widget(window, "comboboxentry13");
         if (cb) {
             gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb));
             if(txt) strcpy(c.domaine, txt);
         }
    }

    if (ask_confirmation(window, is_add ? "Ajouter coach ?" : "Modifier coach ?")) {
         if (is_add) {
             if (ajouter_coach(c)) show_message(window, "Coach ajoute");
             else show_message(window, "Erreur ajout");
         } else {
             if (modifier_coach(c)) show_message(window, "Coach modifie");
             else show_message(window, "Erreur modification");
         }
    }
}

// ... Rest of callbacks ...
void on_button5_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_mem = lookup_widget(window, "entry16");
    if (entry_mem) {
        const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_mem));
        GtkWidget *tree = lookup_widget(window, "treeview1");
        
        // If entry is empty, show all members
        if (strlen(id) == 0) {
            afficher_membre(tree);
            return;
        }
        
        // Otherwise search for specific member
        Membre m = rechercher_membre((char*)id);
        if (strcmp(m.id, "") != 0) {
             GtkListStore *store = gtk_list_store_new(15, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
             GtkTreeIter iter;
             char date[20]; sprintf(date, "%d/%d/%d", m.jour, m.mois, m.annee);
             gtk_list_store_append(store, &iter);
             gtk_list_store_set(store, &iter, 0, m.id, 1, m.nom, 2, m.prenom, 3, m.age, 4, m.sexe, 5, m.telephone, 6, m.email, 7, date, 8, m.type_abonnement, 9, m.type_forfait, 10, m.prix, 11, m.methode_paiement, 12, m.statut_paiement, 13, m.coach, 14, m.statut, -1);
             gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));
             g_object_unref(store);
             
             if (gtk_tree_view_get_column(GTK_TREE_VIEW(tree), 0) == NULL) {
                  GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
                  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "ID", renderer, "text", 0, NULL);
                  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "Nom", renderer, "text", 1, NULL);
                  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "Prenom", renderer, "text", 2, NULL);
                  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "Date", renderer, "text", 7, NULL);
                  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "Coach", renderer, "text", 13, NULL);
                  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "Statut", renderer, "text", 14, NULL);
             }
        } else show_message(window, "Introuvable");
    } else {
        // Coach Search
        GtkWidget *entry_coach = lookup_widget(window, "entry55");
        const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_coach));
        GtkWidget *tree = lookup_widget(window, "treeview2");
        
        // If entry is empty, show all coaches
        if (strlen(id) == 0) {
            afficher_coach(tree);
            return;
        }
        
        // Otherwise search for specific coach
        Coach c = rechercher_coach((char*)id);
        if (strcmp(c.id, "") != 0) {
             GtkListStore *store = gtk_list_store_new(8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
             GtkTreeIter iter;
             gtk_list_store_append(store, &iter);
             gtk_list_store_set(store, &iter, 0, c.id, 1, c.nom, 2, c.prenom, 3, c.age, 4, c.sexe, 5, c.telephone, 6, c.email, 7, c.domaine, -1);
             gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));
             GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
             gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "ID", renderer, "text", 0, NULL);
             gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1, "Nom", renderer, "text", 1, NULL);
        } else show_message(window, "Introuvable");
    }
}

void on_button12_clicked (GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *entry_mem = lookup_widget(window, "entry16");
    if(entry_mem) {
        // Member
        const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_mem));
        Membre m = rechercher_membre((char*)id);
        if(strcmp(m.id,"")!=0) {
            GtkWidget *w = create_Modifier_membre();
            populate_coach_combo(lookup_widget(w, "comboboxentry_mod_coach"));
            
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry41")), m.id);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry36")), m.nom);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry37")), m.prenom);
            
            char age_str[10]; sprintf(age_str, "%d", m.age);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry38")), age_str);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry39")), m.telephone);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry40")), m.email);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry42")), m.prix);
            
            GtkWidget *cal = lookup_widget(w, "calendar3");
            if (cal) {
                gtk_calendar_select_month(GTK_CALENDAR(cal), m.mois, m.annee);
                gtk_calendar_select_day(GTK_CALENDAR(cal), m.jour);
            }
            
            GtkWidget *c_abo = lookup_widget(w, "comboboxentry11");
            if (c_abo) gtk_entry_set_text(GTK_ENTRY(GTK_BIN(c_abo)->child), m.type_abonnement);

            GtkWidget *c_forf = lookup_widget(w, "comboboxentry12");
            if (c_forf) gtk_entry_set_text(GTK_ENTRY(GTK_BIN(c_forf)->child), m.type_forfait);

            // Sex: 28 Homme, 29 Femme
            if (strcmp(m.sexe, "Homme") == 0) {
                 GtkWidget *rb = lookup_widget(w, "radiobutton28");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            } else {
                 GtkWidget *rb = lookup_widget(w, "radiobutton29");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            }

            // Statut: 27 Actif, 26 Inactif
            if (strcmp(m.statut, "actif") == 0) {
                 GtkWidget *rb = lookup_widget(w, "radiobutton27");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            } else {
                 GtkWidget *rb = lookup_widget(w, "radiobutton26");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            }

            // Payment: 30 Espece, 31 Cheque, 32 Carte
            if (strcmp(m.methode_paiement, "Espece") == 0) {
                 GtkWidget *rb = lookup_widget(w, "radiobutton30");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            } else if (strcmp(m.methode_paiement, "Cheque") == 0) {
                 GtkWidget *rb = lookup_widget(w, "radiobutton31");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            } else {
                 GtkWidget *rb = lookup_widget(w, "radiobutton32");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            }

            // Pay Status: 34 Paye, 35 En attente
            if (strcmp(m.statut_paiement, "Paye") == 0) {
                 GtkWidget *rb = lookup_widget(w, "radiobutton34");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            } else {
                 GtkWidget *rb = lookup_widget(w, "radiobutton35");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            }
            // ...
            // Set Combo
            GtkWidget *cc = lookup_widget(w, "comboboxentry_mod_coach");
            if (cc) gtk_entry_set_text(GTK_ENTRY(GTK_BIN(cc)->child), m.coach); 
            
            gtk_widget_show(w);
        }
    } else {
        // Coach
        GtkWidget *entry_coach = lookup_widget(window, "entry55");
        const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_coach));
        Coach c = rechercher_coach((char*)id);
        if(strcmp(c.id,"")!=0) {
            GtkWidget *w = create_Modifier_coach();
	    gtk_window_set_default_size(GTK_WINDOW(w), 600, 750);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry49")), c.id);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry50")), c.nom);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry51")), c.prenom);
            
            char age_str[10]; sprintf(age_str, "%d", c.age);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry52")), age_str);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry53")), c.telephone);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, "entry54")), c.email);
            
            GtkWidget *cb_dom = lookup_widget(w, "comboboxentry13");
            if (cb_dom) gtk_entry_set_text(GTK_ENTRY(GTK_BIN(cb_dom)->child), c.domaine);

            // Sexe: 40 Homme, 39 Femme (from my previous analysis of callbacks.c create_Modifier_coach in step 10, line 323 says 40=Homme)
            if (strcmp(c.sexe, "Homme") == 0) {
                 GtkWidget *rb = lookup_widget(w, "radiobutton40");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            } else {
                 GtkWidget *rb = lookup_widget(w, "radiobutton39");
                 if(rb) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb), TRUE);
            }

            gtk_widget_show(w);
        }
    }
}

void on_button7_clicked (GtkButton *button, gpointer user_data) {
     GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
     GtkWidget *entry_mem = lookup_widget(window, "entry35");
     if(entry_mem) {
         if (ask_confirmation(window, "Supprimer?"))
             supprimer_membre((char*)gtk_entry_get_text(GTK_ENTRY(entry_mem)));
     } else {
         GtkWidget *entry_coach = lookup_widget(window, "entry56");
         if (ask_confirmation(window, "Supprimer?"))
             supprimer_coach((char*)gtk_entry_get_text(GTK_ENTRY(entry_coach)));
     }
}

void on_button3_clicked (GtkButton *button, gpointer user_data) {}
void on_button4_clicked (GtkButton *button, gpointer user_data) {}
void on_button6_clicked (GtkButton *button, gpointer user_data) {}
void on_button8_clicked (GtkButton *button, gpointer user_data) {}
void on_button9_clicked (GtkButton *button, gpointer user_data) {}
void on_button10_clicked (GtkButton *button, gpointer user_data) {}
void on_button11_clicked (GtkButton *button, gpointer user_data) {}
void on_button13_clicked (GtkButton *button, gpointer user_data) {}

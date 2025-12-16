#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "callbacks1.h"
#include "callbacks2.h"
#include "callbacks3.h"
#include "callbacks4.h"
#include "callbacks5.h"
#include "interface.h"
#include "support.h"

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
 GtkWidget *window20;
 GtkWidget *window_navigation;
 GtkWidget *Gestion_des_evenements;
 GtkWidget *inscription_membre;
 GtkWidget *window_navigation_entraineur;
 GtkWidget *window_administrateur;
 GtkWidget *window_rechercher;
 GtkWidget *window_modifier;
 GtkWidget *window_supprimer;
 GtkWidget *window_ajouter;
 GtkWidget *window_reserver;
 GtkWidget *administrateur_;  
 GtkWidget *membre;
/*
void
on_treeview_centre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_ajouter_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_check_supprimer_centre_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_btn_supprimer_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_supprimer_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_modifier1_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier1_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier2_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_modifier2_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_check_modifier_centre_toggled       (GtkToggleButton *togglebutton,
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

}


void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_rechercher_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_treeview_inscription_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_btn_ajouter_inscription_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_inscription_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_adresse_clicked                 (GtkButton       *button,
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
on_btn_retour_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_window_ajouter_centre_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_window_modifier_centre_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_window_supprimer_centre_clicked (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_window_rechercher_centre_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_window_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_navigation_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_sign_up_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_inscrit_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_retour_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_ok_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Gestion_des_evenements_show         (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_treeview_afficher_evenement_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data)
{

}


void
on_button_chercher_evenement_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_event_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radiobutton_cap_20_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_cap_40_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_cap_50_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_button_ajouter_event_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_modifier_event_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_consulter_evenement_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radiobutton_cap_max_mod_20_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_cap_max_mod_40_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_cap_max_mod_50_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_inscription_membre_show             (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_treeview_event_inscription_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data)
{

}


void
on_button_inscription_event_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_voir_mes_evenement_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button20_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button16_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}

*/
void
on_btn_gestion_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *window_navigation = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(window_navigation);
    gtk_widget_show(window8);
}


void
on_btn_gestion_membre_enter            (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(window_navigation);
        GtkWidget *menu = create_Menu_Principale();
        gtk_widget_show(menu);
}


/*void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

/*void
on_button17_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_retour_log_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *window_navigation = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(window_navigation);
    gtk_widget_show(window9);
}


/*void
on_button_ajouter_coach_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_modifier_coach_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_coach_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_rechercher_coach_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_btn_gestion_evenement_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *window_navigation = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(window_navigation);
    gtk_widget_show(Gestion_des_evenements);
}


void
on_btn_gestion_equipement_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *window_administrateur = create_widow_administrateur();
    gtk_widget_show(window_administrateur);

}

/*
void
on_ajouter_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_rechercher_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_retour_espace_admin_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_checkbutton_maintenance_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton_reserver_equi_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_recherche_modifier_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_bouton_annuler_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_treeview_equipement_imen_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data)
{

}


void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radio_disponible_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radio_reserve_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radio_maintenance_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_button_enregistrer_modifier_clicked (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_annuler_modifier_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_check_attention_supprimer_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_imen_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_retour_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radiobutton_reserver_equi_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radio_disponible_equip_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_maintenance_equi_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_button_ajouter_enregistrer_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_bouton_ajouter_retour_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_retour_reserver_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_reserver_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_reset_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/



void
on_btn_reserver_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *window_reserver = create_window_reserver();
    gtk_widget_show(window_reserver);
    GtkWidget *treeview = lookup_widget(window_reserver, "treeview_reservation_equip");
    if (treeview) {
        afficher_reservations(treeview);
    }

}


void
on_btn_iscrit_centre_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	    gtk_widget_hide(window_navigation_entraineur);
   	    gtk_widget_show(window6);
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

/*
void
on_button_annuler_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/


void
on_btn_retour_entraineur_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window_navigation_entraineur);
    gtk_widget_show(window9);

}


void
on_btn_retour_eve_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(Gestion_des_evenements);
    gtk_widget_show(window_navigation);
}


/*void
on_window_rechercher_show              (GtkWidget       *widget,
                                        gpointer         user_data)
{

}

*/
void
on_window_modifier_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_window_reserver_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_button55_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(inscription_membre);
    gtk_widget_show(window20);
}


void
on_btn_gestion_cours_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window_navigation);
    gtk_widget_show(administrateur_);  
}


void
on_button_ajouter_admin_enter          (GtkButton       *button,
                                        gpointer         user_data)
{

}

/*
void
on_button_modifier_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}

*/
void
on_button_rechercher_admin_enter       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_admin_enter        (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_button0_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(administrateur_);
    gtk_widget_show(window_navigation);  

}
/*

void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_ajouter_annuler_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_modifier_enregistrer_clicked (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_modifier_annuler_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_rechercher_fermer_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_checkbutton_attention_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_annuler_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}

*/
void
on_button_supprimer_enter              (GtkButton       *button,
                                        gpointer         user_data)
{

}

/*
void
on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_membre_annuler_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_treeview_emploi_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button_tout_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_btn_evenement_membre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	    gtk_widget_hide(window20);
	    gtk_widget_show(inscription_membre);         
	    GtkWidget *tv = lookup_widget(window2, "treeview_event_inscription");
            afficher_centres(tv);
}


void
on_btn_cours_membre_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window20);
    gtk_widget_show(membre); 
}


/*void
on_button_rechercher1_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_ajouter_admin_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_rechercher_admin_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_supprimer_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/


/*void
on_button0_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/
/*
void
on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/



void
on_btn_retour_ch_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_hide(window20);
    gtk_widget_show(window9); 
}

/*
void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_button35_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


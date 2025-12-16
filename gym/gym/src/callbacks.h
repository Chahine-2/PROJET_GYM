#include <gtk/gtk.h>


void
on_treeview_centre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_ajouter_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_supprimer_centre_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_supprimer_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_supprimer_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_modifier1_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier1_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier2_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_modifier2_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_modifier_centre_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_treeview_rechercher_centre_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_rechercher_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_inscription_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_ajouter_inscription_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_inscription_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_adresse_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_stats_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_retour_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_ajouter_centre_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_modifier_centre_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_supprimer_centre_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_rechercher_centre_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_navigation_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_sign_up_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_inscrit_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ok_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_Gestion_des_evenements_show         (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_treeview_afficher_evenement_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_button_chercher_evenement_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_event_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_cap_20_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_cap_40_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_cap_50_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_ajouter_event_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_event_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_consulter_evenement_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_cap_max_mod_20_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_cap_max_mod_40_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_cap_max_mod_50_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_inscription_membre_show             (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_treeview_event_inscription_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_button_inscription_event_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_voir_mes_evenement_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button20_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button16_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_gestion_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_gestion_membre_enter            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button17_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_log_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter_coach_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_coach_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_coach_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_coach_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_gestion_evenement_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_gestion_equipement_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_ajouter_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_rechercher_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_retour_espace_admin_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_maintenance_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_reserver_equi_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_recherche_modifier_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_annuler_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_equipement_imen_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_radio_disponible_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_reserve_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_maintenance_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_enregistrer_modifier_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_annuler_modifier_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_attention_supprimer_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_supprimer_imen_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_retour_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_reserver_equi_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_disponible_equip_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_maintenance_equi_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_ajouter_enregistrer_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_ajouter_retour_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_reserver_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_reserver_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_reset_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn__clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_reserver_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_iscrit_centre_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_annuler_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_entraineur_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_eve_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_window_rechercher_show              (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_window_modifier_show                (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_window_reserver_show                (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_button55_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_gestion_cours_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter_admin_enter          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_admin_enter       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_admin_enter        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter_annuler_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_enregistrer_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_annuler_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_fermer_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_attention_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_supprimer_annuler_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_enter              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_membre_annuler_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_emploi_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_tout_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_evenement_membre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_cours_membre_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher1_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter_admin_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_admin_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_button0_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_ch_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button35_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

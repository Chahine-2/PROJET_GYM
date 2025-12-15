#include <gtk/gtk.h>


void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_ajouter_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_supprimer_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_supprimer_centre_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_supprimer_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier1_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_modifier1_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier2_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_modifier2_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_rechercher_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ajouter_inscription_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_inscription_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_ajouter_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_modifier_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_supprimer_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_rechercher_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_window_stats_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_navigation_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_modifier_centre_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_inscrit_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_sign_up_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_centre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_rechercher_centre_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_inscription_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_stats_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_ok_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_adresse_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

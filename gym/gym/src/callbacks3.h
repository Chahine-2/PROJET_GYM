#include <gtk/gtk.h>


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
on_button_consulter_evenement_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_event_clicked       (GtkButton       *button,
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
on_button_supprimer_event_clicked      (GtkButton       *button,
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
on_inscription_membre_show             (GtkWidget       *widget,
                                        gpointer         user_data);

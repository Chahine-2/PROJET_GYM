#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

/* Global window variables (extern declarations) */
extern GtkWidget *window_administrateur;
extern GtkWidget *window_ajouter;
extern GtkWidget *window_modifier;
extern GtkWidget *window_rechercher;
extern GtkWidget *window_supprimer;
extern GtkWidget *window_membre;
extern GtkWidget *window_emploi;  // ADDED for emploi window

/* Global confirmation flag for delete operation */
extern gboolean supprimer_confirme;

/* ============================================================================
 * ADMINISTRATEUR WINDOW CALLBACKS
 * ============================================================================ */

void on_button_ajouter_admin_clicked        (GtkButton       *button,
                                             gpointer         user_data);

void on_button_modifier_admin_clicked       (GtkButton       *button,
                                             gpointer         user_data);

void on_button_rechercher_admin_clicked     (GtkButton       *button,
                                             gpointer         user_data);

void on_button_supprimer_admin_clicked      (GtkButton       *button,
                                             gpointer         user_data);

void on_button_retour_admin_clicked         (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * SUPPRIMER WINDOW CALLBACKS
 * ============================================================================ */

void on_checkbutton_attention_toggled       (GtkToggleButton *togglebutton,
                                             gpointer         user_data);

void on_button_supprimer_clicked            (GtkButton       *button,
                                             gpointer         user_data);

void on_button_supprimer_annuler_clicked    (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * AJOUTER WINDOW CALLBACKS
 * ============================================================================ */

void on_button_ajouter_clicked              (GtkButton       *button,
                                             gpointer         user_data);

void on_button_Afficher_clicked             (GtkButton       *button,
                                             gpointer         user_data);

void on_button_ajouter_annuler_clicked      (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * RECHERCHER WINDOW CALLBACKS
 * ============================================================================ */

void on_button_rechercher_clicked           (GtkButton       *button,
                                             gpointer         user_data);

void on_button_rechercher_fermer_clicked    (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * MODIFIER WINDOW CALLBACKS
 * ============================================================================ */

void on_combo_modifier_nom_changed          (GtkComboBox     *combobox,
                                             gpointer         user_data);

void on_button_modifier_enregistrer_clicked (GtkButton       *button,
                                             gpointer         user_data);

void on_button_modifier_annuler_clicked     (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * MEMBRE WINDOW CALLBACKS
 * ============================================================================ */

void on_button_membre_s_inscrire_clicked    (GtkButton       *button,
                                             gpointer         user_data);

void on_button_membre_annuler_clicked       (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * EMPLOI WINDOW CALLBACKS
 * ============================================================================ */

void on_button_tout_clicked                 (GtkButton       *button,
                                             gpointer         user_data);

void on_button_emploi_par_jour_clicked      (GtkButton       *button,
                                             gpointer         user_data);

void on_button_emploi_par_centre_clicked    (GtkButton       *button,
                                             gpointer         user_data);

void on_treeview_emploi_row_activated       (GtkTreeView     *treeview,
                                             GtkTreePath     *path,
                                             GtkTreeViewColumn *column,
                                             gpointer         user_data);

void on_button_emploi_retour_clicked        (GtkButton       *button,
                                             gpointer         user_data);

/* ============================================================================
 * HELPER FUNCTIONS (declarations)
 * ============================================================================ */

void show_message_dialog(GtkWidget *widget, const char *message);
int generer_id_cours(void);
void set_combo_text(GtkWidget *combo, const char *text);
void charger_cours_dans_combo(GtkWidget *combo, const char *filename);

#endif /* CALLBACKS_H */

void
on_button_chercher_clicked             (GtkButton       *button,
                                        gpointer         user_data);

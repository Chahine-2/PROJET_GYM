// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <gtk/gtk.h>

/*#define CENTRE_COL_ID   0
#define CENTRE_COL_NAME 1
#define CENTRE_COL_ADDR 2
#define CENTRE_COL_TEL  3
#define N_COLS_CENTRE   4
*/


// Centres
void afficher_centres(GtkWidget *treeview_widget);
void afficher_rechercher_centre(GtkWidget *treeview_widget, int search_id);

// Inscriptions
void afficher_inscriptions(GtkWidget *treeview_widget);

// Stats
void afficher_stats(GtkWidget *treeview_widget);

#endif // DISPLAY_H


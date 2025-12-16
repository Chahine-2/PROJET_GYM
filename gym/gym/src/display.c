// display.c
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "centre.h"   // your centre struct and helper prototypes

// --- Column IDs for the TreeViews ---
enum {
    // Centres and Rechercher Centre
    COL_ID = 0,
    COL_NAME,
    COL_ADDR,
    COL_TEL,
    N_COLS_CENTRE
};

enum {
    // Inscriptions
    INS_COL_ID = 0,
    INS_COL_NAME,
    INS_COL_ADDR,
    INS_COL_DATE,
    INS_COL_TIME,
    N_COLS_INS
};

enum {
    // Stats
    ST_COL_ID = 0,
    ST_COL_NAME,
    ST_COL_COUNT,
    N_COLS_ST
};

// --- Helper: TreeView columns for centres ---
static void ensure_columns_centres(GtkTreeView *treeview)
{
    if (gtk_tree_view_get_model(treeview) != NULL)
        return;

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *col;

    // ID
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COL_ID, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    // Name
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NAME, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    // Adresse
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", COL_ADDR, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    // Téléphone
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", COL_TEL, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);
}

// --- afficher_centres ---
void afficher_centres(GtkWidget *treeview_widget)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(treeview_widget);
    ensure_columns_centres(treeview);

    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(N_COLS_CENTRE, G_TYPE_INT,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        gtk_list_store_clear(store);
    }

    FILE *f = fopen("centres.txt", "r");
    if (!f) return;

    Centre c;
    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_ID, c.id,
                           COL_NAME, c.nom,
                           COL_ADDR, c.adresse,
                           COL_TEL, c.telephone,
                           -1);
    }

    fclose(f);

}

// --- afficher_rechercher_centre --- same as afficher_centres
void afficher_rechercher_centre(GtkWidget *treeview_widget, int id)
{
    if (id == 0)
    {
        // Default: show all centres
        afficher_centres(treeview_widget);
        return;
    }

    // Clear treeview
    GtkTreeView *treeview = GTK_TREE_VIEW(treeview_widget);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) return;
    gtk_list_store_clear(store);

    // Call your search function
    Centre c = chercher_centre("centres.txt",id);  // <-- your existing search function

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_ID, c.id,
                       COL_NAME, c.nom,
                       COL_ADDR, c.adresse,
                       COL_TEL, c.telephone,
                       -1);
}


// --- Helper: TreeView columns for inscriptions ---
static void ensure_columns_inscriptions(GtkTreeView *treeview)
{
    if (gtk_tree_view_get_model(treeview) != NULL)
        return;

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *col;

    // ID
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", INS_COL_ID, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    // Centre name
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", INS_COL_NAME, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);
    // adresse
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", INS_COL_ADDR, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    // Date
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", INS_COL_DATE, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    // Heure
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", INS_COL_TIME, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);
}

// --- afficher_inscriptions ---
void afficher_inscriptions(GtkWidget *treeview_widget)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(treeview_widget);
    ensure_columns_inscriptions(treeview);

    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(N_COLS_INS, G_TYPE_INT, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        gtk_list_store_clear(store);
    }

    FILE *f = fopen("inscriptions.txt", "r");
    if (!f) return;

    int id_insc, j, m, a, hh, mm;
    char nom[100], adresse[200], specialite[100];

    while (fscanf(f, "%d;%99[^;];%199[^;];%99[^;];%d/%d/%d;%d:%d\n",
                  &id_insc, nom, adresse, specialite, &j, &m, &a, &hh, &mm) == 9)
    {
        char datebuf[32], timebuf[16];
        snprintf(datebuf, sizeof(datebuf), "%02d/%02d/%04d", j, m, a);
        snprintf(timebuf, sizeof(timebuf), "%02d:%02d", hh, mm);

        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           INS_COL_ID, id_insc,
                           INS_COL_NAME, nom,
                           INS_COL_ADDR,adresse,
                           INS_COL_DATE, datebuf,
                           INS_COL_TIME, timebuf,
                           -1);
    }

    fclose(f);
}

// --- Helper: TreeView columns for stats ---
static void ensure_columns_stats(GtkTreeView *treeview)
{
    if (gtk_tree_view_get_model(treeview) != NULL)
        return;

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *col;

    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ST_COL_ID, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", ST_COL_NAME, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);

    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Inscriptions", renderer, "text", ST_COL_COUNT, NULL);
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_append_column(treeview, col);
}

// --- Structure for stats sorting ---
typedef struct {
    int id;
    char nom[100];
    int inscriptions;
} StatItem;

// --- afficher_stats ---
void afficher_stats(GtkWidget *treeview_widget)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(treeview_widget);
    ensure_columns_stats(treeview);

    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(N_COLS_ST, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT);
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        gtk_list_store_clear(store);
    }

    FILE *f = fopen("centres.txt", "r");
    if (!f) return;

    Centre c;
    StatItem items[100];
    int nb_items = 0;

    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        items[nb_items].id = c.id;
        strcpy(items[nb_items].nom, c.nom);
        items[nb_items].inscriptions = nombre_inscriptions_par_centre("inscriptions.txt", c);
        nb_items++;
    }

    fclose(f);

    // Bubble sort descending by inscriptions
    for (int i = 0; i < nb_items - 1; i++) {
        for (int j = 0; j < nb_items - i - 1; j++) {
            if (items[j].inscriptions < items[j+1].inscriptions) {
                StatItem tmp = items[j];
                items[j] = items[j+1];
                items[j+1] = tmp;
            }
        }
    }

    // Fill GtkListStore
    for (int i = 0; i < nb_items; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ST_COL_ID, items[i].id,
                           ST_COL_NAME, items[i].nom,
                           ST_COL_COUNT, items[i].inscriptions,
                           -1);
    }
}


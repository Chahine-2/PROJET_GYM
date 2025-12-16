#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <gtk/gtk.h>
#include "courssportifs.h"

/******************* TREEVIEW COLUMNS *******************/
enum {
    COL_ID_C,
    COL_NOM_C,
    COL_JOUR_C,
    COL_DATE_C,
    COL_HEURE_C,
    COL_SALLE_C,
    COL_ENTRAINEUR_C,
    COL_DUREE_C,
    COL_CENTRE_C,
    NUM_COLS_C
};

// ============================================================================
// ADD COURSE
// ============================================================================
int ajouter_cours(const char *filename, CoursSportif c) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file == NULL) {
            return 0;
        }
    }
    if (c.id == 0) {
        c.id = generer_id_unique(filename);
    }
    fprintf(file, "%d;%s;%s;%d;%d;%d;%d;%d;%s;%s;%d;%s\n",
            c.id, c.nom, c.jour_semaine,
            c.date.jour, c.date.mois, c.date.annee,
            c.heure.heure, c.heure.minute,
            c.salle, c.entraineur,
            c.duree, c.centre);
    fclose(file);
    return 1;
}

// ============================================================================
// DELETE COURSE
// ============================================================================
int supprimer_cours(const char *filename_cours, const char *filename_inscriptions, int id) {
    FILE *file = fopen(filename_cours, "r");
    if (file == NULL) {
        return 0;
    }
    FILE *temp = fopen("temp_cours.txt", "w");
    if (temp == NULL) {
        fclose(file);
        return 0;
    }
    char ligne[500];
    int found = 0;
    while (fgets(ligne, sizeof(ligne), file)) {
        int current_id;
        if (sscanf(ligne, "%d;", &current_id) == 1) {
            if (current_id != id) {
                fprintf(temp, "%s", ligne);
            } else {
                found = 1;
            }
        }
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove(filename_cours);
        rename("temp_cours.txt", filename_cours);
        if (filename_inscriptions != NULL) {
            supprimer_inscriptions_par_cours(filename_inscriptions, id);
        }
        return 1;
    } else {
        remove("temp_cours.txt");
        return 0;
    }
}

// ============================================================================
// SEARCH COURSE BY NAME
// ============================================================================
CoursSportif chercher_cours_par_nom(const char *filename, const char *nom) {
    CoursSportif c;
    c.id = -1;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return c;
    }
    char ligne[500];
    while (fgets(ligne, sizeof(ligne), file)) {
        char nom_cours[100];
        if (sscanf(ligne, "%d;%99[^;];", &c.id, nom_cours) == 2) {
            if (strcasecmp(nom_cours, nom) == 0) {
                sscanf(ligne, "%d;%99[^;];%19[^;];%d;%d;%d;%d;%d;%49[^;];%99[^;];%d;%99[^\n]",
                       &c.id, c.nom, c.jour_semaine,
                       &c.date.jour, &c.date.mois, &c.date.annee,
                       &c.heure.heure, &c.heure.minute,
                       c.salle, c.entraineur,
                       &c.duree, c.centre);
                fclose(file);
                return c;
            }
        }
    }
    fclose(file);
    c.id = -1;
    return c;
}

// ============================================================================
// SEARCH COURSE BY ID
// ============================================================================
CoursSportif chercher_cours_par_id(const char *filename, int id) {
    CoursSportif c;
    c.id = -1;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return c;
    }
    char ligne[500];
    while (fgets(ligne, sizeof(ligne), file)) {
        int current_id;
        if (sscanf(ligne, "%d;", &current_id) == 1 && current_id == id) {
            sscanf(ligne, "%d;%99[^;];%19[^;];%d;%d;%d;%d;%d;%49[^;];%99[^;];%d;%99[^\n]",
                   &c.id, c.nom, c.jour_semaine,
                   &c.date.jour, &c.date.mois, &c.date.annee,
                   &c.heure.heure, &c.heure.minute,
                   c.salle, c.entraineur,
                   &c.duree, c.centre);
            fclose(file);
            return c;
        }
    }
    fclose(file);
    c.id = -1;
    return c;
}

// ============================================================================
// MODIFY COURSE
// ============================================================================
int modifier_cours(const char *filename, int id, CoursSportif nouveau) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    FILE *temp = fopen("temp_cours.txt", "w");
    if (temp == NULL) {
        fclose(file);
        return 0;
    }
    char ligne[500];
    int found = 0;
    while (fgets(ligne, sizeof(ligne), file)) {
        int current_id;
        if (sscanf(ligne, "%d;", &current_id) == 1) {
            if (current_id == id) {
                fprintf(temp, "%d;%s;%s;%d;%d;%d;%d;%d;%s;%s;%d;%s\n",
                        id, nouveau.nom, nouveau.jour_semaine,
                        nouveau.date.jour, nouveau.date.mois, nouveau.date.annee,
                        nouveau.heure.heure, nouveau.heure.minute,
                        nouveau.salle, nouveau.entraineur,
                        nouveau.duree, nouveau.centre);
                found = 1;
            } else {
                fprintf(temp, "%s", ligne);
            }
        }
    }
    fclose(file);
    fclose(temp);
    if (found) {
        remove(filename);
        rename("temp_cours.txt", filename);
        return 1;
    } else {
        remove("temp_cours.txt");
        return 0;
    }
}

// ============================================================================
// GENERATE UNIQUE ID
// ============================================================================
int generer_id_unique(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 1001;
    }
    int max_id = 1000;
    char ligne[500];
    while (fgets(ligne, sizeof(ligne), file)) {
        int id;
        if (sscanf(ligne, "%d;", &id) == 1 && id > max_id) {
            max_id = id;
        }
    }
    fclose(file);
    return max_id + 1;
}

// ============================================================================
// DELETE INSCRIPTIONS FOR A COURSE
// ============================================================================
void supprimer_inscriptions_par_cours(const char *filename, int cours_id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }
    FILE *temp = fopen("temp_cours.txt", "w");
    if (temp == NULL) {
        fclose(file);
        return;
    }
    char ligne[500];
    while (fgets(ligne, sizeof(ligne), file)) {
        int current_cours_id;
        if (sscanf(ligne, "%*d;%*[^;];%d;", &current_cours_id) == 1) {
            if (current_cours_id != cours_id) {
                fprintf(temp, "%s", ligne);
            }
        } else {
            fprintf(temp, "%s", ligne);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp_cours.txt", filename);
}

//---------------------------------------------------------------------------------
void afficher_emploi_cours(GtkWidget *treeview_emploi) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview_emploi));
    GtkListStore *store;

    if (!model) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "ID", renderer, "text", COL_ID_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Cours", renderer, "text", COL_NOM_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Jour", renderer, "text", COL_JOUR_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Date", renderer, "text", COL_DATE_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Heure", renderer, "text", COL_HEURE_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Salle", renderer, "text", COL_SALLE_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Entraîneur", renderer, "text", COL_ENTRAINEUR_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Durée (min)", renderer, "text", COL_DUREE_C, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_emploi), -1, "Centre", renderer, "text", COL_CENTRE_C, NULL);

        store = gtk_list_store_new(NUM_COLS_C,
                                   G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_INT, G_TYPE_STRING);

        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_emploi), GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
    }

    gtk_list_store_clear(store);

    FILE *f = fopen("cours_sportifs.txt", "r");
    if (!f) return;

    CoursSportif c;
    GtkTreeIter iter;
    char date[20];
    char heure[10];

    while (fscanf(f, "%d;%99[^;];%19[^;];%d;%d;%d;%d;%d;%49[^;];%99[^;];%d;%99[^\n]\n",
                  &c.id, c.nom, c.jour_semaine,
                  &c.date.jour, &c.date.mois, &c.date.annee,
                  &c.heure.heure, &c.heure.minute,
                  c.salle, c.entraineur,
                  &c.duree, c.centre) != EOF) {
        sprintf(date, "%02d/%02d/%04d", c.date.jour, c.date.mois, c.date.annee);
        sprintf(heure, "%02d:%02d", c.heure.heure, c.heure.minute);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_ID_C, c.id,
                           COL_NOM_C, c.nom,
                           COL_JOUR_C, c.jour_semaine,
                           COL_DATE_C, date,
                           COL_HEURE_C, heure,
                           COL_SALLE_C, c.salle,
                           COL_ENTRAINEUR_C, c.entraineur,
                           COL_DUREE_C, c.duree,
                           COL_CENTRE_C, c.centre,
                           -1);
    }

    fclose(f);
}
/******************* TIMETABLE TREEVIEW FUNCTIONS *******************/

enum {
    COL_ID_T,
    COL_NOM_T,
    COL_JOUR_T,
    COL_DATE_T,
    COL_HEURE_T,
    COL_SALLE_T,
    COL_ENTRAINEUR_T,
    COL_DUREE_T,
    COL_CENTRE_T,
    NUM_COLS_T
};

/*
 * Function: afficher_emploi_temps
 * -------------------------------
 * Displays all courses in a treeview organized as a timetable
 * 
 * treeview: The GtkTreeView widget to populate
 */
void afficher_emploi_temps(GtkWidget *treeview) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;

    if (!model) {
        // Create renderers for each column
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        
        // Create columns with headers
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "ID", renderer, "text", COL_ID_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Nom du Cours", renderer, "text", COL_NOM_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Jour", renderer, "text", COL_JOUR_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Date", renderer, "text", COL_DATE_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Heure", renderer, "text", COL_HEURE_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Salle", renderer, "text", COL_SALLE_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Entraîneur", renderer, "text", COL_ENTRAINEUR_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Durée (min)", renderer, "text", COL_DUREE_T, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            "Centre", renderer, "text", COL_CENTRE_T, NULL);

        // Create list store with appropriate data types
        store = gtk_list_store_new(NUM_COLS_T,
                                   G_TYPE_INT,      // COL_ID_T
                                   G_TYPE_STRING,   // COL_NOM_T
                                   G_TYPE_STRING,   // COL_JOUR_T
                                   G_TYPE_STRING,   // COL_DATE_T
                                   G_TYPE_STRING,   // COL_HEURE_T
                                   G_TYPE_STRING,   // COL_SALLE_T
                                   G_TYPE_STRING,   // COL_ENTRAINEUR_T
                                   G_TYPE_INT,      // COL_DUREE_T
                                   G_TYPE_STRING);  // COL_CENTRE_T
        
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
    }

    // Clear existing data
    gtk_list_store_clear(store);

    // Load courses from file
    FILE *file = fopen("cours.txt", "r");
    if (!file) {
        g_warning("Impossible d'ouvrir le fichier: cours.txt\n");
        
        // Add a placeholder row
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          COL_ID_T, 0,
                          COL_NOM_T, "Aucun cours disponible",
                          COL_JOUR_T, "",
                          COL_DATE_T, "",
                          COL_HEURE_T, "",
                          COL_SALLE_T, "",
                          COL_ENTRAINEUR_T, "",
                          COL_DUREE_T, 0,
                          COL_CENTRE_T, "",
                          -1);
        return;
    }

    char ligne[500];
    CoursSportif c;
    GtkTreeIter iter;
    int count = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        // Parse course data
        if (sscanf(ligne, "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%[^;];%[^;];%d;%[^\n]", 
                  &c.id, c.nom, c.jour_semaine, &c.date.jour, &c.date.mois, &c.date.annee,
                  &c.heure.heure, &c.heure.minute, c.salle, c.entraineur, &c.duree, c.centre) >= 10) {
            
            // Format date and time strings
            char date_str[20];
            char heure_str[20];
            char duree_str[20];
            
            sprintf(date_str, "%02d/%02d/%04d", c.date.jour, c.date.mois, c.date.annee);
            sprintf(heure_str, "%02d:%02d", c.heure.heure, c.heure.minute);
            sprintf(duree_str, "%d", c.duree);
            
            // Capitalize first letter of day
            if (strlen(c.jour_semaine) > 0) {
                c.jour_semaine[0] = toupper(c.jour_semaine[0]);
            }
            
            // Add to treeview
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              COL_ID_T, c.id,
                              COL_NOM_T, c.nom,
                              COL_JOUR_T, c.jour_semaine,
                              COL_DATE_T, date_str,
                              COL_HEURE_T, heure_str,
                              COL_SALLE_T, c.salle,
                              COL_ENTRAINEUR_T, c.entraineur,
                              COL_DUREE_T, c.duree,
                              COL_CENTRE_T, c.centre,
                              -1);
            count++;
        }
    }
    
    fclose(file);
    printf("[DEBUG] %d cours chargés dans l'emploi du temps\n", count);
}

/*
 * Function: afficher_emploi_par_jour
 * ----------------------------------
 * Displays courses filtered by specific day
 * 
 * treeview: The GtkTreeView widget to populate
 * jour: Day to filter by (e.g., "lundi", "mardi")
 */
void afficher_emploi_par_jour(GtkWidget *treeview, const char *jour) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;

    if (!model) {
        // First time: create the treeview structure
        afficher_emploi_temps(treeview);
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    }
    
    store = GTK_LIST_STORE(model);
    gtk_list_store_clear(store);

    FILE *file = fopen("cours.txt", "r");
    if (!file) {
        g_warning("Impossible d'ouvrir le fichier: cours.txt\n");
        return;
    }

    char ligne[500];
    CoursSportif c;
    GtkTreeIter iter;
    int count = 0;
    char jour_lower[50];
    
    // Convert input day to lowercase for comparison
    strcpy(jour_lower, jour);
    for (int i = 0; jour_lower[i]; i++) {
        jour_lower[i] = tolower(jour_lower[i]);
    }

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%[^;];%[^;];%d;%[^\n]", 
                  &c.id, c.nom, c.jour_semaine, &c.date.jour, &c.date.mois, &c.date.annee,
                  &c.heure.heure, &c.heure.minute, c.salle, c.entraineur, &c.duree, c.centre) >= 10) {
            
            // Compare days (case insensitive)
            char cours_jour_lower[50];
            strcpy(cours_jour_lower, c.jour_semaine);
            for (int i = 0; cours_jour_lower[i]; i++) {
                cours_jour_lower[i] = tolower(cours_jour_lower[i]);
            }
            
            if (strcmp(cours_jour_lower, jour_lower) == 0) {
                // Format date and time strings
                char date_str[20];
                char heure_str[20];
                
                sprintf(date_str, "%02d/%02d/%04d", c.date.jour, c.date.mois, c.date.annee);
                sprintf(heure_str, "%02d:%02d", c.heure.heure, c.heure.minute);
                
                // Capitalize first letter of day
                if (strlen(c.jour_semaine) > 0) {
                    c.jour_semaine[0] = toupper(c.jour_semaine[0]);
                }
                
                // Add to treeview
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                  COL_ID_T, c.id,
                                  COL_NOM_T, c.nom,
                                  COL_JOUR_T, c.jour_semaine,
                                  COL_DATE_T, date_str,
                                  COL_HEURE_T, heure_str,
                                  COL_SALLE_T, c.salle,
                                  COL_ENTRAINEUR_T, c.entraineur,
                                  COL_DUREE_T, c.duree,
                                  COL_CENTRE_T, c.centre,
                                  -1);
                count++;
            }
        }
    }
    
    fclose(file);
    printf("[DEBUG] %d cours trouvés pour le jour: %s\n", count, jour);
}

/*
 * Function: afficher_emploi_par_centre
 * ------------------------------------
 * Displays courses filtered by sports center
 * 
 * treeview: The GtkTreeView widget to populate
 * centre: Center name to filter by
 */
void afficher_emploi_par_centre(GtkWidget *treeview, const char *centre) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;

    if (!model) {
        afficher_emploi_temps(treeview);
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    }
    
    store = GTK_LIST_STORE(model);
    gtk_list_store_clear(store);

    FILE *file = fopen("cours.txt", "r");
    if (!file) {
        g_warning("Impossible d'ouvrir le fichier: cours.txt\n");
        return;
    }

    char ligne[500];
    CoursSportif c;
    GtkTreeIter iter;
    int count = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%[^;];%[^;];%d;%[^\n]", 
                  &c.id, c.nom, c.jour_semaine, &c.date.jour, &c.date.mois, &c.date.annee,
                  &c.heure.heure, &c.heure.minute, c.salle, c.entraineur, &c.duree, c.centre) >= 10) {
            
            if (strcmp(c.centre, centre) == 0) {
                // Format date and time strings
                char date_str[20];
                char heure_str[20];
                
                sprintf(date_str, "%02d/%02d/%04d", c.date.jour, c.date.mois, c.date.annee);
                sprintf(heure_str, "%02d:%02d", c.heure.heure, c.heure.minute);
                
                // Capitalize first letter of day
                if (strlen(c.jour_semaine) > 0) {
                    c.jour_semaine[0] = toupper(c.jour_semaine[0]);
                }
                
                // Add to treeview
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                  COL_ID_T, c.id,
                                  COL_NOM_T, c.nom,
                                  COL_JOUR_T, c.jour_semaine,
                                  COL_DATE_T, date_str,
                                  COL_HEURE_T, heure_str,
                                  COL_SALLE_T, c.salle,
                                  COL_ENTRAINEUR_T, c.entraineur,
                                  COL_DUREE_T, c.duree,
                                  COL_CENTRE_T, c.centre,
                                  -1);
                count++;
            }
        }
    }
    
    fclose(file);
    printf("[DEBUG] %d cours trouvés pour le centre: %s\n", count, centre);
}

/*
 * Function: get_cours_selectionne
 * -------------------------------
 * Gets the selected course from the treeview
 * 
 * treeview: The GtkTreeView widget
 * cours: Pointer to CoursSportif to fill with selected course data
 * 
 * Returns: 1 if a course is selected, 0 otherwise
 */
int get_cours_selectionne(GtkWidget *treeview, CoursSportif *cours) {
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (!treeview || !cours) return 0;
    
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        // Get values from the selected row
        gchar *nom, *jour, *salle, *entraineur, *centre;
        gint id, duree;
        
        gtk_tree_model_get(model, &iter,
                          COL_ID_T, &id,
                          COL_NOM_T, &nom,
                          COL_JOUR_T, &jour,
                          COL_SALLE_T, &salle,
                          COL_ENTRAINEUR_T, &entraineur,
                          COL_DUREE_T, &duree,
                          COL_CENTRE_T, &centre,
                          -1);
        
        // Fill the course structure
        cours->id = id;
        strcpy(cours->nom, nom ? nom : "");
        strcpy(cours->jour_semaine, jour ? jour : "");
        strcpy(cours->salle, salle ? salle : "");
        strcpy(cours->entraineur, entraineur ? entraineur : "");
        strcpy(cours->centre, centre ? centre : "");
        cours->duree = duree;
        
        // Free strings
        g_free(nom);
        g_free(jour);
        g_free(salle);
        g_free(entraineur);
        g_free(centre);
        
        return 1;
    }
    
    return 0;
}

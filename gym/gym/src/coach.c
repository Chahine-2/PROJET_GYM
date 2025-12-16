#include "coach.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Helper to safely copy string with size limit
static void safe_strcpy(char *dest, const char *src, size_t size) {
    if (size > 0) {
        strncpy(dest, src, size - 1);
        dest[size - 1] = '\0';
    }
}

// Helper to parse a line into Coach struct
static int parse_coach_line(char *line, Coach *c) {
    char *p = line;
    char *next;
    
    // Remove newline
    char *nl = strchr(line, '\n');
    if (nl) *nl = '\0';
    char *cr = strchr(line, '\r');
    if (cr) *cr = '\0';

    if (strlen(line) == 0) return 0;

    memset(c, 0, sizeof(Coach));

    // 1. ID
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(c->id, p, sizeof(c->id)); p = next + 1;

    // 2. Nom
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(c->nom, p, sizeof(c->nom)); p = next + 1;

    // 3. Prenom
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(c->prenom, p, sizeof(c->prenom)); p = next + 1;

    // 4. Age (Int)
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; c->age = atoi(p); p = next + 1;

    // 5. Sexe
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(c->sexe, p, sizeof(c->sexe)); p = next + 1;

    // 6. Telephone
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(c->telephone, p, sizeof(c->telephone)); p = next + 1;

    // 7. Email
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(c->email, p, sizeof(c->email)); p = next + 1;

    // 8. Domaine (Last field)
    safe_strcpy(c->domaine, p, sizeof(c->domaine));

    return 1;
}

int ajouter_coach(Coach c) {
    FILE *f;
    f = fopen("coach.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s;%s;%s;%d;%s;%s;%s;%s\n",
                c.id, c.nom, c.prenom, c.age, c.sexe, c.telephone, c.email, c.domaine);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifier_coach(Coach c) {
    FILE *f, *tmp;
    Coach temp;
    int found = 0;
    char line[1024];

    f = fopen("coach.txt", "r");
    tmp = fopen("coach.tmp", "w");

    if (f != NULL && tmp != NULL) {
        while (fgets(line, sizeof(line), f)) {
            if (parse_coach_line(line, &temp)) {
                if (strcmp(temp.id, c.id) == 0) {
                    fprintf(tmp, "%s;%s;%s;%d;%s;%s;%s;%s\n",
                            c.id, c.nom, c.prenom, c.age, c.sexe, c.telephone, c.email, c.domaine);
                    found = 1;
                } else {
                    fprintf(tmp, "%s;%s;%s;%d;%s;%s;%s;%s\n",
                            temp.id, temp.nom, temp.prenom, temp.age, temp.sexe, temp.telephone, temp.email, temp.domaine);
                }
            }
        }
        fclose(f);
        fclose(tmp);
        remove("coach.txt");
        rename("coach.tmp", "coach.txt");
    }
    return found;
}

int supprimer_coach(char *id) {
    FILE *f, *tmp;
    Coach temp;
    int found = 0;
    char line[1024];

    f = fopen("coach.txt", "r");
    tmp = fopen("coach.tmp", "w");

    if (f != NULL && tmp != NULL) {
        while (fgets(line, sizeof(line), f)) {
            if (parse_coach_line(line, &temp)) {
                if (strcmp(temp.id, id) != 0) {
                    fprintf(tmp, "%s;%s;%s;%d;%s;%s;%s;%s\n",
                            temp.id, temp.nom, temp.prenom, temp.age, temp.sexe, temp.telephone, temp.email, temp.domaine);
                } else {
                    found = 1;
                }
            }
        }
        fclose(f);
        fclose(tmp);
        remove("coach.txt");
        rename("coach.tmp", "coach.txt");
    }
    return found;
}

Coach rechercher_coach(char *id) {
    FILE *f;
    Coach temp;
    Coach foundCoach;
    char line[1024];

    memset(&foundCoach, 0, sizeof(Coach));
    strcpy(foundCoach.id, ""); 

    f = fopen("coach.txt", "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            char line_copy[1024];
            strncpy(line_copy, line, sizeof(line_copy));
            
            if (parse_coach_line(line_copy, &temp)) {
                if (strcmp(temp.id, id) == 0) {
                    foundCoach = temp;
                    break;
                }
            }
        }
        fclose(f);
    }
    return foundCoach;
}

enum {
    ID_COACH_COLUMN,
    NOM_COACH_COLUMN,
    PRENOM_COACH_COLUMN,
    AGE_COACH_COLUMN,
    SEXE_COACH_COLUMN,
    TELEPHONE_COACH_COLUMN,
    EMAIL_COACH_COLUMN,
    DOMAINE_COACH_COLUMN,
    N_COACH_COLUMNS
};

void afficher_coach(GtkWidget *liste) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    Coach c;
    char line[1024];

    GtkCellRenderer *renderer;

    store = gtk_list_store_new(N_COACH_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen("coach.txt", "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            if (parse_coach_line(line, &c)) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   ID_COACH_COLUMN, c.id,
                                   NOM_COACH_COLUMN, c.nom,
                                   PRENOM_COACH_COLUMN, c.prenom,
                                   AGE_COACH_COLUMN, c.age,
                                   SEXE_COACH_COLUMN, c.sexe,
                                   TELEPHONE_COACH_COLUMN, c.telephone,
                                   EMAIL_COACH_COLUMN, c.email,
                                   DOMAINE_COACH_COLUMN, c.domaine,
                                   -1);
            }
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);

    if (gtk_tree_view_get_column(GTK_TREE_VIEW(liste), 0) == NULL) {
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "ID", renderer, "text", ID_COACH_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Nom", renderer, "text", NOM_COACH_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Prenom", renderer, "text", PRENOM_COACH_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Domaine", renderer, "text", DOMAINE_COACH_COLUMN, NULL);
    }
}

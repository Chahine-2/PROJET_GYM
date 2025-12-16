#include "member.h"
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

// Helper to parse a line into Membre struct
// Returns 1 on success (even if partial fields), 0 if completely malformed
static int parse_line(char *line, Membre *m) {
    char *p = line;
    char *next;
    
    // Remove newline
    char *nl = strchr(line, '\n');
    if (nl) *nl = '\0';
    // Remove carriage return
    char *cr = strchr(line, '\r');
    if (cr) *cr = '\0';

    if (strlen(line) == 0) return 0;

    memset(m, 0, sizeof(Membre));

    // 1. ID
    next = strchr(p, ';'); 
    if (!next) return 0; // Require at least one separator
    *next = '\0'; safe_strcpy(m->id, p, sizeof(m->id)); p = next + 1;

    // 2. Nom
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->nom, p, sizeof(m->nom)); p = next + 1;

    // 3. Prenom
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->prenom, p, sizeof(m->prenom)); p = next + 1;

    // 4. Age (Int)
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; m->age = atoi(p); p = next + 1;

    // 5. Sexe
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->sexe, p, sizeof(m->sexe)); p = next + 1;

    // 6. Telephone
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->telephone, p, sizeof(m->telephone)); p = next + 1;

    // 7. Email
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->email, p, sizeof(m->email)); p = next + 1;

    // 8. Date (d/m/y)
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; 
    sscanf(p, "%d/%d/%d", &m->jour, &m->mois, &m->annee);
    p = next + 1;

    // 9. Type Abonnement
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->type_abonnement, p, sizeof(m->type_abonnement)); p = next + 1;

    // 10. Type Forfait
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->type_forfait, p, sizeof(m->type_forfait)); p = next + 1;

    // 11. Prix
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->prix, p, sizeof(m->prix)); p = next + 1;

    // 12. Methode Paiement
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->methode_paiement, p, sizeof(m->methode_paiement)); p = next + 1;

    // 13. Statut Paiement
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->statut_paiement, p, sizeof(m->statut_paiement)); p = next + 1;

    // 14. Coach
    next = strchr(p, ';'); 
    if (!next) return 0; 
    *next = '\0'; safe_strcpy(m->coach, p, sizeof(m->coach)); p = next + 1;

    // 15. Statut
    // Handle garbage: read until semicolon OR end of string. 
    next = strchr(p, ';'); 
    if (next) *next = '\0'; 
    safe_strcpy(m->statut, p, sizeof(m->statut));

    return 1;
}

int ajouter_membre(Membre m) {
    FILE *f;
    f = fopen("membre.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s;%s;%s;%d;%s;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s\n",
                m.id, m.nom, m.prenom, m.age, m.sexe, m.telephone, m.email,
                m.jour, m.mois, m.annee, m.type_abonnement, m.type_forfait,
                m.prix, m.methode_paiement, m.statut_paiement, m.coach, m.statut);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifier_membre(Membre m) {
    FILE *f, *tmp;
    Membre temp;
    int found = 0;
    char line[1024];

    f = fopen("membre.txt", "r");
    tmp = fopen("membre.tmp", "w");

    if (f != NULL && tmp != NULL) {
        while (fgets(line, sizeof(line), f)) {
            if (parse_line(line, &temp)) {
                if (strcmp(temp.id, m.id) == 0) {
                    fprintf(tmp, "%s;%s;%s;%d;%s;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s\n",
                            m.id, m.nom, m.prenom, m.age, m.sexe, m.telephone, m.email,
                            m.jour, m.mois, m.annee, m.type_abonnement, m.type_forfait,
                            m.prix, m.methode_paiement, m.statut_paiement, m.coach, m.statut);
                    found = 1;
                } else {
                    fprintf(tmp, "%s;%s;%s;%d;%s;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s\n",
                            temp.id, temp.nom, temp.prenom, temp.age, temp.sexe, temp.telephone, temp.email,
                            temp.jour, temp.mois, temp.annee, temp.type_abonnement, temp.type_forfait,
                            temp.prix, temp.methode_paiement, temp.statut_paiement, temp.coach, temp.statut);
                }
            }
        }
        fclose(f);
        fclose(tmp);
        remove("membre.txt");
        rename("membre.tmp", "membre.txt");
    }
    return found;
}

int supprimer_membre(char *id) {
    FILE *f, *tmp;
    Membre temp;
    int found = 0;
    char line[1024];

    f = fopen("membre.txt", "r");
    tmp = fopen("membre.tmp", "w");

    if (f != NULL && tmp != NULL) {
        while (fgets(line, sizeof(line), f)) {
            if (parse_line(line, &temp)) {
                if (strcmp(temp.id, id) != 0) {
                     fprintf(tmp, "%s;%s;%s;%d;%s;%s;%s;%d/%d/%d;%s;%s;%s;%s;%s;%s;%s\n",
                            temp.id, temp.nom, temp.prenom, temp.age, temp.sexe, temp.telephone, temp.email,
                            temp.jour, temp.mois, temp.annee, temp.type_abonnement, temp.type_forfait,
                            temp.prix, temp.methode_paiement, temp.statut_paiement, temp.coach, temp.statut);
                } else {
                    found = 1;
                }
            }
        }
        fclose(f);
        fclose(tmp);
        remove("membre.txt");
        rename("membre.tmp", "membre.txt");
    }
    return found;
}

Membre rechercher_membre(char *id) {
    FILE *f;
    Membre temp;
    Membre foundMember;
    char line[1024];
    
    memset(&foundMember, 0, sizeof(Membre));
    strcpy(foundMember.id, ""); 

    f = fopen("membre.txt", "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            // Make a copy of line because parse_line modifies it (inserts \0)
            char line_copy[1024];
            strncpy(line_copy, line, sizeof(line_copy));
            
            if (parse_line(line_copy, &temp)) {
                if (strcmp(temp.id, id) == 0) {
                    foundMember = temp;
                    break;
                }
            }
        }
        fclose(f);
    }
    return foundMember;
}

enum {
    ID_COLUMN,
    NOM_COLUMN,
    PRENOM_COLUMN,
    AGE_COLUMN,
    SEXE_COLUMN,
    TELEPHONE_COLUMN,
    EMAIL_COLUMN,
    DATE_COLUMN,
    ABONNEMENT_COLUMN,
    FORFAIT_COLUMN,
    PRIX_COLUMN,
    PAIEMENT_COLUMN,
    STATUT_PAIEMENT_COLUMN,
    COACH_COLUMN,
    STATUT_COLUMN,
    N_COLUMNS
};

void afficher_membre(GtkWidget *liste) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    Membre m;
    char date[20];
    char line[1024];

    GtkCellRenderer *renderer;
    
    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen("membre.txt", "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
             if (parse_line(line, &m)) {
                sprintf(date, "%02d/%02d/%04d", m.jour, m.mois, m.annee);
                
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   ID_COLUMN, m.id,
                                   NOM_COLUMN, m.nom,
                                   PRENOM_COLUMN, m.prenom,
                                   AGE_COLUMN, m.age,
                                   SEXE_COLUMN, m.sexe,
                                   TELEPHONE_COLUMN, m.telephone,
                                   EMAIL_COLUMN, m.email,
                                   DATE_COLUMN, date,
                                   ABONNEMENT_COLUMN, m.type_abonnement,
                                   FORFAIT_COLUMN, m.type_forfait,
                                   PRIX_COLUMN, m.prix,
                                   PAIEMENT_COLUMN, m.methode_paiement,
                                   STATUT_PAIEMENT_COLUMN, m.statut_paiement,
                                   COACH_COLUMN, m.coach,
                                   STATUT_COLUMN, m.statut,
                                   -1);
             }
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);

    if (gtk_tree_view_get_column(GTK_TREE_VIEW(liste), 0) == NULL) {
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "ID", renderer, "text", ID_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Nom", renderer, "text", NOM_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Prenom", renderer, "text", PRENOM_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Date", renderer, "text", DATE_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Coach", renderer, "text", COACH_COLUMN, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(liste), -1, "Statut", renderer, "text", STATUT_COLUMN, NULL);
    }
}

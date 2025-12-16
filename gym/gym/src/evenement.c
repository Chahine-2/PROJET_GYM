#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include "evenement.h"
#include "centre.h"
/******************* FONCTIONS UTILITAIRES *******************/
void to_lowercase_event(char *str, char *result) {
    int i = 0;
    while (str[i]) {
        result[i] = tolower(str[i]);
        i++;
    }
    result[i] = '\0';
}

int generer_id_evenement(char *new_id) {
    FILE *f = fopen(EVENEMENT_FILE, "r");
    int max_id = 0;
    Evenement e;

    if (f) {
        while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                      e.id, e.nom, e.description, e.type,
                      &e.date.jour, &e.date.mois, &e.date.annee,
                      e.heure_debut, e.heure_fin,
                      &e.id_centre, e.salle, e.entraineur_nom,
                      &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {
            int current_id = atoi(e.id);
            if (current_id > max_id) max_id = current_id;
        }
        fclose(f);
    }

    sprintf(new_id, "%d", max_id + 1);
    return max_id + 1;
}

/******************* VERIFIER SI L'ID EXISTE *******************/
int evenement_existe(const char *id) {
    FILE *f = fopen(EVENEMENT_FILE, "r");
    if (!f) return 0;

    Evenement e;
    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  e.id, e.nom, e.description, e.type,
                  &e.date.jour, &e.date.mois, &e.date.annee,
                  e.heure_debut, e.heure_fin,
                  &e.id_centre, e.salle, e.entraineur_nom,
                  &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {
        if (strcmp(e.id, id) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/******************* FONCTIONS CRUD *******************/
int ajouter_evenement(Evenement e) {
    FILE *f = fopen(EVENEMENT_FILE, "a");
    if (!f) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", EVENEMENT_FILE);
        return 0;
    }

    generer_id_evenement(e.id);

    fprintf(f, "%s %s %s %s %02d/%02d/%04d %s %s %d %s %s %d %d %.2f\n",
            e.id, e.nom, e.description, e.type,
            e.date.jour, e.date.mois, e.date.annee,
            e.heure_debut, e.heure_fin,
            e.id_centre, e.salle, e.entraineur_nom,
            e.capacite_max, e.nb_inscrits, e.prix);

    fflush(f);
    fclose(f);
    return 1;
}

/******************* MODIFIER EVENEMENT *******************/
int modifier_evenement(const char *id, Evenement e) {
    FILE *f = fopen(EVENEMENT_FILE, "r");
    FILE *temp = fopen("temp_evenement.txt", "w");
    if (!f || !temp) {
        if (f) fclose(f);
        if (temp) fclose(temp);
        return 0;
    }

    int found = 0;
    Evenement temp_e;

    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  temp_e.id, temp_e.nom, temp_e.description, temp_e.type,
                  &temp_e.date.jour, &temp_e.date.mois, &temp_e.date.annee,
                  temp_e.heure_debut, temp_e.heure_fin,
                  &temp_e.id_centre, temp_e.salle, temp_e.entraineur_nom,
                  &temp_e.capacite_max, &temp_e.nb_inscrits, &temp_e.prix) != EOF) {

        if (strcmp(temp_e.id, id) == 0) {
            strcpy(e.id, id);
            fprintf(temp, "%s %s %s %s %02d/%02d/%04d %s %s %d %s %s %d %d %.2f\n",
                    e.id, e.nom, e.description, e.type,
                    e.date.jour, e.date.mois, e.date.annee,
                    e.heure_debut, e.heure_fin,
                    e.id_centre, e.salle, e.entraineur_nom,
                    e.capacite_max, e.nb_inscrits, e.prix);
            found = 1;
        } else {
            fprintf(temp, "%s %s %s %s %02d/%02d/%04d %s %s %d %s %s %d %d %.2f\n",
                    temp_e.id, temp_e.nom, temp_e.description, temp_e.type,
                    temp_e.date.jour, temp_e.date.mois, temp_e.date.annee,
                    temp_e.heure_debut, temp_e.heure_fin,
                    temp_e.id_centre, temp_e.salle, temp_e.entraineur_nom,
                    temp_e.capacite_max, temp_e.nb_inscrits, temp_e.prix);
        }
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(EVENEMENT_FILE);
        rename("temp_evenement.txt", EVENEMENT_FILE);
        return 1;
    } else {
        remove("temp_evenement.txt");
        return 0;
    }
}

/******************* SUPPRIMER EVENEMENT *******************/
int supprimer_evenement(const char *id) {
    FILE *f = fopen(EVENEMENT_FILE, "r");
    FILE *temp = fopen("temp_evenement.txt", "w");
    if (!f || !temp) {
        if (f) fclose(f);
        if (temp) fclose(temp);
        return 0;
    }

    int found = 0;
    Evenement e;

    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  e.id, e.nom, e.description, e.type,
                  &e.date.jour, &e.date.mois, &e.date.annee,
                  e.heure_debut, e.heure_fin,
                  &e.id_centre, e.salle, e.entraineur_nom,
                  &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {

        if (strcmp(e.id, id) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s %s %s %s %02d/%02d/%04d %s %s %d %s %s %d %d %.2f\n",
                    e.id, e.nom, e.description, e.type,
                    e.date.jour, e.date.mois, e.date.annee,
                    e.heure_debut, e.heure_fin,
                    e.id_centre, e.salle, e.entraineur_nom,
                    e.capacite_max, e.nb_inscrits, e.prix);
        }
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(EVENEMENT_FILE);
        rename("temp_evenement.txt", EVENEMENT_FILE);
        return 1;
    } else {
        remove("temp_evenement.txt");
        return 0;
    }
}

/******************* CHERCHER EVENEMENT *******************/
Evenement chercher_evenement(const char *id) {
    FILE *f = fopen(EVENEMENT_FILE, "r");
    Evenement e;
    Evenement empty = {"", "", "", "", {0,0,0}, "", "", 0, "", "", 0, 0, 0.0};

    if (!f) return empty;

    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  e.id, e.nom, e.description, e.type,
                  &e.date.jour, &e.date.mois, &e.date.annee,
                  e.heure_debut, e.heure_fin,
                  &e.id_centre, e.salle, e.entraineur_nom,
                  &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {
        if (strcmp(e.id, id) == 0) {
            fclose(f);
            return e;
        }
    }
    fclose(f);
    return empty;
}

/******************* RECHERCHE (multi critères) *******************/
void rechercher_evenement_multi_criteres(
    const char *nom, int use_nom,
    const char *type, int use_type,
    const char *id, int use_id,
    int jour, int mois, int annee, int use_date,
    const char *quick_search,
    Evenement *resultats, int *count) {

    FILE *f = fopen(EVENEMENT_FILE, "r");
    if (!f) { *count = 0; return; }

    *count = 0;
    Evenement e;

    char nom_lower[100] = "", type_lower[50] = "", quick_lower[100] = "";
    char buf[300];

    if (nom) to_lowercase_event((char*)nom, nom_lower);
    if (type) to_lowercase_event((char*)type, type_lower);
    if (quick_search) to_lowercase_event((char*)quick_search, quick_lower);

    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  e.id, e.nom, e.description, e.type,
                  &e.date.jour, &e.date.mois, &e.date.annee,
                  e.heure_debut, e.heure_fin,
                  &e.id_centre, e.salle, e.entraineur_nom,
                  &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {

        int match = 1;

        // Recherche rapide
        if (quick_search && strlen(quick_search) > 0) {
            char temp[300];
            strcpy(temp, e.nom); to_lowercase_event(temp, temp);
            if (strstr(temp, quick_lower) == NULL) {
                strcpy(temp, e.type); to_lowercase_event(temp, temp);
                if (strstr(temp, quick_lower) == NULL) {
                    strcpy(temp, e.id); to_lowercase_event(temp, temp);
                    if (strstr(temp, quick_lower) == NULL) {
                        strcpy(temp, e.description); to_lowercase_event(temp, temp);
                        if (strstr(temp, quick_lower) == NULL) {
                            strcpy(temp, e.salle); to_lowercase_event(temp, temp);
                            if (strstr(temp, quick_lower) == NULL) {
                                strcpy(temp, e.entraineur_nom); to_lowercase_event(temp, temp);
                                if (strstr(temp, quick_lower) == NULL) match = 0;
                            }
                        }
                    }
                }
            }
        }

        if (match && use_nom && nom && strlen(nom) > 0) {
            to_lowercase_event(e.nom, buf);
            if (strstr(buf, nom_lower) == NULL) match = 0;
        }

        if (match && use_type && type && strlen(type) > 0) {
            to_lowercase_event(e.type, buf);
            if (strcmp(buf, type_lower) != 0) match = 0;
        }

        if (match && use_id && id && strlen(id) > 0) {
            if (strcmp(e.id, id) != 0) match = 0;
        }

        if (match && use_date) {
            if (e.date.jour != jour || e.date.mois != mois || e.date.annee != annee)
                match = 0;
        }

        if (match && *count < 100) {
            resultats[(*count)++] = e;
        }
    }
    fclose(f);
}

/******************* AFFICHAGE *******************/
enum {
    COL_ID_E,
    COL_NOM_E,
    COL_DESCRIPTION_E,
    COL_TYPE_E,
    COL_DATE_E,
    COL_HEURE_DEBUT_E,
    COL_HEURE_FIN_E,
    COL_ID_CENTRE_E,
    COL_SALLE_E,
    COL_ENTRAINEUR_E,
    COL_CAPACITE_E,
    COL_INSCRITS_E,
    COL_PRIX_E,
    NUM_COLS_E
};

void afficher_evenements(GtkWidget *treeview) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;

    if (!model) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "ID", renderer, "text", COL_ID_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Nom", renderer, "text", COL_NOM_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Description", renderer, "text", COL_DESCRIPTION_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Type", renderer, "text", COL_TYPE_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Date", renderer, "text", COL_DATE_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Heure Début", renderer, "text", COL_HEURE_DEBUT_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Heure Fin", renderer, "text", COL_HEURE_FIN_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Centre", renderer, "text", COL_ID_CENTRE_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Salle", renderer, "text", COL_SALLE_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Entraîneur", renderer, "text", COL_ENTRAINEUR_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Capacité", renderer, "text", COL_CAPACITE_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Inscrits", renderer, "text", COL_INSCRITS_E, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Prix", renderer, "text", COL_PRIX_E, NULL);

        store = gtk_list_store_new(NUM_COLS_E,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT,
                                   G_TYPE_FLOAT);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
    }

    gtk_list_store_clear(store);

    FILE *f = fopen(EVENEMENT_FILE, "r");
    if (!f) {
        g_warning("Impossible d'ouvrir le fichier: %s\n", EVENEMENT_FILE);
        return;
    }

    Evenement e;
    char date_str[20];
    GtkTreeIter iter;
    int line = 0;

    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  e.id, e.nom, e.description, e.type,
                  &e.date.jour, &e.date.mois, &e.date.annee,
                  e.heure_debut, e.heure_fin,
                  &e.id_centre, e.salle, e.entraineur_nom,
                  &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {

        line++;
        sprintf(date_str, "%02d/%02d/%04d", e.date.jour, e.date.mois, e.date.annee);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_ID_E, e.id,
                           COL_NOM_E, e.nom,
                           COL_DESCRIPTION_E, e.description,
                           COL_TYPE_E, e.type,
                           COL_DATE_E, date_str,
                           COL_HEURE_DEBUT_E, e.heure_debut,
                           COL_HEURE_FIN_E, e.heure_fin,
                           COL_ID_CENTRE_E, e.id_centre,
                           COL_SALLE_E, e.salle,
                           COL_ENTRAINEUR_E, e.entraineur_nom,
                           COL_CAPACITE_E, e.capacite_max,
                           COL_INSCRITS_E, e.nb_inscrits,
                           COL_PRIX_E, e.prix,
                           -1);
    }
    
    fclose(f);
    g_print("Chargé %d événements dans le treeview\n", line);
}

void afficher_resultats_recherche(GtkWidget *treeview, Evenement *resultats, int count) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;
    
    if (!model) {
        afficher_evenements(treeview);
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    }
    
    store = GTK_LIST_STORE(model);
    gtk_list_store_clear(store);

    char date_str[20];
    GtkTreeIter iter;

    for (int i = 0; i < count; i++) {
        sprintf(date_str, "%02d/%02d/%04d",
                resultats[i].date.jour, resultats[i].date.mois, resultats[i].date.annee);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_ID_E, resultats[i].id,
                           COL_NOM_E, resultats[i].nom,
                           COL_DESCRIPTION_E, resultats[i].description,
                           COL_TYPE_E, resultats[i].type,
                           COL_DATE_E, date_str,
                           COL_HEURE_DEBUT_E, resultats[i].heure_debut,
                           COL_HEURE_FIN_E, resultats[i].heure_fin,
                           COL_ID_CENTRE_E, resultats[i].id_centre,
                           COL_SALLE_E, resultats[i].salle,
                           COL_ENTRAINEUR_E, resultats[i].entraineur_nom,
                           COL_CAPACITE_E, resultats[i].capacite_max,
                           COL_INSCRITS_E, resultats[i].nb_inscrits,
                           COL_PRIX_E, resultats[i].prix,
                           -1);
    }
}


/******************* FONCTIONS D'INSCRIPTION DES MEMBRES *******************/

// Vérifier si le membre est déjà inscrit à un événement
int membre_inscrit_evenement(const char *id_membre, const char *id_evenement) {
    FILE *f = fopen(INSCRIPTION_FILE, "r");
    if (!f) return 0;

    char membre[20], event[20];
    while (fscanf(f, "%s %s\n", membre, event) != EOF) {
        if (strcmp(membre, id_membre) == 0 && strcmp(event, id_evenement) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

// Inscrire un membre à un événement
int inscrire_membre_evenement(const char *id_membre, const char *id_evenement) {
    // Vérifier si l'événement existe
    if (!evenement_existe(id_evenement)) {
        g_warning("L'événement %s n'existe pas\n", id_evenement);
        return 0;
    }

    // Vérifier si déjà inscrit
    if (membre_inscrit_evenement(id_membre, id_evenement)) {
        g_warning("Le membre %s est déjà inscrit à l'événement %s\n", id_membre, id_evenement);
        return 0;
    }

    // Récupérer les détails de l'événement
    Evenement e = chercher_evenement(id_evenement);
    
    // Vérifier si l'événement est complet
    if (e.nb_inscrits >= e.capacite_max) {
        g_warning("L'événement %s est complet\n", id_evenement);
        return 0;
    }

    // Ajouter l'inscription
    FILE *f = fopen(INSCRIPTION_FILE, "a");
    if (!f) {
        g_warning("Impossible d'ouvrir le fichier des inscriptions\n");
        return 0;
    }
    fprintf(f, "%s %s\n", id_membre, id_evenement);
    fclose(f);

    // Mettre à jour le nombre d'inscrits
    e.nb_inscrits++;
    modifier_evenement(id_evenement, e);

    return 1;
}

// Désinscrire un membre d'un événement
int desinscrire_membre_evenement(const char *id_membre, const char *id_evenement) {
    FILE *f = fopen(INSCRIPTION_FILE, "r");
    FILE *temp = fopen("temp_inscription.txt", "w");
    if (!f || !temp) {
        if (f) fclose(f);
        if (temp) fclose(temp);
        return 0;
    }

    int found = 0;
    char membre[20], event[20];

    while (fscanf(f, "%s %s\n", membre, event) != EOF) {
        if (strcmp(membre, id_membre) == 0 && strcmp(event, id_evenement) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s %s\n", membre, event);
        }
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(INSCRIPTION_FILE);
        rename("temp_inscription.txt", INSCRIPTION_FILE);
        
        // Mettre à jour le nombre d'inscrits
        Evenement e = chercher_evenement(id_evenement);
        if (e.nb_inscrits > 0) {
            e.nb_inscrits--;
            modifier_evenement(id_evenement, e);
        }
        
        return 1;
    } else {
        remove("temp_inscription.txt");
        return 0;
    }
}

// Afficher les événements disponibles pour inscription (non complets, non inscrits)
void afficher_evenements_disponibles(GtkWidget *treeview, const char *id_membre) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;

    if (!model) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "ID", renderer, "text", 0, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Nom", renderer, "text", 1, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Type", renderer, "text", 2, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Date", renderer, "text", 3, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Heure", renderer, "text", 4, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Salle", renderer, "text", 5, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Entraîneur", renderer, "text", 6, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Places Dispo", renderer, "text", 7, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Prix", renderer, "text", 8, NULL);

        store = gtk_list_store_new(9,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
    }

    gtk_list_store_clear(store);

    FILE *f = fopen(EVENEMENT_FILE, "r");
    if (!f) return;

    Evenement e;
    char date_str[20], heure_str[20], places_str[20], prix_str[20];
    GtkTreeIter iter;

    while (fscanf(f, "%s %s %s %s %d/%d/%d %s %s %d %s %s %d %d %f\n",
                  e.id, e.nom, e.description, e.type,
                  &e.date.jour, &e.date.mois, &e.date.annee,
                  e.heure_debut, e.heure_fin,
                  &e.id_centre, e.salle, e.entraineur_nom,
                  &e.capacite_max, &e.nb_inscrits, &e.prix) != EOF) {

        // Ignorer si déjà inscrit ou événement complet
        if (strlen(id_membre) > 0 && membre_inscrit_evenement(id_membre, e.id)) continue;
        if (e.nb_inscrits >= e.capacite_max) continue;

        sprintf(date_str, "%02d/%02d/%04d", e.date.jour, e.date.mois, e.date.annee);
        sprintf(heure_str, "%s-%s", e.heure_debut, e.heure_fin);
        sprintf(places_str, "%d/%d", e.capacite_max - e.nb_inscrits, e.capacite_max);
        sprintf(prix_str, "%.2f DT", e.prix);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, e.id,
                           1, e.nom,
                           2, e.type,
                           3, date_str,
                           4, heure_str,
                           5, e.salle,
                           6, e.entraineur_nom,
                           7, places_str,
                           8, prix_str,
                           -1);
    }
    
    fclose(f);
}

// Afficher les événements auxquels le membre est inscrit
void afficher_evenements_membre(GtkWidget *treeview, const char *id_membre) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;

    if (!model) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "ID", renderer, "text", 0, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Nom", renderer, "text", 1, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Type", renderer, "text", 2, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Date", renderer, "text", 3, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Heure", renderer, "text", 4, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Salle", renderer, "text", 5, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Entraîneur", renderer, "text", 6, NULL);
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
            "Prix", renderer, "text", 7, NULL);

        store = gtk_list_store_new(8,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
    }

    gtk_list_store_clear(store);

    FILE *f = fopen(INSCRIPTION_FILE, "r");
    if (!f) return;

    char membre[20], event_id[20];
    GtkTreeIter iter;

    while (fscanf(f, "%s %s\n", membre, event_id) != EOF) {
        if (strcmp(membre, id_membre) == 0) {
            Evenement e = chercher_evenement(event_id);
            
            if (strlen(e.id) > 0) {
                char date_str[20], heure_str[20], prix_str[20];
                sprintf(date_str, "%02d/%02d/%04d", e.date.jour, e.date.mois, e.date.annee);
                sprintf(heure_str, "%s-%s", e.heure_debut, e.heure_fin);
                sprintf(prix_str, "%.2f DT", e.prix);

                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   0, e.id,
                                   1, e.nom,
                                   2, e.type,
                                   3, date_str,
                                   4, heure_str,
                                   5, e.salle,
                                   6, e.entraineur_nom,
                                   7, prix_str,
                                   -1);
            }
        }
    }
    
    fclose(f);
}

void populate_centre_combobox(GtkWidget *combobox) {
    if (!combobox) {
        g_warning("ComboBox widget is NULL!\n");
        return;
    }
    
    // Clear existing items
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combobox));
    if (model) {
        gtk_list_store_clear(GTK_LIST_STORE(model));
    }
    
    FILE *f = fopen(CENTRE_FILE, "r");
    if (!f) {
        g_warning("Impossible d'ouvrir le fichier: %s\n", CENTRE_FILE);
        return;
    }
    
    Centre c;
    while (fscanf(f, "%d %s %s %d %s %s %s %d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) != EOF) {
        
        // Replace underscores with spaces for display
        char display_name[100];
        strcpy(display_name, c.nom);
        for (int i = 0; display_name[i]; i++) {
            if (display_name[i] == '_') display_name[i] = ' ';
        }
        
        gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), display_name);
    }
    
    fclose(f);
    g_print("Centre combobox populated successfully\n");
}

int get_centre_id_by_name(const char *nom) {
    if (!nom || strlen(nom) == 0) return 0;
    
    FILE *f = fopen(CENTRE_FILE, "r");
    if (!f) return 0;
    
    Centre c;
    char search_name[100];
    strcpy(search_name, nom);
    
    // Replace spaces with underscores for comparison
    for (int i = 0; search_name[i]; i++) {
        if (search_name[i] == ' ') search_name[i] = '_';
    }
    
    while (fscanf(f, "%d %s %s %d %s %s %s %d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) != EOF) {
        
        if (strcmp(c.nom, search_name) == 0) {
            fclose(f);
            return c.id;
        }
    }
    
    fclose(f);
    return 0;
}

char* get_centre_name_by_id(int id) {
    static char name[100];
    strcpy(name, "");
    
    FILE *f = fopen(CENTRE_FILE, "r");
    if (!f) return name;
    
    Centre c;
    while (fscanf(f, "%d %s %s %d %s %s %s %d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) != EOF) {
        
        if (c.id == id) {
            strcpy(name, c.nom);
            // Replace underscores with spaces
            for (int i = 0; name[i]; i++) {
                if (name[i] == '_') name[i] = ' ';
            }
            fclose(f);
            return name;
        }
    }
    
    fclose(f);
    return name;
}

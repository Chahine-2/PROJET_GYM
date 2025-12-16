#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <gtk/gtk.h>

// Structure for Date (renamed to DateEvent to avoid conflict with centre.h)
typedef struct {
    int jour;
    int mois;
    int annee;
} DateEvent;

// Structure for Event
typedef struct {
    char id[20];
    char nom[100];
    char description[300];
    char type[50];
    DateEvent date;  // Using DateEvent instead of Date
    char heure_debut[6];
    char heure_fin[6];
    int id_centre;
    char salle[100];              // Room/Hall name
    char entraineur_nom[100];     // Trainer/Coach name
    int capacite_max;
    int nb_inscrits;
    float prix;
} Evenement;

// CRUD Functions
int ajouter_evenement(Evenement e);
int modifier_evenement(const char *id, Evenement e);
int supprimer_evenement(const char *id);
Evenement chercher_evenement(const char *id);
int evenement_existe(const char *id);

// Utility
int generer_id_evenement(char *new_id);
void afficher_evenements(GtkWidget *treeview);
void to_lowercase_event(char *str, char *result);

// Advanced Search
void rechercher_evenement_multi_criteres(
    const char *nom, int use_nom,
    const char *type, int use_type,
    const char *id, int use_id,
    int jour, int mois, int annee, int use_date,
    const char *quick_search,
    Evenement *resultats, int *count);
void afficher_resultats_recherche(GtkWidget *treeview, Evenement *resultats, int count);

// Member inscription functions
int inscrire_membre_evenement(const char *id_membre, const char *id_evenement);
int desinscrire_membre_evenement(const char *id_membre, const char *id_evenement);
int membre_inscrit_evenement(const char *id_membre, const char *id_evenement);
void afficher_evenements_membre(GtkWidget *treeview, const char *id_membre);
void afficher_evenements_disponibles(GtkWidget *treeview, const char *id_membre);

void populate_centre_combobox(GtkWidget *combobox);
int get_centre_id_by_name(const char *nom);
char* get_centre_name_by_id(int id);

// Files
#define CENTRE_FILE "centre.txt"
#define INSCRIPTION_CENTRE_FILE "inscriptions_centres.txt"
#define EVENEMENT_FILE "evenements.txt"
#define INSCRIPTION_FILE "inscriptions.txt"

#endif // EVENEMENT_H

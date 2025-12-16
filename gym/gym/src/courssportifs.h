#ifndef COURSSPORTIFS_H
#define COURSSPORTIFS_H

#include <gtk/gtk.h>   // REQUIRED for GtkWidget

// ================= Structures =================

// Structure for Date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Structure for Time
typedef struct {
    int heure;
    int minute;
} Heure;

// Structure for Cours Sportif
typedef struct {
    int id;
    char nom[100];
    char jour_semaine[20];
    Date date;
    Heure heure;
    char salle[50];
    char entraineur[100];
    int duree; // in minutes
    char centre[100];
} CoursSportif;

// ================= Function Prototypes =================

// CRUD operations
int ajouter_cours(const char *filename, CoursSportif c);
int supprimer_cours(const char *filename_cours,
                    const char *filename_inscriptions,
                    int id);

CoursSportif chercher_cours_par_nom(const char *filename, const char *nom);
CoursSportif chercher_cours_par_id(const char *filename, int id);

int modifier_cours(const char *filename, int id, CoursSportif nouveau);
int generer_id_unique(const char *filename);

void supprimer_inscriptions_par_cours(const char *filename, int cours_id);

// Display / GTK-related functions
void afficher_tous_cours(const char *filename);
void afficher_emploi_cours(GtkWidget *treeview);

// ComboBox helper
void charger_cours_dans_combo(GtkWidget *combo, const char *filename);
/******************* TIMETABLE TREEVIEW FUNCTIONS *******************/

/* Display functions for timetable treeview */
void afficher_emploi_temps(GtkWidget *treeview);
void afficher_emploi_par_jour(GtkWidget *treeview, const char *jour);
void afficher_emploi_par_centre(GtkWidget *treeview, const char *centre);
int get_cours_selectionne(GtkWidget *treeview, CoursSportif *cours);

#endif /* COURSSPORTIFS_H */


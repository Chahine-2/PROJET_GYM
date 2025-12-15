#ifndef CENTRE_H
#define CENTRE_H

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    int heure;
    int minute;
} Heure;

typedef struct
{
    int id;
    char nom[100];
    char adresse[200];
    int nb_salles;
    char telephone[30];
    char email[100];
    char type[50];     
    int capacite;
} Centre;

typedef struct {
    int id;
    char nom_centre[100];
    char adresse[100];
    char specialite[100];
    Date date;
    Heure heure;
} Inscription;

typedef struct {
    int total_centres;
    int ids[100];
    char noms[100][100];
    char adresses[100][200];
    int inscriptions[100];
    int nb_centres;
    int id_max; // ID of centre with most inscriptions
} Stats;

int ajouter_centre(char *filename, Centre c);
int modifier_centre(char *filename, int id, Centre nouv);
int supprimer_centre(char *filename_centres, char *filename_inscriptions, int id);
Centre chercher_centre(char *filename, int id);

int tableau_centre_disponible(char noms[][100]);
int tableau_centre_adresse(char adresses[][100],char nom[100]);
int inscriptions_meme_creneau(char *fichier_inscriptions, Centre c, Date d, Heure h);
int ajouter_inscription(char *fichier_inscriptions, char *fichier_centres, Inscription i);

int nombre_total_centres(char *filename);
int nombre_inscriptions_par_centre(char *fichier_inscriptions, Centre c);
int centre_plus_dinscriptions(char *fichier_centres, char *fichier_inscriptions);
void statistiques(char *fichier_centres, char *fichier_inscriptions, Stats *s);

#endif


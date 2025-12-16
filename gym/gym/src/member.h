#ifndef MEMBER_H
#define MEMBER_H

#include <gtk/gtk.h>

typedef struct {
    char id[50];
    char nom[50];
    char prenom[50];
    int age;
    char sexe[10];
    char telephone[20];
    char email[50];
    int jour;
    int mois;
    int annee;
    char type_abonnement[50];
    char type_forfait[50];
    char prix[20];
    char methode_paiement[20];
    char statut_paiement[20];
    char coach[100]; // "Name Surname (ID)"
    char statut[20]; // "actif" or "inactif"
} Membre;

int ajouter_membre(Membre m);
int modifier_membre(Membre m);
int supprimer_membre(char *id);
Membre rechercher_membre(char *id);
void afficher_membre(GtkWidget *liste);

#endif

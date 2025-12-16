#ifndef COACH_H
#define COACH_H

#include <gtk/gtk.h>

typedef struct {
    char id[50];
    char nom[50];
    char prenom[50];
    int age;
    char sexe[10];
    char telephone[20];
    char email[50];
    char domaine[50];
} Coach;

int ajouter_coach(Coach c);
int modifier_coach(Coach c);
int supprimer_coach(char *id);
Coach rechercher_coach(char *id);
void afficher_coach(GtkWidget *liste);

#endif

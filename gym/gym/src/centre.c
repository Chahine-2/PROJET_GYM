#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "centre.h"


int tableau_centre_disponible(char noms[][100])
{
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    int n = 0;

    if (f == NULL)
        return 0;

    while (fscanf(f, "%d;%[^;];%[^;];%d;%[^;];%[^;];%[^;];%d\n",
                  &c.id,
                  c.nom,
                  c.adresse,
                  &c.nb_salles,
                  c.telephone,
                  c.email,
                  c.type,
                  &c.capacite) != EOF)
    {
        strcpy(noms[n], c.nom);   // on garde le nom du centre
        n++;
    }

    fclose(f);
    return n;   // nombre de centres
}

int tableau_centre_adresse(char adresses[][100],char nom[100])
{
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    int n = 0;

    if (f == NULL)
        return 0;

    while (fscanf(f, "%d;%[^;];%[^;];%d;%[^;];%[^;];%[^;];%d\n",
                  &c.id,
                  c.nom,
                  c.adresse,
                  &c.nb_salles,
                  c.telephone,
                  c.email,
                  c.type,
                  &c.capacite) != EOF)
    {
	if (strcmp(nom,c.nom)==0){
		strcpy(adresses[n], c.adresse);   
		n++;
	}
    }

    fclose(f);
    return n;   
}




// AJOUTER
int ajouter_centre(char *filename, Centre c)
{
    if (c.id <= 0 || strlen(c.nom) == 0 || strlen(c.adresse) == 0)
        return 3; 

    if (chercher_centre(filename, c.id).id != -1)
        return 2; 

    FILE *f = fopen(filename, "a");
    if (!f) return 0;

    fprintf(f, "%d;%s;%s;%d;%s;%s;%s;%d\n",c.id, c.nom, c.adresse,c.nb_salles, c.telephone, c.email,c.type, c.capacite);

    fclose(f);
    return 1;
}

// MODIFIER 
int modifier_centre(char *filename, int id, Centre nouv)
{
    FILE *f = fopen(filename, "r");
    FILE *tmp = fopen("tmp.txt", "w");
    if (!f || !tmp) {
        if (f) fclose(f);
        if (tmp) fclose(tmp);
        return 0;
    }

    Centre c;
    int found = 0;

    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        if (c.id == id) {
            found = 1;

            fprintf(tmp, "%d;%s;%s;%d;%s;%s;%s;%d\n",c.id,nouv.nom,nouv.adresse,nouv.nb_salles,nouv.telephone,nouv.email,nouv.type,nouv.capacite);
        } else {
          
            fprintf(tmp, "%d;%s;%s;%d;%s;%s;%s;%d\n",c.id, c.nom, c.adresse,c.nb_salles, c.telephone, c.email,c.type, c.capacite);
        }
    }

    fclose(f);
    fclose(tmp);

    remove(filename);
    rename("tmp.txt", filename);

    return found;
}

// SUPPRIMER 
int supprimer_centre(char *filename_centres, char *filename_inscriptions, int id)
{
    // --- Step 1: Delete the centre from centres file ---
    FILE *f = fopen(filename_centres, "r");
    FILE *tmp = fopen("tmp_centres.txt", "w");
    if (!f || !tmp) {
        if (f) fclose(f);
        if (tmp) fclose(tmp);
        return 0;
    }

    Centre c, deleted;
    int found = 0;

    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles, c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        if (c.id == id) {
            found = 1;
            deleted = c; // store the deleted centre
        } else {
            fprintf(tmp, "%d;%s;%s;%d;%s;%s;%s;%d\n",
                    c.id, c.nom, c.adresse, c.nb_salles, c.telephone, c.email, c.type, c.capacite);
        }
    }

    fclose(f);
    fclose(tmp);

    if (!found) {
        remove("tmp_centres.txt");
        return 0; // centre not found
    }

    remove(filename_centres);
    rename("tmp_centres.txt", filename_centres);

    // --- Step 2: Delete inscriptions of the deleted centre ---
    FILE *fi = fopen(filename_inscriptions, "r");
    FILE *t2 = fopen("tmp_insc.txt", "w");
    if (!fi || !t2) {
        if (fi) fclose(fi);
        if (t2) fclose(t2);
        return 1; // centre deleted, inscriptions untouched
    }

    int id_insc;
    char nom[100], adresse[200], spec[100];
    int j, m, a, hh, mm;

    while (fscanf(fi, "%d;%99[^;];%199[^;];%99[^;];%d/%d/%d;%d:%d\n",
                  &id_insc, nom, adresse, spec, &j, &m, &a, &hh, &mm) == 9)
    {
        // Keep inscriptions NOT related to the deleted centre
        if (strcmp(nom, deleted.nom) != 0 || strcmp(adresse, deleted.adresse) != 0)
        {
            fprintf(t2, "%d;%s;%s;%s;%02d/%02d/%04d;%02d:%02d\n",
                    id_insc, nom, adresse, spec, j, m, a, hh, mm);
        }
    }

    fclose(fi);
    fclose(t2);

    remove(filename_inscriptions);
    rename("tmp_insc.txt", filename_inscriptions);

    return 1; // success
}
// CHERCHER
Centre chercher_centre(char *filename, int id)
{
    Centre c;
    c.id = -1;

    FILE *f = fopen(filename, "r");
    if (!f) return c;

    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",&c.id, c.nom, c.adresse, &c.nb_salles,c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        if (c.id == id) {
            fclose(f);
            return c;
        }
    }

    fclose(f);
    c.id = -1;
    return c;
}


int inscriptions_meme_creneau(char *fichier_inscriptions, Centre c, Date d, Heure h)
{
    FILE *f = fopen(fichier_inscriptions, "r");
    if (!f) return 0;

    int id;
    char nom[100], adresse[200], spec[100];
    int j, m, a, hh, mm;
    int count = 0;

    while (fscanf(f, "%d;%99[^;];%199[^;];%99[^;];%d/%d/%d;%d:%d\n",
                  &id, nom, adresse, spec, &j, &m, &a, &hh, &mm) == 9)
    {
        if (strcmp(nom, c.nom) == 0 &&
            strcmp(adresse, c.adresse) == 0 &&
            j == d.jour && m == d.mois && a == d.annee &&
            hh == h.heure && mm == h.minute)
        {
            count++;
        }
    }

    fclose(f);
    return count;
}




// AJOUTER INSCRIPTION 
int ajouter_inscription(char *fichier_inscriptions, char *fichier_centres, Inscription i)
{
    FILE *f = fopen(fichier_centres, "r");
    if (!f) return 0;

    Centre c;
    int found = 0;

    // Search for the centre by name + address
    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",
                  &c.id, c.nom, c.adresse, &c.nb_salles,
                  c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        if (strcmp(c.nom, i.nom_centre) == 0 &&
            strcmp(c.adresse, i.adresse) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(f);

    if (!found) return 2; // Centre does not exist
    int nb = inscriptions_meme_creneau(fichier_inscriptions, c, i.date, i.heure);
    if (nb >= c.nb_salles)
    	return 3;
    // Append the new inscription
    f = fopen(fichier_inscriptions, "a");
    if (!f) return 0;

    fprintf(f, "%d;%s;%s;%s;%02d/%02d/%04d;%02d:%02d\n",
            i.id,
            i.nom_centre,
            i.adresse,
            i.specialite,
            i.date.jour,
            i.date.mois,
            i.date.annee,
            i.heure.heure,
            i.heure.minute);

    fclose(f);
    return 1;
}

// NOMBRE TOTAL
int nombre_total_centres(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) return 0;

    int count = 0;
    Centre c;

    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",&c.id, c.nom, c.adresse, &c.nb_salles,c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        count++;
    }

    fclose(f);
    return count;
}

// NOMBRE D’INSCRIPTIONS PAR CENTRE
int nombre_inscriptions_par_centre(char *fichier_inscriptions, Centre c)
{
    FILE *f = fopen(fichier_inscriptions, "r");
    if (!f) return 0;

    int id_insc;
    char nom[100], adresse[200], specialite[100];
    int jour, mois, annee, heure, minute;
    int count = 0;

    // Use / for date and : for time
    while (fscanf(f, "%d;%99[^;];%199[^;];%99[^;];%d/%d/%d;%d:%d\n",
                  &id_insc, nom, adresse, specialite,
                  &jour, &mois, &annee, &heure, &minute) == 9)
    {
        if (strcmp(nom, c.nom) == 0 && strcmp(adresse, c.adresse) == 0)
            count++;
    }

    fclose(f);
    return count;
}
// CENTRE AVEC LE PLUS D’INSCRIPTIONS
int centre_plus_dinscriptions(char *fichier_centres, char *fichier_inscriptions)
{
    FILE *f = fopen(fichier_centres, "r");
    if (!f) return -1;

    Centre c;
    int max_insc = -1;
    int id_max = -1;

    while (fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",&c.id, c.nom, c.adresse, &c.nb_salles,c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        int n = nombre_inscriptions_par_centre(fichier_inscriptions, c);
        if (n > max_insc)
        {
            max_insc = n;
            id_max = c.id;
        }
    }

    fclose(f);
    return id_max;
}

// STATISTIQUES
void statistiques(char *fichier_centres, char *fichier_inscriptions, Stats *s)
{
    s->total_centres = nombre_total_centres(fichier_centres);
    s->nb_centres = 0;

    FILE *f = fopen(fichier_centres, "r");
    if (!f) return;

    Centre c;

    while (s->nb_centres < 100 &&
           fscanf(f, "%d;%99[^;];%199[^;];%d;%29[^;];%99[^;];%49[^;];%d\n",&c.id, c.nom, c.adresse, &c.nb_salles,c.telephone, c.email, c.type, &c.capacite) == 8)
    {
        s->ids[s->nb_centres] = c.id;
        strcpy(s->noms[s->nb_centres], c.nom);
        strcpy(s->adresses[s->nb_centres], c.adresse);
        s->inscriptions[s->nb_centres] =nombre_inscriptions_par_centre(fichier_inscriptions, c);

        s->nb_centres++;
    }

    fclose(f);

    s->id_max = centre_plus_dinscriptions(fichier_centres, fichier_inscriptions);
}


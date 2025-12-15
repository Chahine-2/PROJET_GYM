#include <stdio.h>
#include <string.h>
#include "user.h"

char file_users[] = "user.txt";


void encode(char *pass) {
    for (int i = 0; pass[i] != '\0'; i++) {
        pass[i] = pass[i] + 3;
    }
}

void decode(char *pass) {
    for (int i = 0; pass[i] != '\0'; i++) {
        pass[i] = pass[i] - 3;
    }
}


int username_exists(char *username) {
    FILE *f = fopen(file_users, "r");
    if (!f) return 0;

    User u;
    while (fscanf(f, "%49s %49s %d %99s %19s %49s %49s %19s",u.nom, u.prenom, &u.age, u.email, u.tel,u.username, u.password, u.role) != EOF)
    {
        if (strcmp(username, u.username) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}


int add_user(User u) {
    if (username_exists(u.username)) {
        return 0; 
    }

    FILE *f = fopen(file_users, "a");
    if (!f) return -1;

    char encoded_pass[50];
    strcpy(encoded_pass, u.password);
    encode(encoded_pass);

    fprintf(f, "%s %s %d %s %s %s %s %s\n",u.nom,u.prenom,u.age,u.email,u.tel,u.username,encoded_pass,u.role);

    fclose(f);
    return 1;
}


int authenticate( char *username, char *password, User *out) {
    FILE *f = fopen(file_users, "r");
    if (!f) return -1;

    User u;
    while (fscanf(f, "%49s %49s %d %99s %19s %49s %49s %19s",u.nom, u.prenom, &u.age, u.email, u.tel,u.username, u.password, u.role) != EOF)
    {
       
        decode(u.password);

        if (strcmp(username, u.username) == 0 &&
            strcmp(password, u.password) == 0)
        {
            if (out) *out = u;
            fclose(f);
            return 1; 
        }
    }

    fclose(f);
    return 0; 
}


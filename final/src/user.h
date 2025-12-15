#ifndef USER_H
#define USER_H

typedef struct {
    char nom[50];
    char prenom[50];
    int age;
    char email[100];
    char tel[20];
    char username[50];
    char password[50];
    char role[20];
} User;

int add_user(User u);  
int authenticate(char *username, char *password, User *out); 
int username_exists(char *username);

void encode(char *pass);
void decode(char *pass);

#endif


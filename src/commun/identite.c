#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "identite.h"

/*
    Identité d’une personne
*/
struct sIdentite
{
    int Identifiant; // Identifiant unique
    char * Nom; // Nom (chaîne de caractères allouée dynamiquement)
    char * Prenom; // Prénom (chaîne de caractères allouée dynamiquement)
    char Sexe; // ’F’ ou ’M’
    char DateNaissance[LG_DATE + 1]; // Date de naissance sous la forme jj/mm/aaaa
};

/*
    Crée une identité à partir des informations passées en paramètres, c’est-à-dire son 
    identifiant, son nom, son prénom, son sexe et sa date de naissance. 
*/
tIdentite IdentiteCreer(int Id, char *Nom, char *Prenom, char Sexe, char DateNais[]) {
    tIdentite id = malloc(sizeof(struct sIdentite));
    if (id == NULL) {
        fprintf(stderr, "identite.c:IdentiteCreer - Impossible d'allouer la mémoire\n");
        return NULL;
    }

    id->Identifiant = Id;

    id->Nom = malloc(sizeof(char) * (strlen(Nom)+1));
    if (id->Nom == NULL) return NULL;
    strcpy(id->Nom, Nom);
    
    id->Prenom = malloc(sizeof(char) * (strlen(Prenom)+1));
    if (id->Prenom == NULL) return NULL;
    strcpy(id->Prenom, Prenom);
    
    id->Sexe = Sexe;
    
    strcpy(id->DateNaissance, DateNais);

    return id;
}

/*
    Libère tout l’espace mémoire (les deux chaînes et la structure) occupé par l’identité 
    représentée par `Identite`.
*/
void IdentiteLiberer(tIdentite Identite) {
    if (Identite == NULL)
        return;
    free(Identite->Nom);
    free(Identite->Prenom);
    free(Identite);
}


/* 
    Retourne l’identifiant de la personne décrite par `Identite`.
*/
int IdentiteIdentifiant(tIdentite Identite) {
    return Identite->Identifiant;
}

/*
    Retourne l’adresse du premier caractère du nom de la personne décrite par `Identite`.
*/
char *IdentiteNom(tIdentite Identite) {
    return Identite->Nom;
}

/* 
    Retourne l’adresse du premier caractère du prénom de la personne décrite par `Identite`.
*/
char *IdentitePrenom(tIdentite Identite) {
    return Identite->Prenom;
}

/*
    Retourne le sexe (’F’ ou ’M’) de la personne décrite par Identite. */
char IdentiteSexe(tIdentite Identite) {
    return Identite->Sexe;
}

/* 
    Retourne l’adresse du premier caractère de la date de naissance de 
    la personne décrite par Identite. */
char *IdentiteDateNaissance(tIdentite Identite) {
    return Identite->DateNaissance;
}

/* 
    Affiche à l’écran les informations données par
    Identite sous la forme d’une ligne ayant le modèle suivant (␣ représente un 
    caractère espace) :
    ```
        [identifiant] nom prénom, sexe, date_de_naissance
    ```
    
    Avec l’exemple donné ci-dessus, cette fonction doit afficher la ligne :
    ``` 
        [16] DUFF John, M, 13/12/2001
    ``` 
*/
void IdentiteAfficher(tIdentite Identite) {
    if (Identite == NULL) {
        printf("[Identité vide]\n");
    } else {
        printf("[%d] %s %s, %c, %s\n",
            IdentiteIdentifiant(Identite),
            IdentiteNom(Identite),
            IdentitePrenom(Identite),
            IdentiteSexe(Identite),
            IdentiteDateNaissance(Identite)
        );
    }
}

/*
    Lit dans le fichier de texte d’identificateur `f` les informations constituant 
    l’identité d’une personne et retourne l’identité créée. 
    Cette fonction suppose que l’identité est décrite dans le fichier selon le format 
    dans lequel chaque information est sur une ligne constituée d’au plus 80 caractères, 
    les lignes étant placées dans l’ordre suivant :   
    ```
        identifiant  
        nom  
        prénom  
        sexe  
        date de naissance  
    ```  

    Cette fonction doit retourner `NULL` s’il n’y a plus d’informations à lire dans le 
    fichier, c’est-à-dire si une ligne vide (constituée uniquement du caractère \n) est 
    lue ou si la fin du fichier est atteinte.
    Le fichier personne.ind contient les informations correspondant à l’exemple ci-dessus 
    écrites dans ce format.
*/
tIdentite IdentiteLiref(FILE *f) {
    if (f == NULL) {
        fprintf(stderr, "identite.c:IdentiteLiref - Fichier invalide\n");
        return NULL;
    }

    int id;
    char nom[LG_LIGNE_FICHIER_MAX + 1];
    char prenom[LG_LIGNE_FICHIER_MAX + 1];
    char sexe;
    char naissance[LG_DATE + 1];

    if (fscanf(f, "%d", &id) != 1)
        return NULL;
    if (fscanf(f, "%80s", nom) != 1)
        return NULL;
    if (fscanf(f, "%80s", prenom) != 1)
        return NULL;
    fgetc(f);
    sexe = fgetc(f);
    if (sexe == EOF)
        return NULL;
    if (fscanf(f, "%10s", naissance) != 1)
        return NULL;

    tIdentite identite = IdentiteCreer(id, nom, prenom, sexe, naissance);
    return identite;
}

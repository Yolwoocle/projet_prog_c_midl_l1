#include <stdio.h>
#include <stdlib.h>
#include "identite.h"
#include "genea.h"

// Arbre généalogique
struct sArbre {
    struct sFiche * pPremiere; // Adresse de la première fiche
    struct sFiche * pDerniere; // Adresse de la dernière fiche
};
// Fiche associée à chaque individu présent dans l’arbre
struct sFiche {
    tIdentite Identite; // Accès aux informations de l’identité de la personne
    struct sFiche * pPere; // Adresse de la fiche du père
    struct sFiche * pMere; // Adresse de la fiche de la mère
    struct sFiche * pSuivante; // Adresse de la fiche suivante
};

/*
    Crée un arbre généalogique vide et retourne l’arbre créé ou `NULL` en
    cas de problème d’allocation mémoire
*/
tArbre ArbreCreer(void) {
    tArbre arbre = malloc(sizeof(struct sArbre));
    if (arbre == NULL) {
        perror("Impossible d'allouer la mémoire pour l'arbre");
        return NULL;
    }
    arbre->pPremiere = NULL;
    arbre->pDerniere = NULL;
    return arbre;
}

/*
    Affiche à l’écran les informations contenues dans l’arbre représenté par `Arbre`.
*/
void ArbreAfficher(tArbre Arbre) {
    if (Arbre == NULL || Arbre->pPremiere == NULL) {
        printf("[Arbre vide]\n");
        return;
    }
    struct sFiche * fiche = Arbre->pPremiere;

    while (fiche != NULL) {
        IdentiteAfficher(fiche->Identite);
        printf("\tPère : ");
        if (fiche->pPere == NULL)
            printf("inconnu\n");
        else
            IdentiteAfficher(fiche->pPere->Identite);

        printf("\tMère : ");
        if (fiche->pMere == NULL)
            printf("inconnue\n");
        else
            IdentiteAfficher(fiche->pMere->Identite);


        fiche = fiche->pSuivante;
    } 
}

/*
    Crée une fiche, ou `NULL` en cas de problème avec l'allocation mémoire.
*/
struct sFiche * FicheCreer(tIdentite identite, struct sFiche * pPere, struct sFiche * pMere, struct sFiche * pSuivante) {
    struct sFiche * fiche = malloc(sizeof(struct sFiche));
    if (fiche == NULL)
        return NULL;

    fiche->Identite = identite;
    fiche->pPere = pPere;
    fiche->pMere = pMere;
    fiche->pSuivante = pSuivante;

    return fiche;
}

/*
    Libère l'espace mémoire occupé par `fiche`.
*/
void FicheLiberer(struct sFiche * fiche) {
    IdentiteLiberer(fiche->Identite);
    free(fiche);
}

/*
    Renvoie la dernière fiche non nulle d'`Arbre`, ou `NULL` s'il n'y en a pas dans l'arbre.
*/
struct sFiche * ObtenirDerniereFiche(tArbre Arbre) {  
    if (Arbre->pPremiere == NULL)
        return NULL;

    struct sFiche * ficheActuelle = Arbre->pPremiere;
    while (ficheActuelle->pSuivante != NULL) {
        ficheActuelle = ficheActuelle->pSuivante;
    }

    return ficheActuelle;
}

/*
    Ajoute une personne d’identité `Identite` dans l’arbre `Arbre`. Cet ajout doit se faire 
    à la fin de la liste des personnes. En cas de problème d’allocation mémoire, l’exécution 
    ne doit pas être interrompue mais un message d’erreur doit être affiché sur la sortie 
    standard des erreurs.
*/
void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite) {
    if (Arbre == NULL || Identite == NULL) {
        perror("ArbreAjouterPersonne : Arbre NULL");
        return;
    }
    
    struct sFiche * fiche = FicheCreer(Identite, NULL, NULL, NULL);
    struct sFiche * derniereFiche = ObtenirDerniereFiche(Arbre);
    if (derniereFiche == NULL) {
        Arbre->pPremiere = fiche;
        Arbre->pDerniere = fiche;
    } else {
        derniereFiche->pSuivante = fiche;
        Arbre->pDerniere = fiche;
    }
}

/*
    Libère tout l’espace mémoire (y compris les identités) occupé
    par l’arbre représenté par Arbre.
*/
void ArbreLiberer(tArbre Arbre) {
    struct sFiche * ficheActuelle = Arbre->pPremiere;
           
    while (ficheActuelle != NULL) {
        struct sFiche * ficheSuivante = ficheActuelle->pSuivante;
        FicheLiberer(ficheActuelle);

        ficheActuelle = ficheSuivante;
    }

    free(Arbre);
}

/*
    Crée un arbre généalogique à partir d’une liste d’identités de personnes 
    stockées dans le fichier de texte de désignation ``Fichier``. 
    Cette fonction doit retourner l’arbre créé ou `NULL` en cas de problème. 
    Les personnes doivent être ajoutées en fin de liste au fur et à mesure 
    de la lecture dans le fichier. Le fichier ne contenantpas d’information 
    sur les liens de parenté, ils doivent être initialisés à `NULL`.
*/
tArbre ArbreLirePersonnesFichier(char Fichier[]) {
    printf("1 Lecture\n");
    FILE *file = fopen(Fichier, "rt");
    if (file == NULL) {
        perror("Fichier inconnu");
        return NULL;
    }

    printf("2 Lecture\n");
    tArbre arbre = ArbreCreer();
    if (arbre == NULL)
        return NULL;

    printf("3 Lecture\n");
    int i = 0;
    printf("4 Lecture\n");
    while (i == 0) {
        tIdentite identite = IdentiteLiref(file);
        if (identite == NULL)
            i++;
        else
            ArbreAjouterPersonne(arbre, identite);
    }
    printf("5 Lecture\n");

    fclose(file);

    printf("6 Lecture\n");
    return arbre;
}
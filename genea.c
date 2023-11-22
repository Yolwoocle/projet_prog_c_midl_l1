#include <stdio.h>
#include <stdlib.h>
#include "identite.h"
#include "genea.h"

// Arbre généalogique
struct sArbre
{
    struct sFiche * pPremiere ; // Adresse de la première fiche
    struct sFiche * pDerniere ; // Adresse de la dernière fiche
};
// Fiche associée à chaque individu présent dans l’arbre
struct sFiche
{
    tIdentite Identite ; // Accès aux informations de l’identité de la personne
    struct sFiche * pPere ; // Adresse de la fiche du père
    struct sFiche * pMere ; // Adresse de la fiche de la mère
    struct sFiche * pSuivante ; // Adresse de la fiche suivante
};

/*
    Crée un arbre généalogique vide et retourne l’arbre créé ou `NULL` en
    cas de problème d’allocation mémoire
*/
tArbre ArbreCreer(void) {
    tArbre arbre = malloc(sizeof(struct sArbre));
    arbre->pPremiere = malloc(sizeof(struct sFiche));
    arbre->pDerniere = malloc(sizeof(struct sFiche));
    return arbre;
}
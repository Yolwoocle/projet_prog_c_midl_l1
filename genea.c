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
    arbre->pPremiere = NULL;
    arbre->pDerniere = NULL;
    return arbre;
}

/*
    Affiche à l’écran les informations contenues dans l’arbre
    représenté par Arbre. Cette fonction doit afficher, pour chaque personne présente dans l’arbre,
    les informations sous la forme des trois lignes suivantes :
    identité de la personne
    7−→Père : identité du père de la personne
    7−→Mère : identité de la mère de la personne
    où 7−→ représente le caractère tabulation (’\t’) et les identités sont affichées selon le format de
    la fonction IdentiteAfficher du module identite. Si un parent n’est pas présent dans l’arbre,
    c’est le mot inconnu qui doit être affiché à la place de son identité.
    Voici le résultat de l’affichage de l’arbre généalogique constitué des quatre personnes citées
    précédemment :
    ```
        [122] DUBOURG Pierre , M , 15/12/1910
        P è re : [18] DUBOURG Jean , M , 21/07/1866
        M è re : [19] COURBIN Marthe , F , 22/04/1872
        [9] DUBOURG Catherine , F , 21/08/1904
        P è re : [18] DUBOURG Jean , M , 21/07/1866
        M è re : [19] COURBIN Marthe , F , 22/04/1872
        [19] COURBIN Marthe , F , 22/04/1872
        P è re : inconnu
        M è re : inconnue
        [18] DUBOURG Jean , M , 21/07/1866
        P è re : inconnu
        M è re : inconnue
    ```
*/
void ArbreAfficher(tArbre Arbre) {
    struct sFiche * fiche = Arbre->pPremiere;
    //todo fiche == null
    while (fiche->pSuivante != NULL) {
        IdentiteAfficher(fiche->Identite);
        printf("\tPère : ");
        IdentiteAfficher(fiche->pPere->Identite);
        printf("\n");
        printf("\tMère : ");
        IdentiteAfficher(fiche->pMere->Identite);

        fiche = fiche->pSuivante;
    } 
}
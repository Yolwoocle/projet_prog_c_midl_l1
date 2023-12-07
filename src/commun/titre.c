#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titre.h"

#define LONG_MAX_TITRE 70


/*
 * Affiche un séparateur sous la forme `"-----------------"`.
 */
void printSep() {
    for (int i = 0; i < LONG_MAX_TITRE; i++) {
        printf("-");
    }
    printf("\n");
}

/*
 * Affiche un texte sous la forme `"xxxxx| (string) |xxxxx"`, avec `'x'` remplacé par `charLigne`.
 */
static void printTitreGenerique(char texte[], char charLigne) {
    int longTitre = strlen(texte);
    int longLigne = (LONG_MAX_TITRE - longTitre) / 2;

    // Affichage de la ligne de gauche
    int i = 0;
    while (i < longLigne-2) {
        printf("%c", charLigne);
        i++;
    }

    // Affichage du texte
    printf("| %s |", texte);
    i += longTitre + 4;

    // Affichage de la ligne de droite
    while (i < LONG_MAX_TITRE) {
        printf("%c", charLigne);
        i++;
    }
    printf("\n");
}

/*
 * Affiche un texte sous la forme `"=====| (texte) |====="`.
 */
void printTitre(char texte[]) {
    printTitreGenerique(texte, '=');
}

/*
 * Affiche un texte sous la forme `"-----| (string) |-----"`.
 */
void printSousTitre(char texte[]) {
    printTitreGenerique(texte, '-');
}
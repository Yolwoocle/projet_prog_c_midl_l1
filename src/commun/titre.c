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
 * Affiche un titre sous la forme `"=====| (string) |===="`.
 */
void printTitre(char titre[]) {
    int longTitre = strlen(titre);
    int longLigne = (LONG_MAX_TITRE - longTitre) / 2;

    // Affichage de la ligne de gauche
    int i = 0;
    while (i < longLigne-2) {
        printf("=");
        i++;
    }

    // Affichage du titre
    printf("| %s |", titre);
    i += longTitre + 4;

    // Affichage de la ligne de droite
    while (i < LONG_MAX_TITRE) {
        printf("=");
        i++;
    }
    printf("\n");
}
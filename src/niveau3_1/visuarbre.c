#include <string.h>
#include "identite.h"
#include "genea.h"
#include "titre.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Nombre invalide d'arguments.\n");
        return 0;
    }
    printTitre("Test de lecture d'un arbre généalogique");

    char * nomFichPersonnes = argv[1];
    char * nomFichLiensParente = argv[2];
    tArbre arbre = ArbreLirePersonnesFichier(nomFichPersonnes);

    ArbreAfficher(arbre);
    printSep();
    ArbreLireLienParenteFichier(arbre, nomFichLiensParente);
    ArbreAfficher(arbre);

    ArbreLiberer(arbre);
    printTitre("OK");
    return 0;
}
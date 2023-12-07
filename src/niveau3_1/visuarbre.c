#include "identite.h"
#include "genea.h"
#include "titre.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Nombre invalide d'arguments. Format: \"./visuarbre fichier-personnes fichier-liens-parente fichier-dot\"\n");
        return 0;
    }
    printTitre("Test de visualisation d'arbre avec le format DOT");

    char * nomFichPersonnes = argv[1];
    char * nomFichLiensParente = argv[2];
    char * nomFichDot = argv[3];

    tArbre arbre = ArbreLirePersonnesFichier(nomFichPersonnes);
    ArbreLireLienParenteFichier(arbre, nomFichLiensParente);

    ArbreEcrireGV(arbre, nomFichDot);

    printSep();
    ArbreAfficherAscendants(arbre, 4);
    ArbreEcrireAscendantsGV(arbre, 4, "data/ascendant_id4.dot");

    ArbreLiberer(arbre);
    printTitre("OK");
    return 0;
}
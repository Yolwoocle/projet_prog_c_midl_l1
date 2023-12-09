#include "identite.h"
#include "genea.h"
#include "titre.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Nombre invalide d'arguments. Format : \"./visuarbreasc fichier-personnes fichier-liens-parente identifiant fichier-dot\"\n");
        return 0;
    }
    printTitre("Test sur les arbres généalogiques ascendants");

    char * nomFichPersonnes = argv[1];
    char * nomFichLiensParente = argv[2];
    int identifiant;
    sscanf(argv[3], "%d", &identifiant);
    char * nomFichDot = argv[4];

    tArbre arbre = ArbreLirePersonnesFichier(nomFichPersonnes);
    ArbreLireLienParenteFichier(arbre, nomFichLiensParente);

    ArbreAfficherAscendants(arbre, identifiant);
    ArbreEcrireAscendantsGV(arbre, identifiant, nomFichDot);

    ArbreLiberer(arbre);
    printTitre("OK");
    return 0;
}
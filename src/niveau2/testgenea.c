#include <string.h>
#include "identite.h"
#include "genea.h"
#include "titre.h"

void test_arbre1() {
    printTitre("Identités en jeu");
    tIdentite identiteCena = IdentiteCreer(69, "CENA", "John", 'M', "11/11/1111");
    IdentiteAfficher(identiteCena);
    tIdentite identitePapa = IdentiteCreer(12, "PIG", "Papa", 'M', "11/11/1111");
    IdentiteAfficher(identitePapa);
    tIdentite identiteMama = IdentiteCreer(2, "PIG", "Mama", 'F', "11/11/1111");
    IdentiteAfficher(identiteMama);

    printf("\n");
    printTitre("Arbre");
    tArbre arbre = ArbreCreer();
    ArbreAjouterPersonne(arbre, identiteCena);
    ArbreAjouterPersonne(arbre, identitePapa);
    ArbreAjouterPersonne(arbre, identiteMama);
    ArbreAfficher(arbre);

    ArbreLiberer(arbre);
}

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

    ArbreEcrireGV(arbre, "data/arbre4.dot");

    printSep();
    ArbreAfficherAscendants(arbre, 4);
    ArbreEcrireAscendantsGV(arbre, 4, "data/ascendant_id4.dot");

    ArbreLiberer(arbre);
    printTitre("OK");
    return 0;
}










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
        printf("Nombre invalide d'arguments. Format : \"./testgenea fichier-personnes fichier-liens-parente\"\n");
        return 0;
    }
    printTitre("Test de lecture d'un arbre généalogique");

    char * nomFichPersonnes = argv[1];
    char * nomFichLiensParente = argv[2];
    tArbre arbre = ArbreLirePersonnesFichier(nomFichPersonnes);

    ArbreAfficher(arbre);
    printSousTitre("Lecture des liens de parenté");
    ArbreLireLienParenteFichier(arbre, nomFichLiensParente);
    ArbreAfficher(arbre);

    ArbreLiberer(arbre);
    printTitre("OK");
    return 0;
}
#include "identite.h"
#include "genea.h"

void print_titre(char string[]) {
    printf("=====| %s |=====\n", string);
}

int main(void) {

    print_titre("Identités en jeu");
    tIdentite identiteCena = IdentiteCreer(69, "CENA", "John", 'M', "11/11/1111");
    IdentiteAfficher(identiteCena);
    tIdentite identitePapa = IdentiteCreer(12, "PIG", "Papa", 'M', "11/11/1111");
    IdentiteAfficher(identitePapa);
    tIdentite identiteMama = IdentiteCreer(2, "PIG", "Mama", 'F', "11/11/1111");
    IdentiteAfficher(identiteMama);

    printf("\n");
    print_titre("Arbre");
    tArbre arbre = ArbreCreer();
    ArbreAjouterPersonne(arbre, identiteCena);
    ArbreAjouterPersonne(arbre, identitePapa);
    ArbreAjouterPersonne(arbre, identiteMama);
    ArbreAfficher(arbre);
    
    ArbreLiberer(arbre);
    return 0;
}
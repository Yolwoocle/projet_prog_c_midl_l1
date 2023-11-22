#include "identite.h"

int main(void) {
    tIdentite identite = IdentiteCreer(69, "cena", "john", 'M', "11/11/1111");
    
    IdentiteIdentifiant(identite);
    IdentiteNom(identite);
    IdentitePrenom(identite);
    IdentiteSexe(identite);
    IdentiteDateNaissance(identite);

    IdentiteLiberer(identite);
    return 0;
}
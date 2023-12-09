#include <stdio.h>
#include <stdlib.h>
#include "identite.h"
#include "titre.h"

int main(void) {
    printTitre("Test du module identite");
    {
        tIdentite identite = IdentiteCreer(2, "Cena", "John", 'M', "23/04/1977");

        printf("Identitfiant = %d\n", IdentiteIdentifiant(identite));
        printf("Nom = %s\n", IdentiteNom(identite));
        printf("Prenom = %s\n", IdentitePrenom(identite));
        printf("Sexe = %c\n", IdentiteSexe(identite));
        printf("Date de naissance = %s\n", IdentiteDateNaissance(identite));
        IdentiteAfficher(identite);

        IdentiteLiberer(identite);
    }

    printSep();
    
    {
        printf("Lecture de personne.ind\n");
        FILE * f = fopen("personne.ind", "rt");
        tIdentite identite_fich = IdentiteLiref(f);

        IdentiteAfficher(identite_fich);

        fclose(f);
        IdentiteLiberer(identite_fich);
    }

    printTitre("OK");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "identite.h"

int main(void) {
    printf("====| Test du module identite... |====\n");
    {
        tIdentite identite = IdentiteCreer(2, "Cena", "John", 'M', "01/01/2000");

        printf("Identitfiant = %d\n", IdentiteIdentifiant(identite));
        printf("Nom = %s\n", IdentiteNom(identite));
        printf("Prenom = %s\n", IdentitePrenom(identite));
        printf("Sexe = %c\n", IdentiteSexe(identite));
        printf("Date de naissance = %s\n", IdentiteDateNaissance(identite));
        IdentiteAfficher(identite);

        IdentiteLiberer(identite);
    }
    {
        FILE * f = fopen("personne.ind", "rt");
        tIdentite identite_fich = IdentiteLiref(f);

        IdentiteAfficher(identite_fich);

        fclose(f);
        IdentiteLiberer(identite_fich);
    } 

    printf("================| OK |================\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "identite.h"
#include "genea.h"

// Arbre généalogique
struct sArbre {
    struct sFiche * pPremiere; // Adresse de la première fiche
    struct sFiche * pDerniere; // Adresse de la dernière fiche
};
// Fiche associée à chaque individu présent dans l’arbre
struct sFiche {
    tIdentite Identite; // Accès aux informations de l’identité de la personne
    struct sFiche * pPere; // Adresse de la fiche du père
    struct sFiche * pMere; // Adresse de la fiche de la mère
    struct sFiche * pSuivante; // Adresse de la fiche suivante
};

/*
    Crée un arbre généalogique vide et retourne l’arbre créé ou `NULL` en
    cas de problème d’allocation mémoire
*/
tArbre ArbreCreer(void) {
    tArbre arbre = malloc(sizeof(struct sArbre));
    if (arbre == NULL) {
        free(arbre);
        fprintf(stderr, "genea.c:ArbreCreer - Impossible d'allouer la mémoire pour l'arbre\n");
        return NULL;
    }
    arbre->pPremiere = NULL;
    arbre->pDerniere = NULL;
    return arbre;
}

/*
    Affiche à l’écran les informations contenues dans l’arbre représenté par `Arbre`.
*/
void ArbreAfficher(tArbre Arbre) {
    if (Arbre == NULL || Arbre->pPremiere == NULL) {
        printf("[Arbre vide]\n");
        return;
    }
    struct sFiche * fiche = Arbre->pPremiere;

    while (fiche != NULL) {
        IdentiteAfficher(fiche->Identite);
        printf("\tPère : ");
        if (fiche->pPere == NULL)
            printf("inconnu\n");
        else
            IdentiteAfficher(fiche->pPere->Identite);

        printf("\tMère : ");
        if (fiche->pMere == NULL)
            printf("inconnue\n");
        else
            IdentiteAfficher(fiche->pMere->Identite);


        fiche = fiche->pSuivante;
    } 
}

/*
    Crée une fiche, ou `NULL` en cas de problème avec l'allocation mémoire.
*/
struct sFiche * FicheCreer(tIdentite identite, struct sFiche * pPere, struct sFiche * pMere, struct sFiche * pSuivante) {
    struct sFiche * fiche = malloc(sizeof(struct sFiche));
    if (fiche == NULL)
        return NULL;

    fiche->Identite = identite;
    fiche->pPere = pPere;
    fiche->pMere = pMere;
    fiche->pSuivante = pSuivante;

    return fiche;
}

/*
    Libère l'espace mémoire occupé par `fiche`.
*/
void FicheLiberer(struct sFiche * fiche) {
    IdentiteLiberer(fiche->Identite);
    free(fiche);
}

/*
    Renvoie la dernière fiche non nulle d'`Arbre`, ou `NULL` s'il n'y en a pas dans l'arbre.
*/
struct sFiche * ObtenirDerniereFiche(tArbre Arbre) {  
    if (Arbre->pPremiere == NULL)
        return NULL;

    struct sFiche * ficheActuelle = Arbre->pPremiere;
    while (ficheActuelle->pSuivante != NULL) {
        ficheActuelle = ficheActuelle->pSuivante;
    }

    return ficheActuelle;
}

/*
    Ajoute une personne d’identité `Identite` dans l’arbre `Arbre`. Cet ajout doit se faire 
    à la fin de la liste des personnes. En cas de problème d’allocation mémoire, l’exécution 
    ne doit pas être interrompue mais un message d’erreur doit être affiché sur la sortie 
    standard des erreurs.
*/
void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite) {
    if (Arbre == NULL || Identite == NULL) {
        fprintf(stderr, "genea.c:ArbreAjouterPersonne - Arbre est égal à NULL\n");
        return;
    }
    
    struct sFiche * fiche = FicheCreer(Identite, NULL, NULL, NULL);
    struct sFiche * derniereFiche = ObtenirDerniereFiche(Arbre);
    if (derniereFiche == NULL) {
        Arbre->pPremiere = fiche;
        Arbre->pDerniere = fiche;
    } else {
        derniereFiche->pSuivante = fiche;
        Arbre->pDerniere = fiche;
    }
}

/*
    Libère tout l’espace mémoire (y compris les identités) occupé
    par l’arbre représenté par `Arbre`.
*/
void ArbreLiberer(tArbre Arbre) {
    struct sFiche * ficheActuelle = Arbre->pPremiere;
           
    while (ficheActuelle != NULL) {
        struct sFiche * ficheSuivante = ficheActuelle->pSuivante;
        FicheLiberer(ficheActuelle);

        ficheActuelle = ficheSuivante;
    }

    free(Arbre);
}

/*
    Crée un arbre généalogique à partir d’une liste d’identités de personnes 
    stockées dans le fichier de texte de désignation ``Fichier``. 
    Cette fonction doit retourner l’arbre créé ou `NULL` en cas de problème. 
    Les personnes doivent être ajoutées en fin de liste au fur et à mesure 
    de la lecture dans le fichier. Le fichier ne contenantpas d’information 
    sur les liens de parenté, ils doivent être initialisés à `NULL`.
*/
tArbre ArbreLirePersonnesFichier(char Fichier[]) {
    FILE *file = fopen(Fichier, "rt");
    if (file == NULL) {
        fprintf(stderr, "genea.c:ArbreLirePersonnesFichier - Fichier inconnu\n");
        return NULL;
    }

    tArbre arbre = ArbreCreer();
    if (arbre == NULL)
        return NULL;

    int lire = 1;
    int i = 0;
    
    while (lire == 1) {
        tIdentite identite = IdentiteLiref(file);
        if (identite == NULL)
            lire = 0;
        else
            ArbreAjouterPersonne(arbre, identite);
        i++;
    }

    fclose(file);

    return arbre;
}

/*
    Renoive un pointeur vers la fiche correspondant à l'identifiant `id`, ou `NULL` si aucun n'a été trouvé.
*/
struct sFiche * ObtenirFiche(tArbre Arbre, int id) {
    if (Arbre->pPremiere == NULL)
        return NULL;

    struct sFiche * ficheActuelle = Arbre->pPremiere;
    while (ficheActuelle != NULL) {
        if (IdentiteIdentifiant(ficheActuelle->Identite) == id) {
            return ficheActuelle;
        }
        ficheActuelle = ficheActuelle->pSuivante;
    }

    return NULL;
}

/*
    Ajoute dans l’arbre `Arbre` un lien de parenté entre l’enfant d’indentifiant `IdEnfant` et le parent
    d’indentifiant `IdParent`. Le type de lien de parenté est décrit par `Parente` qui peut valoir `'M'`
    pour « mère » ou `'P'` pour « père ». Si un identifiant n’est pas trouvé dans l’arbre, l’exécution ne
    doit pas être interrompue mais un message d’erreur doit être affiché sur la sortie standard des
    erreurs.
*/
void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente) {
    struct sFiche * ficheEnfant = ObtenirFiche(Arbre, IdEnfant);
    if (ficheEnfant == NULL) {
        fprintf(stderr, "genea.c:ArbreAjouterLienParente - Impossible de trouver la fiche avec identifiant %d pour l'enfant\n", IdEnfant);
        return;
    }

    struct sFiche * ficheParent = ObtenirFiche(Arbre, IdParent);
    if (ficheParent == NULL) {
        fprintf(stderr, "genea.c:ArbreAjouterLienParente - Impossible de trouver la fiche avec identifiant %d pour le parent\n", IdParent);
        return;
    }

    if (Parente == 'P') {
        ficheEnfant->pPere = ficheParent;
    } else if (Parente == 'M') {
        ficheEnfant->pMere = ficheParent;
    } else {
        fprintf(stderr, "genea.c:ArbreAjouterLienParente - Lien de parenté invalide : %c\n", Parente);
    }
}

/*
    Lit dans le fichier de texte d’identificateur `f` les informations constituant un lien de parenté et
    stocke l’identifiant de l’enfant à l’adresse `pIdEnfant`, l’identifiant du parent à l’adresse `pIdParent`
    et la parenté à l’adresse `pParente`.
    Cette fonction retourne 1 si la lecture s’est bien passée, et 0 s’il n’y a plus d’informations à lire
    dans le fichier, c’est-à-dire si une ligne vide (constituée uniquement du caractère `\n`) est lue, si
    la fin du fichier est atteinte ou en cas de problème.
    Cette fonction suppose que le lien de parenté est décrit dans le fichier sous la forme
    d’une ligne constituée de l’identifiant de l’enfant, l’identifiant du parent et le caractère F ou M,
    séparés par un espace. Par exemple, le fait que Marthe est la mère de Pierre sera représenté par
    la ligne suivante :
    ```
    122 19 M
    ```
*/
int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente) {
    if (f == NULL) {
        fprintf(stderr, "genea.c:ArbreLireLienParentef - Le fichier donné est NULL\n");
        return 0;
    }

    char ligne[LG_LIGNE_FICHIER_MAX + 1];
    char * fgetsout = fgets(ligne, LG_LIGNE_FICHIER_MAX, f);
    if (fgetsout == NULL) {
        return 0;
    }
    if (sscanf(ligne, "%d %d %c", pIdEnfant, pIdParent, pParente) != 3) {
        fprintf(stderr, "genea.c:ArbreLireLienParentef - Format invalide de ligne: \"%s\"\n", ligne);
        return 0;
    }

    return 1;
}

/*
    Ajoute à l’arbre `Arbre` les liens de parenté décrits dans le fichier de texte de désignation `Fichier`.
    Chaque lien de parenté est décrit dans le fichier par une ligne au format décrit pour la fonction
    `ArbreLireLienParentef`.
    Cette fonction retourne l’arbre modifié ou `NULL` en cas de problème.
*/
tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]) {
    FILE *f = fopen(Fichier, "rt");
    if (f == NULL) {
        fprintf(stderr, "genea.c:ArbreLireLienParenteFichier - Erreur lors de l'ouverture de \"%s\"\n", Fichier);
        return NULL;
    }
    int idEnfant;
    int idParent;
    char parente;

    int succes = 1;
    while (succes == 1) {
        succes = ArbreLireLienParentef(f, &idEnfant, &idParent, &parente);
        if (succes == 1) {
            ArbreAjouterLienParente(Arbre, idEnfant, idParent, parente);
        }
    }

    return Arbre;
}

/*
    Écrit une identité dans le fichier `f`, exemple :
    ```
    8 [label = "CHARLOT\nJacques\n08/04/1900"];
    ```
*/
void EcrireIdentite(FILE *f, tIdentite identite) {
    fprintf(f, "    %d [label = \"%s\\n%s\\n%s\"];\n",
            IdentiteIdentifiant(identite),
            IdentiteNom(identite),
            IdentitePrenom(identite),
            IdentiteDateNaissance(identite)
    );
}

/*
    Écrit dans le fichier `f` les personnes contenues dans l'arbre `arbre` de sexe `sexe`, sous le format DOT.
    Exemple de sortie :
    ```
        122 [label = "DUBOURG\nPierre\n15/12/1910"];
        18 [label = "DUBOURG\nJean\n21/07/1866"];
    ```
*/
void EcrirePersonnesFiltrerSexe(FILE *f, tArbre arbre, char sexe) {
    struct sFiche * fiche = arbre->pPremiere;
    while (fiche != NULL) {
        tIdentite identite = fiche->Identite;
        if (IdentiteSexe(identite) == sexe) {
            EcrireIdentite(f, identite);
        }
        fiche = fiche->pSuivante;
    }
}


/*
    Écrit dans le fichier `f` des arcs décrivant les liens de pârenté de la personne dans `fiché` sous le format DOT.
    Suppose que les nœuds correspondant aux personnes ont déjà été écrits dans le fichier `f`.
    Exemple de sortie si la personne d'ID 122 a comme parents 18 et 19 :
    ```
        122 -> 18;
        122 -> 19;
    ```
*/
void EcrireArcParente(FILE *f, struct sFiche * fiche) {
    if (fiche->pPere != NULL) {
        fprintf(f, "    %d -> %d;\n",
                IdentiteIdentifiant(fiche->Identite),
                IdentiteIdentifiant(fiche->pPere->Identite)
        );
    }
    if (fiche->pMere != NULL) {
        fprintf(f, "    %d -> %d;\n",
                IdentiteIdentifiant(fiche->Identite),
                IdentiteIdentifiant(fiche->pMere->Identite)
        );
    }
}


/*
    Écrit dans le fichier de texte de désignation `Fichier` l’arbre `Arbre` au format DOT 6 afin de pouvoir le
    visualiser grâce à l’outil de visualisation de graphe Graphviz 7.
*/
void ArbreEcrireGV(tArbre Arbre, char Fichier[]) {
    FILE *f = fopen(Fichier, "wt");
    if (f == NULL) {
        fprintf(stderr, "genea.c:ArbreEcrireGV - Erreur lors de l'ouverture de \"%s\"\n", Fichier);
        return;
    }

    fprintf(f, "digraph {\n");
    fprintf(f, "    rankdir = \"BT\";\n");
    fprintf(f, "    \n");
    fprintf(f, "    node [shape = box, fontname = \"Arial\", fontsize = 10];\n");
    EcrirePersonnesFiltrerSexe(f, Arbre, 'M');

    fprintf(f, "    \n");
    fprintf(f, "    node [color = green];\n");
    EcrirePersonnesFiltrerSexe(f, Arbre, 'F');

    fprintf(f, "    \n");
    fprintf(f, "    edge [dir = none];\n");
    struct sFiche * fiche = Arbre->pPremiere;
    while (fiche != NULL) {
        EcrireArcParente(f, fiche);
        fiche = fiche->pSuivante;
    }
    fprintf(f, "}");

    fclose(f);
}

void ArbreAfficherAscendantsRec(struct sFiche * fiche, int indentation) {
    if (fiche == NULL) {
        return;
    }

    IdentiteAfficher(fiche->Identite);

    if (fiche->pPere != NULL) {
        for (int i = 0; i < indentation+1; i++) {
            printf("\t");
        }
        printf("Père : ");
        ArbreAfficherAscendantsRec(fiche->pPere, indentation + 1);
    }
    if (fiche->pMere != NULL) {
        for (int i = 0; i < indentation+1; i++) {
            printf("\t");
        }
        printf("Mère : ");
        ArbreAfficherAscendantsRec(fiche->pMere, indentation + 1);
    }
}

/*
    Affiche à l’écran l’arbre généalogique ascendant (constitué de tous les ascendants) de la personne
    d’identifiant `Identifiant` contenu dans l’arbre `Arbre`. Si l’identifiant de la personne n’est pas
    présent dans l’arbre, l’exécution ne sera pas interrompue mais un message d’erreur sera affiché sur
    la sortie standard des erreurs.
*/
void ArbreAfficherAscendants(tArbre Arbre, int Identifiant) {
    struct sFiche * fiche = ObtenirFiche(Arbre, Identifiant);
    if (fiche == NULL) {
        fprintf(stderr, "genea.c:ArbreAfficherAscendants - L'arbre ne contient pas de personne avec l'identifiant %d.", Identifiant);
        return;
    }
    ArbreAfficherAscendantsRec(fiche, 0);
}


void ArbreEcrireAscendantsGVRec(FILE *f, struct sFiche * fiche) {
    if (fiche == NULL) {
        return;
    }

    fprintf(f, "    \n");
    fprintf(f, "    node [color = %s];\n", IdentiteSexe(fiche->Identite) == 'M' ? "blue" : "green");
    EcrireIdentite(f, fiche->Identite);

    if (fiche->pPere != NULL) {
        fprintf(f, "    %d -> %d;\n",
                IdentiteIdentifiant(fiche->Identite),
                IdentiteIdentifiant(fiche->pPere->Identite)
        );
    }
    if (fiche->pMere != NULL) {
        fprintf(f, "    %d -> %d;\n",
                IdentiteIdentifiant(fiche->Identite),
                IdentiteIdentifiant(fiche->pMere->Identite)
        );
    }

    if (fiche->pPere != NULL) {
        ArbreEcrireAscendantsGVRec(f, fiche->pPere);
    }
    if (fiche->pMere != NULL) {
        ArbreEcrireAscendantsGVRec(f, fiche->pMere);
    }
}

/*
    Écrit au format DOT dans le fichier de texte de désignation Fichier l’arbre généalogique ascendant de la
    personne d’identifiant Identifiant contenu dans l’arbre Arbre. Il est conseillé de faire appel à
    une fonction récursive pour réaliser cette écriture. Le contenu du fichier arbre10.dot au format
    DOT de l’arbre généalogique ascendant de Jean-Louis CHARLOT, extrait de l’arbre stocké dans
    les fichiers arbre10.ind et arbre10.par, peut être :
*/
void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]) {
    FILE *f = fopen(Fichier, "wt");
    if (f == NULL) {
        fprintf(stderr, "genea.c:ArbreEcrireGV - Erreur lors de l'ouverture de \"%s\"\n", Fichier);
        return;
    }

    fprintf(f, "digraph {\n");
    fprintf(f, "    rankdir = \"BT\";\n");
    fprintf(f, "    \n");
    fprintf(f, "    node [shape = box, fontname = \"Arial\", fontsize = 10];\n");
    fprintf(f, "    edge [dir = none];\n");

    ArbreEcrireAscendantsGVRec(f, ObtenirFiche(Arbre, Identifiant));

    fprintf(f, "    \n");
    fprintf(f, "}");

    fclose(f);
}

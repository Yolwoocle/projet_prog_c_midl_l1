#ifndef GENEA_H
#define GENEA_H

// Type permettant de manipuler un arbre généalogique
typedef struct sArbre * tArbre ;

tArbre ArbreCreer(void);
void ArbreAfficher(tArbre Arbre);
void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite);
void ArbreLiberer(tArbre Arbre);
tArbre ArbreLirePersonnesFichier(char Fichier[]);
void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente);
int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente);
tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]);

#endif
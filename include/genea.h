#ifndef GENEA_H
#define GENEA_H

// Type permettant de manipuler un arbre généalogique
typedef struct sArbre * tArbre ;
struct sFiche;

extern tArbre ArbreCreer(void);
extern void ArbreAfficher(tArbre Arbre);
extern void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite);
extern void ArbreLiberer(tArbre Arbre);
extern tArbre ArbreLirePersonnesFichier(char Fichier[]);
extern void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente);
extern int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente);
extern tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]);
extern void ArbreEcrireGV(tArbre Arbre, char Fichier[]);
extern void ArbreAfficherAscendants(tArbre Arbre, int Identifiant);
extern void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]);

static void EcrireIdentite(FILE *f, tIdentite identite);
static struct sFiche * ObtenirFiche(tArbre Arbre, int id);
static void EcrirePersonnesFiltrerSexe(FILE *f, tArbre arbre, char sexe);
static void EcrireArcParente(FILE *f, struct sFiche * fiche);
static void ArbreAfficherAscendantsRec(struct sFiche * fiche, int indentation);
static void ArbreEcrireAscendantsGVRec(FILE *f, struct sFiche * fiche);
#endif
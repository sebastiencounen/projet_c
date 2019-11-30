#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Structures
typedef struct Medecin Medecin;
typedef struct Patient Patient;

struct Medecin
{
    char numInami[15], nom[21], prenom[21];
    Medecin *next;
};

struct Patient
{
    int adNum, adCp;
    char regNat[16], nom[21], prenom[21], numTel[14], dateN[9], adRue[41], adVille[21];
    Patient *next;
};

// Prototype des fonctions

// Fonctions Menu
int menuPrincipal();
int menuMed();
int menuPat();

void afficherListeMed(Medecin *);
void afficherListePat(Patient *);

void ajouterMed(Medecin **, int *);
void ajouterPat(Patient **, int *);

void supprimerMed(Medecin **, int *);
void supprimerPat(Patient **, int *);

void rechercherMed(Medecin *);
void rechercherPat(Patient *);

void modifierMed(Medecin *);
void modifierPat(Patient *);

void sauvegarde(Medecin *, Patient *);

// Autres fonctions utilitaires
void majuscule(char *);
void clearBuffer();
int lire(char *, int);
int lireInt(char *, int);
long lireLong(char *, int);
int formatAndCompare(char *, char *);

#endif
#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Structures
typedef struct Medecin Medecin;
typedef struct Patient Patient;

struct Medecin
{
    long numInami;
    char nom[21], prenom[21], dateN[9];
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
int menu();

void afficherListeMed(Medecin *);
void afficherListePat(Patient *);

void ajouterMed(Medecin **, int*);
void ajouterPat(Patient **, int*);

void supprimerMed(Medecin **, int*);
void supprimerPat(Patient **, int*);

void rechercherMed(Medecin *);
void rechercherPat(Patient *);

void modifierMad(Medecin *);
void modifierPat(Patient *);

// Autres fonctions utilitaires
void majuscule(char *);
void clearBuffer();
int lire(char *, int);
int lireInt(char *, int);
// int lireFile(char *, int, FILE **);
long lireLong(char *, int);

#endif
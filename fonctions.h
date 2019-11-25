#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Structures
typedef struct Medecin Medecin;
typedef struct Patient Patient;

struct Medecin
{
    long numInami;
    char nom[30], prenom[30], dateN[9];
    Medecin *next;
};

struct Patient
{
    char regNat[16], nom[30], prenom[30], numTel[14], dateN[9];
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

#endif
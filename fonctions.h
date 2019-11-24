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
void afficherListeMed(Medecin *);
void afficherListePat(Patient *);

void ajouterMed(Medecin *);
void ajouterPat(Patient *);

void supprimerMed(Medecin *);
void supprimerPat(Patient *);

void rechercherMed(Medecin *);
void rechercherPat(Patient *);

int menu();
void majuscule(char *);

#endif
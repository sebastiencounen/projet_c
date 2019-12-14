#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Structures
typedef struct Medecin Medecin;
typedef struct Patient Patient;
typedef struct Consultation Consultation;
typedef struct Date Date;
typedef struct Adresse Adresse;

struct Date
{
    int jour, mois, annee;
};

struct Adresse
{
    int num;
    char cp[5], rue[41], ville[21];
};

struct Consultation
{
    // char nomMed[21];
    char nomPat[21];
};

struct Medecin
{
    char numInami[15], nom[21], prenom[21], specialite[21];
    Consultation cons[7][17];
    Medecin *next;
};

struct Patient
{
    char regNat[16], nom[21], prenom[21], numTel[14];
    Date dateN;
    Adresse adresse;
    Patient *next;
};

// Prototype des fonctions

//Lectures fichiers
void lectureMedecins(Medecin **, Medecin **, Medecin **, Medecin **, int *);
void lecturePatients(Patient **, Patient **, Patient **, Patient **, int *);

// Fonctions Menu
int menuPrincipal();
int menuMed();
int menuPat();

void afficherListeMed(Medecin *, int);
void afficherListePat(Patient *, int);
// void afficherListeCons(Consultation *);

void ajouterMed(Medecin **, Medecin **, Medecin **, int *);
void ajouterPat(Patient **, Patient **, Patient **, int *);
void ajouterCons(Patient *, Patient **, Medecin *, Medecin **);

void supprimerMed(Medecin **, int *);
void supprimerPat(Patient **, int *);
// void supprimerCons(Consultation **, int *);

void rechercherMed(Medecin *, Medecin **);
void rechercherPat(Patient *, Patient **);

void modifierMed(Medecin *);
void modifierPat(Patient *);

void sauvegarde(Medecin *, Patient *);

// Autres fonctions utilitaires
void majuscule(char *);
void clearBuffer();
int lire(char *, int);
int lireInt(char *, int);
long lireLong(char *, int);
int formatAndCompare(char *, char *, int);

#endif
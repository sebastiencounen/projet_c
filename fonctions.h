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
    char nomPat[21], lettrePrenPat;
};

struct Medecin
{
    char numInami[15], nom[21], prenom[21], specialite[21], nomenclature[7];
    Consultation cons[7][17];
    Medecin *next;
};

struct Patient
{
    char regNat[16], nom[21], prenom[21], numTel[14], sexe;
    Date dateN;
    Adresse adresse;
    Patient *next;
};

// Prototype des fonctions

//Lectures fichiers
int lectureMedecins(Medecin **, Medecin **, Medecin **, Medecin **, int *);
int lecturePatients(Patient **, Patient **, Patient **, Patient **, int *);

// Fonctions Menu
int menuPrincipal();
int menuMed();
int menuPat();

void afficherListeMed(Medecin *, int);
void afficherListePat(Patient *, int);

void ajouterMed(Medecin **, Medecin **, Medecin **, int *, char **, char **, int);
void ajouterPat(Patient **, Patient **, Patient **, int *);
void ajouterCons(Patient *, Patient **, Medecin *, Medecin **, int, char **);

void supprimerMed(Medecin **, int *);
void supprimerPat(Patient **, int *);
void supprimerCons(Medecin *, Medecin **, int, char **);

void rechercherMed(Medecin *, Medecin **, int, char **);
void rechercherPat(Patient *, Patient **);

void afficherHoraire(Medecin *, Medecin *);

void reinitialisationRDV(Medecin *);

void sauvegarde(Medecin *, Patient *);

void ajouterSpecialite(FILE *, int *, int *);

// Autres fonctions utilitaires
void majuscule(char *);
void clearBuffer();
int lire(char *, int);
void lireChar(char*);
int lireInt(char *, int);
long lireLong(char *, int);
int formatAndCompare(char *, char *, int);

#endif
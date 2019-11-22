#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 30

typedef struct Medecin Medecin;
typedef struct Patient Patient;

struct Medecin
{
    int numInami;
    char nom[NAME_SIZE], prenom[NAME_SIZE], dateN[9];
    Medecin *next;
};

struct Patient
{
    char regNat[16], nom[NAME_SIZE], prenom[NAME_SIZE], numTel[14], dateN[9];
    Patient *next;
};

int main()
{
    // Fichiers
    FILE *fdatMed, *fdatPat;
    fdatMed = fopen("medecins.dat", "r");
    fdatPat = fopen("patients.dat", "r");

    // Variables
    Medecin *firstM, *currentM, *nextM, *lastM;
    Patient *firstP, *currentP, *nextP, *lastP;

    int cpM = 0, cpP = 0;
    int n = 1;

    // Lecture Medecins
    firstM = malloc(sizeof(Medecin));
    currentM = firstM;

    fscanf(fdatMed, "%11d", &currentM->numInami);
    while(!feof(fdatMed))
    {
        fscanf(fdatMed, "%30s %30s %8s",
               &currentM->nom, &currentM->prenom, &currentM->dateN);
        lastM = currentM;

        nextM = malloc(sizeof(Medecin));
        currentM->next = nextM;

        currentM = nextM;

        cpM++;

        fscanf(fdatMed, "%11d", &currentM->numInami);
    }

    lastM->next = NULL;
    cpM--;
    free(nextM);

    // Lecture patients
    firstP = malloc(sizeof(Patient));
    currentP = firstP;

    fscanf(fdatPat, "%15s", &currentP->regNat);
    while(!feof(fdatPat))
    {
        fscanf("%30s %30s %8s %13s",
               &currentP->nom, &currentP->nom, &currentP->numTel, &currentP->dateN);
        lastP = currentP;

        nextP = malloc(sizeof(Patient));
        currentP->next = nextP;

        currentP = nextP;

        cpP++;

        fscanf(fdatPat, "%15s", &currentP->regNat);
    }

    lastP->next = NULL;
    cpP--;
    free(nextP);

    // Affichage de la liste médecins
    printf("Liste des médecins\n"
           "******************\n");
    n = 1;
    currentM = firstM;
    while(currentM != NULL)
    {
        printf("Médecin %d --> %11d %-30s %-30s %-8s\n",
               n, currentM->numInami, currentM->nom, currentM->prenom, currentM->dateN);
        n++;
        currentM = currentM->next;
    }

    // Affichage liste de patients
    printf("\nListe des médecins\n"
           "******************\n");
    n = 1;
    currentP= firstP;
    while(currentP != NULL)
    {
        printf("Patient %d --> %-15s %-30s %-30s %-14s %-8s\n",
               n, currentP->regNat, currentP->nom, currentP->prenom, currentP->numTel, currentP->dateN);
        n++;
        currentP = currentP->next;
    }

    return 0;
}

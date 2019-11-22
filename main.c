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

    // MENU
    printf("GESTION CABINET\n"
           "***************\n"
           "1. ");
    return 0;
}

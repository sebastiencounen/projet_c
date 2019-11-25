#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

#define NAME_SIZE 30

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

    fscanf(fdatMed, "%ld", &currentM->numInami);
    while(!feof(fdatMed))
    {
        fscanf(fdatMed, "%20s %20s %8s",
               &currentM->nom, &currentM->prenom, &currentM->dateN);
        lastM = currentM;

        nextM = malloc(sizeof(Medecin));
        currentM->next = nextM;

        currentM = nextM;

        cpM++;

        fscanf(fdatMed, "%ld", &currentM->numInami);
    }

    lastM->next = NULL;
    free(nextM);

    //
    printf("Nombre de médecins à l'initialisation : %d\n", cpM);

    // Lecture patients
    firstP = malloc(sizeof(Patient));
    currentP = firstP;

    fscanf(fdatPat, "%15s", &currentP->regNat);
    while(!feof(fdatPat))
    {
        fscanf(fdatPat, "%20s %20s %14s %8s",
               &currentP->nom, &currentP->prenom, &currentP->numTel, &currentP->dateN);
        fgets(currentP->adRue, 40, fdatPat);
        fscanf(fdatPat, "%3d %4d", &currentP->adNum, &currentP->adCp);
        fgets(currentP->adVille, 20, fdatPat);
        lastP = currentP;

        nextP = malloc(sizeof(Patient));
        currentP->next = nextP;

        currentP = nextP;

        cpP++;

        fscanf(fdatPat, "%15s", &currentP->regNat);
    }

    lastP->next = NULL;
    free(nextP);

    //
    printf("Nombre de patients à l'initialisation : %d\n", cpP);

    // Menu interactif
    while(1)
    {
        switch(menu())
        {
        case 1:
            afficherListeMed(firstM);
            break;

        case 2:
            afficherListePat(firstP);
            break;

        case 3:
            ajouterMed(&lastM, &cpM);
            break;
        
        case 4:
            ajouterPat(&lastP, &cpP);
            break;

        case 5:
            supprimerMed(&firstM, &cpM);
            break;

        case 6:
            supprimerPat(&firstP, &cpP);
            break;
        
        case 7:
            rechercherMed(firstM);
            break;
        
        case 8:
            rechercherPat(firstP);
            break;

        case 9:
            return 0;

        default:
            printf("Mauvais numéro sélectionné !\n");
        }
    }

    return 0;
}

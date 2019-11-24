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
        fscanf(fdatMed, "%30s %30s %8s",
               &currentM->nom, &currentM->prenom, &currentM->dateN);
        lastM = currentM;

        nextM = malloc(sizeof(Medecin));
        currentM->next = nextM;

        currentM = nextM;

        cpM++;

        fscanf(fdatMed, "%ld", &currentM->numInami);
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
        fscanf(fdatPat, "%30s %30s %14s %8s",
               &currentP->nom, &currentP->prenom, &currentP->numTel, &currentP->dateN);
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

    // // Affichage de la liste médecins
    // printf("Liste des médecins\n"
    //        "******************\n");
    // n = 1;
    // currentM = firstM;
    // while(currentM != NULL)
    // {
    //     printf("Médecin %d --> %ld %-30s %-30s %-8s\n",
    //            n, currentM->numInami, currentM->nom, currentM->prenom, currentM->dateN);
    //     n++;
    //     currentM = currentM->next;
    // }

    // // Affichage liste de patients
    // printf("\nListe des patients\n"
    //        "******************\n");
    // n = 1;
    // currentP= firstP;
    // while(currentP != NULL)
    // {
    //     printf("Patient %d --> %-15s %-30s %-30s %-14s %-8s\n",
    //            n, currentP->regNat, currentP->nom, currentP->prenom, currentP->numTel, currentP->dateN);
    //     n++;
    //     currentP = currentP->next;
    // }

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
            printf("\nAdresse du dernier avant : %x\n", lastM);
            ajouterMed(&lastM);
            printf("Adresse du dernier après : %x\n", lastM);
            break;
        
        case 4:
            ajouterPat(lastP);
            break;

        case 5:
            supprimerMed(firstM);
            break;

        case 6:
            supprimerPat(firstP);
            break;

        case 7:
            return 0;

        default:
            printf("Mauvais numéro sélectionné !\n");
        }
    }

    return 0;
}

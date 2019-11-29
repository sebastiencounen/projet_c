#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int main()
{
    // Fichiers
    FILE *fdatMed, *fdatPat;
    fdatMed = fopen("medecins.dat", "r");
    fdatPat = fopen("patients.dat", "r");

    // Variables
    Medecin *firstM, *currentM, *nextM, *lastM;
    Patient *firstP, *currentP, *nextP, *lastP;

    int cpM = 0, cpP = 0, exitMenu = 0;
    int n = 1;

    // Lecture Medecins
    firstM = malloc(sizeof(Medecin));
    currentM = firstM;

    fscanf(fdatMed, "%ld", &currentM->numInami);
    while(!feof(fdatMed))
    {
        fgets(currentM->nom, 21, fdatMed);
        fgets(currentM->prenom, 21, fdatMed);
        fscanf(fdatMed, "%8s", &currentM->dateN);
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

    fgets(currentP->regNat, 16, fdatPat);
    while(!feof(fdatPat))
    {
        fgets(currentP->nom, 21, fdatPat);
        fgets(currentP->prenom, 21, fdatPat);
        fscanf(fdatPat, "%13s %8s",
               &currentP->numTel, &currentP->dateN);
        fgets(currentP->adRue, 41, fdatPat);
        fscanf(fdatPat, "%3d %4d", &currentP->adNum, &currentP->adCp);
        fgets(currentP->adVille, 21, fdatPat);
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
        switch(menuPrincipal())
        {
        case 1:
            printf("\e[1;1H\e[2J");
            exitMenu = 0;
            while(exitMenu != 1)
            {
                switch(menuMed())
                {
                case 1:
                    afficherListeMed(firstM);
                    break;
                case 2:
                    ajouterMed(&lastM, &cpM);
                    break;
                case 3:
                    supprimerMed(&firstM, &cpM);
                    break;
                case 4:
                    rechercherMed(firstM);
                    break;
                case 5:
                    printf("Option not working yet\n");
                    // modifierMed(firstM);
                    break;
                case 6:
                    // Clear the console
                    printf("\e[1;1H\e[2J");
                    exitMenu = 1;
                    break;
                default:
                    printf("Mauvais numéro sélectionné !\n");
                    break;
                }
            }

            break;
        case 2:
            printf("\e[1;1H\e[2J");
            exitMenu = 0;
            while(exitMenu != 1)
            {
                switch(menuPat())
                {
                case 1:
                    afficherListePat(firstP);
                    break;
                case 2:
                    ajouterPat(&lastP, &cpP);
                    break;
                case 3:
                    supprimerPat(&firstP, &cpP);
                    break;
                case 4:
                    rechercherPat(firstP);
                    break;
                case 5:
                    printf("Option not working yet\n");
                    // modifierPat(firstP);
                    break;
                case 6:
                    // Clear the console
                    printf("\e[1;1H\e[2J");
                    exitMenu = 1;
                    break;
                default:
                    printf("Mauvais numéro sélectionné !\n");
                    break;
                }
            }

            break;
        case 3:
            printf("\e[1;1H\e[2J");
            sauvegarde(firstM, firstP);
            break;
        case 4:
            sauvegarde(firstM, firstP);
            return 0;
        default:
            printf("Mauvais numéro sélectionné !\n");
            break;
        }
    }

    return 0;
}

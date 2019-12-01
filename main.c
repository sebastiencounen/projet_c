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
    Medecin *firstM, *currentM, *nextM, *lastM, *interM;
    Patient *firstP, *currentP, *nextP, *lastP, *interP;

    int cpM = 0, cpP = 0, exitMenu = 0;
    int n = 1;
    char choixSave = 'n';

    // Lecture Medecins
    lectureMedecins(&firstM, &currentM, &interM, &lastM, &cpM);
    //
    printf("Nombre de médecins à l'initialisation : %d\n", cpM);

    // Lecture patients
    lecturePatients(&firstP, &currentP, &interP, &lastP, &cpP);
    //
    printf("Nombre de patients à l'initialisation : %d\n", cpP);

    // Menu interactif
    while (1)
    {
        switch (menuPrincipal())
        {
        case 1:
            printf("\e[1;1H\e[2J");
            exitMenu = 0;
            while (exitMenu != 1)
            {
                switch (menuMed())
                {
                case 1:
                    afficherListeMed(firstM);
                    break;
                case 2:
                    ajouterMed(&currentM, &firstM, &lastM, &cpM);
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
            while (exitMenu != 1)
            {
                switch (menuPat())
                {
                case 1:
                    afficherListePat(firstP);
                    break;
                case 2:
                    ajouterPat(&currentP, &firstP, &lastP, &cpP);
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
            printf("Voulez-vous sauvergdez les changements effectués ? [o/n] : ");
            scanf("%c", &choixSave);
            printf("\n");

            if (choixSave == 'o' || choixSave == 'O')
                sauvegarde(firstM, firstP);
            
            return 0;
        default:
            printf("Mauvais numéro sélectionné !\n");
            break;
        }
    }

    return 0;
}

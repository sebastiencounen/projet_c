#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int main()
{
    // Fichiers
    FILE *fdatMed, *fdatPat, *fdatC;
    fdatMed = fopen("medecins.dat", "r");
    fdatPat = fopen("patients.dat", "r");
    fdatC = fopen("consultations.dat", "r");

    // Variables
    Medecin *firstM, *currentM, *nextM, *lastM, *interM;
    Patient *firstP, *currentP, *nextP, *lastP, *interP;
    Consultation *firstC, *currentC, *nextC, *lastC, *interC;

    int cpM = 0, cpP = 0, exitMenu = 0, i, j, med = 0;
    int n = 1, jour, heure;
    char choixSave = 'n';

    char heuresHoraire[17][12] = {
        "08H00-08H30",
        "08H30-09H00",
        "09H00-09H30",
        "09H30-10H00",
        "10H00-10H30",
        "10H30-11H00",
        "11H00-11H30",
        "11H30-12H00",
        "13H00-13H30",
        "13H30-14H00",
        "14H00-14H30",
        "14H30-15H00",
        "15H00-15H30",
        "15H30-16H00",
        "16H00-16H30",
        "16H30-17H00"};

    // Lecture Medecins
    lectureMedecins(&firstM, &currentM, &interM, &lastM, &cpM);

    // Lecture des consultations
    for (currentM = firstM; currentM != NULL; currentM = currentM->next)
    {
        for (i = 1; i <= 6; i++)
        {
            for (j = 1; j <= 16; j++)
            {
                fscanf(fdatC, "%2d", &heure);
                fgets(currentM->cons[i][j].nomPat, 21, fdatC);
                currentM->cons[i][j].lettrePrenPat = fgetc(fdatC);
            }
        }
    }

    // Lecture patients
    lecturePatients(&firstP, &currentP, &interP, &lastP, &cpP);

    // Menu interactif
    printf("\e[1;1H\e[2J");
    while (1)
    {
        switch (menuPrincipal())
        {
        case 1:
            exitMenu = 0;
            while (exitMenu != 1)
            {
                switch (menuMed())
                {
                case 1:
                    afficherListeMed(firstM, cpM);
                    break;
                case 2:
                    ajouterMed(&currentM, &firstM, &lastM, &cpM);
                    break;
                case 3:
                    supprimerMed(&firstM, &cpM);
                    break;
                case 4:
                    rechercherMed(firstM, &currentM);
                    break;
                case 5:
                    afficherHoraire(firstM, &currentM);
                    break;
                case 6:
                    exitMenu = 1;
                    break;
                default:
                    printf("Mauvais numéro sélectionné !\n");
                    break;
                }
            }

            break;
        case 2:
            exitMenu = 0;
            while (exitMenu != 1)
            {
                switch (menuPat())
                {
                case 1:
                    afficherListePat(firstP, cpP);
                    break;
                case 2:
                    ajouterPat(&currentP, &firstP, &lastP, &cpP);
                    break;
                case 3:
                    supprimerPat(&firstP, &cpP);
                    break;
                case 4:
                    rechercherPat(firstP, &currentP);
                    break;
                case 5:
                    printf("Option not working yet\n");
                    // modifierPat(firstP);
                    break;
                case 6:
                    ajouterCons(firstP, &currentP, firstM, &currentM);
                    break;
                case 7:
                    exitMenu = 1;
                    break;
                default:
                    printf("Mauvais numéro sélectionné !\n");
                    break;
                }
            }

            break;
        case 3:
            sauvegarde(firstM, firstP);
            break;
        case 4:
            printf("Voulez-vous sauvergdez les changements effectués ? [o/n] : ");
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

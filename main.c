#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int main()
{
    // Fichiers
    FILE *fdatC, *fdatSpe;
    fdatC = fopen("consultations.dat", "r");
    fdatSpe = fopen("specialites.dat", "r");

    // Variables
    Medecin *firstM, *currentM, *nextM, *lastM, *interM;
    Patient *firstP, *currentP, *nextP, *lastP, *interP;

    int cpM = 0, cpP = 0, exitMenu = 0, i, j, med = 0;
    int n = 1, heure;
    int cpSpe = 0, c;
    char **tabSpe, **tabNomemclature;
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

    // On compte les spécialités
    if (fdatSpe != NULL)
    {
        while ((c = fgetc(fdatSpe)) != EOF)
        {
            if (c == '\n')
                cpSpe++;
        }

        // On revient au début du fichier
        rewind(fdatSpe);

        // Initialisation dynamique de la taille du tableau
        tabSpe = (char **)malloc(cpSpe * sizeof(char *));
        tabNomemclature = (char **)malloc(cpSpe * sizeof(char *));
        // Initialisation de la taille des chaînes contenues dans les tableaux
        for (i = 0; i < cpSpe; i++)
        {
            tabSpe[i] = (char *)malloc(21 * sizeof(char));
            tabNomemclature[i] = (char *)malloc(7 * sizeof(char));
        }

        // Lecture
        for (i = 0; i < cpSpe; i++)
        {
            fscanf(fdatSpe, "%20s%6s", tabSpe[i], tabNomemclature[i]);
        }

        fclose(fdatSpe);
    }
    else
    {
        printf("Erreur lecture des spécialités\n");
        system("echo \"Le programme va s'arrêter...\" && read a");
        return 0;
    }
    


    // Lecture Medecins
    if (lectureMedecins(&firstM, &currentM, &interM, &lastM, &cpM))
    {
        printf("Erreur lecture des médecins\n");
        system("echo \"Le programme va s'arrêter...\" && read a");
        return 0;
    }
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
    if (lecturePatients(&firstP, &currentP, &interP, &lastP, &cpP))
    {
        printf("Erreur lecture des patients\n");
        system("echo \"Le programme va s'arrêter...\" && read a");
        return 0;
    }

    // Menu interactif
    // printf("\e[1;1H\e[2J");
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
                    system("echo \"Appuyer sur une touche pour continuer...\" && read a");
                    printf("\e[1;1H\e[2J");
                    break;
                case 2:
                    ajouterMed(&currentM, &firstM, &lastM, &cpM, tabSpe, tabNomemclature, cpSpe);
                    break;
                case 3:
                    supprimerMed(&firstM, &cpM);
                    break;
                case 4:
                    rechercherMed(firstM, &currentM, cpSpe, tabSpe);
                    system("echo \"Appuyer sur une touche pour continuer...\" && read a");
                    printf("\e[1;1H\e[2J");
                    break;
                case 5:
                    afficherHoraire(firstM, currentM);
                    system("echo \"Appuyer sur une touche pour continuer...\" && read a");
                    printf("\e[1;1H\e[2J");
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
                    system("echo \"Appuyer sur une touche pour continuer...\" && read a");
                    printf("\e[1;1H\e[2J");
                    break;
                case 2:
                    ajouterPat(&currentP, &firstP, &lastP, &cpP);
                    break;
                case 3:
                    supprimerPat(&firstP, &cpP);
                    break;
                case 4:
                    rechercherPat(firstP, &currentP);
                    system("echo \"Appuyer sur une touche pour continuer...\" && read a");
                    printf("\e[1;1H\e[2J");
                    break;
                case 5:
                    ajouterCons(firstP, &currentP, firstM, &currentM, cpSpe, tabSpe);
                    break;
                case 6:
                    supprimerCons(firstM, &currentM, cpSpe, tabSpe);
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
            reinitialisationRDV(firstM);
            break;
        case 4:
            sauvegarde(firstM, firstP);
            break;
        case 5:
            printf("Voulez-vous sauvergdez les changements effectués ? [o/n] : ");
            choixSave = getc(stdin);
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

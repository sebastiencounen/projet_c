#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

// Fonctions
void afficherListeMed(Medecin *first)
{
    int n = 1;
    Medecin *current;

    current = first;
    while(current != NULL)
    {
        printf("Médecin %d --> %ld %-30s %-30s %-8s\n",
               n, current->numInami, current->nom, current->prenom, current->dateN);

        n++;
        current = current->next;
    }
}

void afficherListePat(Patient *first)
{
    // TODO
}

void ajouterMed(Medecin *last)
{
    // TODO
}

void ajouterPat(Patient *last)
{
    // TODO
}

void supprimerMed(Medecin *first)
{
    // TODO
}

void supprimerPat(Patient *first)
{
    // TODO
}

void rechercherMed(Medecin *first)
{
    // TODO
}

void rechercherPat(Patient *first)
{
    // TODO
}

int menu()
{
    int choix;

    printf("Menu principal\n"
           "**************\n"
           "1. Afficher liste de médecin(s)\n"
           "2. Afficher liste de patient(s)\n"
           "3. Ajouter un médecin\n"
           "4. Ajouter un patient\n"
           "5. Supprimer un médecin\n"
           "6. Supprimer un patient\n"
           "7. Quitter\n: ");

    scanf("%d", &choix);
    printf("\n");

    return choix;
}

void majuscule(char *chaine)
{
    int i;

    for(i = 0; chaine[i] != '\0'; i++)
    {
        chaine[i] = toupper(chaine[i]);
    }
}


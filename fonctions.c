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
    int n = 1;
    Patient *current;

    current = first;
    while(current != NULL)
    {
        printf("Patient %d --> %-15s %-30s %-30s %-14s %-8s\n",
               n, current->regNat, current->nom, current->prenom, current->numTel, current->dateN);
        
        n++;
        current = current->next;
    }
}

void ajouterMed(Medecin **last)
{
    FILE *file;
    file = fopen("medecins.dat", "a"); // append --> ajouter à la fin

    Medecin *new;
    // char regNat[16], nom[30], prenom[30], numTel[14];

    new = malloc(sizeof(Medecin));

    // last->next = new;
    (*last)->next = new;
    new->next = NULL;

    printf("Numéro inami : ");
    scanf("%11lds", &new->numInami);

    printf("\nNom : ");
    scanf("%30s", &new->nom);
    majuscule(&new->nom);

    printf("\nPrénom : ");
    scanf("%30s", &new->prenom);
    majuscule(&new->prenom);
    
    printf("\nDate de naissance (JJ/MM/AA) : ");
    scanf("%8s", &new->dateN);

    printf("\n");

    // Pour que le dernier soit mis à jour au nouveau créé
    *last = new;

    // Ajout du médecin dans le fichier
    fprintf(file, "%11ld %-30s %-30s %-8s\n", 
            new->numInami, new->nom, new->prenom, new->dateN);
    
    fclose(file);
}

void ajouterPat(Patient **last)
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

    printf("\nMenu principal\n"
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

void majuscule(char chaine[])
{
    int i;

    for(i = 0; chaine[i] != '\0'; i++)
    {
        chaine[i] = toupper(chaine[i]);
    }
}


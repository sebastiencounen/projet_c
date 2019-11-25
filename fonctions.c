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
        printf("Patient %d --> %-15s %-30s %-30s %-14s %-8s %-40s %3d %4d %-20s\n",
               n, current->regNat, current->nom, current->prenom, current->numTel, current->dateN,
               current->adRue, current->adNum, current->adCp, current->adVille);
        
        n++;
        current = current->next;
    }
}

void ajouterMed(Medecin **last, int *nb)
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
    *nb++;

    // Ajout du médecin dans le fichier
    fprintf(file, "%11ld %-30s %-30s %-8s\n", 
            new->numInami, new->nom, new->prenom, new->dateN);
    
    fclose(file);
}

void ajouterPat(Patient **last, int *nb)
{
    FILE *file;
    file = fopen("patients.dat", "a");

    Patient *new;
    new = malloc(sizeof(Patient));

    (*last)->next = new;
    new->next = NULL;

    printf("Numéro de registre national : ");
    scanf("%15s", &new->regNat);

    printf("\nNom : ");
    scanf("%30s", &new->nom);
    majuscule(&new->nom);

    printf("\nPrenom : ");
    scanf("%30s", &new->prenom);
    majuscule(&new->prenom);

    printf("\nNuméro de téléphone : ");
    scanf("%13s", &new->numTel);

    printf("\nDate de naissance (JJ/MM/AA) : ");
    scanf("%8s", &new->dateN);

    printf("\n");

    *last = new;
    *nb++;

    fprintf(file, "%-15s %-30s %-30s %-13s  %-8s\n",
            new->regNat, new->nom, new->prenom, new->numTel, new->dateN);

    fclose(file);
}

void supprimerMed(Medecin **first, int *nbTot)
{
    Medecin *current, *tmp;
    int n = 0, i;
    char nom[30], prenom[30];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    scanf("%30s", nom);
    majuscule(nom);

    printf("\nEntrez le prénom du médecin : ");
    scanf("%30s", prenom);
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while(current != NULL)
    {
        n++;
        if((strcmp(nom, current->nom) == 0) && strcmp(prenom, current->prenom) == 0)
            break;

        current = current->next;
    }

    // Suppression
    if(n == 1)
    {
        tmp = *first;
        *first = (*first)->next;
        free(tmp);
    }
    else
    {
        n--;
        current = *first;

        // On se déplace jusqu'à l'élément précédent celui qu'on veut supprimer
        for(i = 0; i < n - 1; i++)
            current = current->next;
        
        if(n != *nbTot)
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);
        }
        else
        {
            tmp = current->next;
            current->next = NULL;
            free(tmp);
        }
        
    }
}

void supprimerPat(Patient **first, int *nbTot)
{
    Patient *current, *tmp;
    int n = 0, i;
    char nom[30], prenom[30];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    scanf("%30s", nom);
    majuscule(nom);

    printf("\nEntrez le prénom du patient : ");
    scanf("%30s", prenom);
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while(current != NULL)
    {
        n++;
        if((strcmp(nom, current->nom) == 0) && strcmp(prenom, current->prenom) == 0)
            break;

        current = current->next;
    }

    // Suppression
    if(n == 1)
    {
        tmp = *first;
        *first = (*first)->next;
        free(tmp);
    }
    else
    {
        n--;
        current = *first;

        // On se déplace jusqu'à l'élément précédent celui qu'on veut supprimer
        for(i = 0; i < n - 1; i++)
            current = current->next;
        
        if(n != *nbTot)
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);
        }
        else
        {
            tmp = current->next;
            current->next = NULL;
            free(tmp);
        }
        
    }
}

void rechercherMed(Medecin *first)
{
    Medecin *current;
    char nom[30], prenom[30];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    scanf("%30s", &nom);
    majuscule(&nom);

    printf("\nEntrez le prénom du médecin : ");
    scanf("%30s", &prenom);
    majuscule(&prenom);
    
    printf("\n");

    // On recherche dans la liste
    current = first;
    while(current != NULL)
    {
        if((strcmp(nom, current->nom) == 0) && strcmp(prenom, current->prenom) == 0)
        {
            printf("%11ld %-30s %-30s %-8s\n",
                   current->numInami, current->nom, current->prenom, current->dateN);
            return;
        }

        current = current->next;
    }

    printf("Erreur : Personne non trouvée\n");
}

void rechercherPat(Patient *first)
{
    Patient *current;
    char nom[30], prenom[30];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    scanf("%30s", &nom);
    majuscule(&nom);

    printf("\nEntrez le prénom du patient : ");
    scanf("%30s", &prenom);
    majuscule(&prenom);
    
    printf("\n");

    // On recherche dans la liste
    current = first;
    while(current != NULL)
    {
        if((strcmp(nom, current->nom) == 0) && strcmp(prenom, current->prenom) == 0)
        {
            printf("Patient --> %-15s %-30s %-30s %-14s %-8s %-40s %3d %4d %-20s\n",
               current->regNat, current->nom, current->prenom, current->numTel, current->dateN,
               current->adRue, current->adNum, current->adCp, current->adVille);
            return;
        }

        current = current->next;
    }

    printf("Erreur : Personne non trouvée\n");
}

void modifierMed(Medecin *first)
{
    // TODO
}

void modifierPat(Patient *first)
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
           "7. Rechercher un médecin\n"
           "8. Rechercher un patient\n"
           "9. Quitter\n: ");

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


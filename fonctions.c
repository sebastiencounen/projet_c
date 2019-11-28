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
        printf("Médecin %d --> %11ld %-20s %-20s %-8s\n",
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
        printf("Patient %d --> %-15s %-20s %-20s %-14s %-8s %-40s %3d %4d %-20s\n",
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

    new = malloc(sizeof(Medecin));

    (*last)->next = new;
    new->next = NULL;

    printf("Numéro inami : ");
    new->numInami = lireLong(&new->numInami, 11);

    printf("\nNom : ");
    // fgets(new->nom, 20, stdin);
    lire(new->nom, 20);
    majuscule(&new->nom);

    printf("\nPrénom : ");
    lire(new->prenom, 20);
    majuscule(&new->prenom);
    
    printf("\nDate de naissance (JJ/MM/AA) : ");
    lire(new->dateN, 20);

    printf("\n");

    // Pour que le dernier soit mis à jour au nouveau créé
    *last = new;
    *nb++;

    // Ajout du médecin dans le fichier
    fprintf(file, "%11ld%-20s%-20s%-8s\n", 
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
    lire(new->regNat, 15);

    printf("\nNom : ");
    lire(new->nom, 20);
    majuscule(&new->nom);

    printf("\nPrenom : ");
    lire(new->prenom, 20);
    majuscule(&new->prenom);

    printf("\nNuméro de téléphone : ");
    lire(new->numTel, 13);

    printf("\nDate de naissance (JJ/MM/AA) : ");
    lire(new->dateN, 8);

    printf("\n");

    *last = new;
    *nb++;

    fprintf(file, "%-15s%-20s%-20s%-13s%-8s\n",
            new->regNat, new->nom, new->prenom, new->numTel, new->dateN);

    fclose(file);
}

void supprimerMed(Medecin **first, int *nbTot)
{
    //
    FILE *fres;
    fres = fopen("test.txt", "w");

    Medecin *current, *tmp;
    int n = 0, i;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du médecin : ");
    lire(prenom, 20);
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while(current != NULL)
    {
        n++;
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
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

    *nbTot--;
}

void supprimerPat(Patient **first, int *nbTot)
{
    Patient *current, *tmp;
    int n = 0, i;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    // fgets(nom, 20, stdin);
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du patient : ");
    // fgets(prenom, 20, stdin);
    lire(prenom, 20);
    printf("\n");
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while(current != NULL)
    {
        n++;
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
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

    *nbTot--;
}

void rechercherMed(Medecin *first)
{
    Medecin *current;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    // fgets(nom, 20, stdin);
    lire(nom, 20);
    majuscule(&nom);

    printf("\nEntrez le prénom du médecin : ");
    // fgets(prenom, 20, stdin);
    lire(prenom, 20);
    printf("\n");
    majuscule(&prenom);
    
    printf("\n");

    // On recherche dans la liste
    current = first;
    while(current != NULL)
    {
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            printf("%11ld %-20s %-20s %-8s\n",
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
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];


    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    // fgets(nom, 20, stdin);
    lire(nom, 20);
    majuscule(&nom);

    printf("\nEntrez le prénom du patient : ");
    // fgets(prenom, 20, stdin);
    lire(prenom, 20);
    printf("\n");
    majuscule(&prenom);
    
    // On recherche dans la liste
    current = first;
    while(current != NULL)
    {
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            printf("Patient --> %-15s %-20s %-20s %-14s %-8s %-40s %3d %4d %-20s\n",
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

    // scanf("%d", &choix);
    choix = lireInt(&choix, 1);
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

void clearBuffer()
{
    int c = 0;
    while(c != '\n' && c != EOF) // Quand c = '\n' et EOF --> fin du buffer
        c = getchar();
}

int lire(char *chaine, int longueur)
{
    char *posReturn = NULL;
    longueur++; // Caractère de fin de chaîne

    if(fgets(chaine, longueur, stdin) != NULL)
    {
        posReturn = strchr(chaine, '\n');
        if(posReturn != NULL)
        {
            // *posReturn = '\0';
            *posReturn = ' ';
            chaine[longueur] = '\0';
        }
        else
            clearBuffer();
        
        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

int lireInt(char *chaine, int longueur)
{
    if(lire(chaine, longueur))
        return (int)(strtol(chaine, NULL, 10));
    else
        return 0;
}

long lireLong(char *chaine, int longueur)
{
    if(lire(chaine, longueur))
        return strtol(chaine, NULL, 10);
    else
        return 0;
}

int formatAndCompare(char *chaine1, char *chaine2)
{
    int i = 0;
    while (chaine1[i] != '\0') 
        i++;

    chaine2[i] = '\0';

    return strcmp(chaine1, chaine2);
}


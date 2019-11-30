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
    while (current != NULL)
    {
        printf("Médecin %d --> %-14s %-20s %-20s\n",
               n, current->numInami, current->nom, current->prenom);

        n++;
        current = current->next;
    }
}

void afficherListePat(Patient *first)
{
    int n = 1;
    Patient *current;

    current = first;
    while (current != NULL)
    {
        printf("Patient %d --> %-15s %-20s %-20s %-14s %-8s %-40s %003d %4d %-20s\n",
               n, current->regNat, current->nom, current->prenom, current->numTel, current->dateN,
               current->adRue, current->adNum, current->adCp, current->adVille);

        n++;
        current = current->next;
    }
}

void ajouterMed(Medecin **last, int *nb)
{
    Medecin *new;

    new = malloc(sizeof(Medecin));

    (*last)->next = new;
    new->next = NULL;

    printf("Numéro inami : ");
    lire(new->numInami, 14);

    printf("\nNom : ");
    // fgets(new->nom, 20, stdin);
    lire(new->nom, 20);
    majuscule(&new->nom);

    printf("\nPrénom : ");
    lire(new->prenom, 20);
    majuscule(&new->prenom);

    printf("\n");

    // Pour que le dernier soit mis à jour au nouveau créé
    *last = new;
    *nb++;
}

void ajouterPat(Patient **last, int *nb)
{
    Patient *new;
    new = malloc(sizeof(Patient));

    (*last)->next = new;
    new->next = NULL;

    printf("Numéro de registre national : ");
    lire(new->regNat, 15);
    printf("\tregnat : %-15s", new->regNat);

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

    printf("\nAdresse (rue) : ");
    lire(new->adRue, 40);
    majuscule(&new->adRue);

    printf("\nAdresse (numéro) : ");
    new->adNum = lireInt(&new->adNum, 3);

    printf("\nAdresse (code postal) : ");
    new->adCp = lireInt(&new->adCp, 4);

    printf("\nAdresse (localité) : ");
    lire(new->adVille, 20);
    majuscule(&new->adVille);

    printf("\n");

    *last = new;
    *nb++;
}

void supprimerMed(Medecin **first, int *nbTot)
{
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
    while (current != NULL)
    {
        n++;
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
            break;

        current = current->next;
    }

    // Suppression
    if (n == 1)
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
        for (i = 0; i < n - 1; i++)
            current = current->next;

        if (n != *nbTot)
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
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du patient : ");
    lire(prenom, 20);
    printf("\n");
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while (current != NULL)
    {
        n++;
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
            break;

        current = current->next;
    }

    // Suppression
    if (n == 1)
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
        for (i = 0; i < n - 1; i++)
            current = current->next;

        if (n != *nbTot)
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
    while (current != NULL)
    {
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            printf("%-14s %-20s %-20s\n",
                   current->numInami, current->nom, current->prenom);
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
    while (current != NULL)
    {
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            printf("Patient --> %-15s %-20s %-20s %-14s %-8s %-40s %003d %4d %-20s\n",
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

int menuPrincipal()
{
    int choix;

    printf("\nMenu principal\n"
           "**************\n"
           "1. Médecins\n"
           "2. Patients\n"
           "3. Sauvegarder\n"
           "4. Quitter\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");

    return choix;
}

int menuMed()
{
    int choix;

    printf("\nMédecin(s)\n"
           "**********\n"
           "1. Afficher la liste\n"
           "2. Ajouter\n"
           "3. Supprimer\n"
           "4. Rechercher\n"
           "5. Modifier\n"
           "6. Retour au menu principal\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");

    return choix;
}

int menuPat()
{
    int choix;

    printf("\nPatient(s)\n"
           "**********\n"
           "1. Afficher la liste\n"
           "2. Ajouter\n"
           "3. Supprimer\n"
           "4. Rechercher\n"
           "5. Modifier\n"
           "6. Retour au menu principal\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");

    return choix;
}

void sauvegarde(Medecin *firstM, Patient *firstP)
{
    Medecin *currentM;
    Patient *currentP;
    FILE *fMed, *fPat;
    fMed = fopen("medecins.dat", "w");
    fPat = fopen("patients.dat", "w");

    // Save médecins
    currentM = firstM;
    while (currentM != NULL)
    {
        fprintf(fMed, "%-14s%-20s%-20s\n",
                currentM->numInami, currentM->nom, currentM->prenom);
        currentM = currentM->next;
    }
    fclose(fMed);

    // Save patients
    currentP = firstP;
    while (currentP != NULL)
    {
        fprintf(fPat, "%-15s%-20s%-20s%-13s%-8s%-40s%003d%4d%-20s\n",
                currentP->regNat, currentP->nom, currentP->prenom, currentP->numTel, currentP->dateN,
                currentP->adRue, currentP->adNum, currentP->adCp, currentP->adVille);
        currentP = currentP->next;
    }
    fclose(fPat);

    printf("Sauvegarde effectuée\n");
}

void majuscule(char chaine[])
{
    int i;

    for (i = 0; chaine[i] != '\0'; i++)
    {
        chaine[i] = toupper(chaine[i]);
    }
}

void clearBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF) // Quand c = '\n' et EOF --> fin du buffer
        c = getchar();
}

int lire(char *chaine, int longueur)
{
    char *posReturn = NULL;
    longueur++; // Caractère de fin de chaîne

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        posReturn = strchr(chaine, '\n');
        if (posReturn != NULL)
        {
            *posReturn = '\0';
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
    if (lire(chaine, longueur))
        return (int)(strtol(chaine, NULL, 10));
    else
        return 0;
}

long lireLong(char *chaine, int longueur)
{
    if (lire(chaine, longueur))
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

void lectureMedecins(Medecin **firstM, Medecin **currentM, Medecin **interM, Medecin **lastM, int *cpM)
{
    //Fichier
    FILE *fdatMed;
    fdatMed = fopen("medecins.dat", "r");
    // Premier client
    *firstM = malloc(sizeof(Medecin));

    *currentM = *firstM;

    // Lecture des clients présents dans le fichier
    fscanf(fdatMed, "%14s", (*currentM)->numInami);
    fgets((*currentM)->nom, 21, fdatMed);
    fgets((*currentM)->prenom, 21, fdatMed);
    while (!feof(fdatMed))
    {
        *interM = malloc(sizeof(Medecin));

        fscanf(fdatMed, "%14s", (*interM)->numInami);
        fgets((*interM)->nom, 21, fdatMed);
        fgets((*interM)->prenom, 21, fdatMed);

        for (*currentM = *firstM; *currentM != NULL; *currentM = (*currentM)->next)
        {
            if (strcmp((*interM)->nom, (*firstM)->nom) < 0)
            {
                (*interM)->next = *currentM;
                *firstM = *interM;
                break;
            }
            else if (strcmp((*interM)->nom, (*currentM)->nom) < 0)
            {
                (*lastM)->next = *interM;
                (*interM)->next = *currentM;
                break;
            }
            else if ((*currentM)->next == NULL && strcmp((*interM)->nom, (*currentM)->nom) > 0)
            {
                (*interM)->next = (*currentM)->next;
                (*currentM)->next = *interM;
                break;
            }
            *lastM = *currentM;
        }
        (*cpM)++;
    }
    *currentM = (*firstM)->next;
    free(*firstM);
    *firstM = *currentM;

    //Adresse du dernier
    for (*currentM = *firstM; *currentM != NULL; *currentM = (*currentM)->next)
        *lastM = *currentM;
}

void lecturePatients(Patient **firstP, Patient **currentP, Patient **interP, Patient **lastP, int *cpP)
{
    //Fichier
    FILE *fdatPat;
    fdatPat = fopen("patients.dat", "r");
    // Premier client
    *firstP = malloc(sizeof(Patient));

    *currentP = *firstP;

    // Lecture des clients présents dans le fichier
    fscanf(fdatPat, "%15s", (*currentP)->regNat);
    fgets((*currentP)->nom, 21, fdatPat);
    fgets((*currentP)->prenom, 21, fdatPat);
    fscanf(fdatPat, "%13s %8s", (*currentP)->numTel, (*currentP)->dateN);
    fgets((*currentP)->adRue, 41, fdatPat);
    fscanf(fdatPat, "%3d %4d", &(*currentP)->adNum, &(*currentP)->adCp);
    fgets((*currentP)->adVille, 21, fdatPat);
    while (!feof(fdatPat))
    {
        *interP = malloc(sizeof(Patient));

        fscanf(fdatPat, "%15s", (*interP)->regNat);
        fgets((*interP)->nom, 21, fdatPat);
        fgets((*interP)->prenom, 21, fdatPat);
        fscanf(fdatPat, "%13s %8s",
               (*interP)->numTel, (*interP)->dateN);
        fgets((*interP)->adRue, 41, fdatPat);
        fscanf(fdatPat, "%3d %4d", &(*interP)->adNum, &(*interP)->adCp);
        fgets((*interP)->adVille, 21, fdatPat);

        for (*currentP = *firstP; *currentP != NULL; *currentP = (*currentP)->next)
        {
            if (strcmp((*interP)->nom, (*firstP)->nom) < 0)
            {
                (*interP)->next = *currentP;
                *firstP = *interP;
                break;
            }
            else if (strcmp((*interP)->nom, (*currentP)->nom) < 0)
            {
                (*lastP)->next = *interP;
                (*interP)->next = *currentP;
                break;
            }
            else if ((*currentP)->next == NULL && strcmp((*interP)->nom, (*currentP)->nom) > 0)
            {
                (*interP)->next = (*currentP)->next;
                (*currentP)->next = *interP;
                break;
            }
            *lastP = *currentP;
        }
        (*cpP)++;
    }
    *currentP = (*firstP)->next;
    free(*firstP);
    *firstP = *currentP;

    //Adresse du dernier
    for (*currentP = *firstP; *currentP != NULL; *currentP = (*currentP)->next)
        *lastP = *currentP;
}
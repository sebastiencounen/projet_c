#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

// Fonctions
void afficherListeMed(Medecin *first, int cp)
{
    int n = 1;
    Medecin *current;

    printf("Nombre de médecins : %2d\n"
           "************************\n",
           cp);
    printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
           "----------------------------------------------------------------------------------\n");

    current = first;
    while (current != NULL)
    {
        printf("%-14s     %-20s  %-20s %-20s\n",
               current->numInami, current->nom, current->prenom, current->specialite);

        n++;
        current = current->next;
    }

    printf("----------------------------------------------------------------------------------\n");
}

void afficherListePat(Patient *first, int cp)
{
    int n = 1;
    Patient *current;

    printf("Nombre de patients : %2d\n"
           "************************\n",
           cp);

    printf("\nRegistre national  Nom                   Prenom                Sexe  Num Tel.        Date naiss.  "
           "Rue                                       Num  CP    Ville               \n"
           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    current = first;
    while (current != NULL)
    {
        printf("%-15s    %-20s  %-20s  %c    %-14s   %02d/%02d/%4d   %-40s  %3d  %-4s  %-20s\n",
               current->regNat, current->nom, current->prenom, current->sexe, current->numTel, current->dateN.jour,
               current->dateN.mois, current->dateN.annee, current->adresse.rue, current->adresse.num,
               current->adresse.cp, current->adresse.ville);

        n++;
        current = current->next;
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void ajouterMed(Medecin **current, Medecin **first, Medecin **last, int *nb)
{
    int n = 0, i, j;
    Medecin *new;

    if (*nb > 0)
    {
        new = malloc(sizeof(Medecin));
    }
    else
    {
        *first = malloc(sizeof(Medecin));
        new = *first;
    }

    printf("Numéro inami (x/xxxxx/xx/xxx) : ");
    lire(new->numInami, 14);

    // Vérification numInami différent
    if (*nb > 0)
    {
        for (*current = *first; *current != NULL; *current = (*current)->next)
        {
            if (strcmp((*current)->numInami, new->numInami) == 0)
                n++;
        }
    }

    if (n == 0)
    {
        printf("\nNom : ");
        lire(new->nom, 20);
        majuscule(&new->nom);

        printf("\nPrénom : ");
        lire(new->prenom, 20);
        majuscule(&new->prenom);

        printf("\nSpecialité : ");
        lire(new->specialite, 20);
        majuscule(&new->specialite);

        printf("\n");
        *nb++;

        // Initialisation à vide des consultations de ce médecin
        for (i = 1; i <= 6; i++)
        {
            for (j = 1; j <= 16; j++)
            {
                strcpy(new->cons[i][j].nomPat, "  /                 ");
                new->cons[i][j].lettrePrenPat = ' ';
            }
        }

        // Tri
        for (*current = *first; *current != NULL; *current = (*current)->next)
        {
            if (strcmp(new->nom, (*first)->nom) < 0)
            {
                new->next = *current;
                *first = new;
                break;
            }
            else if (strcmp(new->nom, (*current)->nom) < 0)
            {
                (*last)->next = new;
                new->next = *current;
                break;
            }
            else if ((*current)->next == NULL && strcmp(new->nom, (*current)->nom) > 0)
            {
                new->next = (*current)->next;
                (*current)->next = new;
                break;
            }
            *last = *current;
        }

        // Adresse du dernier
        for (*current = *first; *current != NULL; *current = (*current)->next)
            *last = *current;
    }
    else
    {
        free(new);
        printf("Ce numéro INAMI appartient déjà à un médecin du cabinet !\n");
    }
}

void ajouterPat(Patient **current, Patient **first, Patient **last, int *nb)
{
    int n = 0;
    Patient *new;

    if (*nb > 0)
    {
        new = malloc(sizeof(Patient));
    }
    else
    {
        *first = malloc(sizeof(Patient));
        new = *first;
    }

    printf("Nom : ");
    lire(new->nom, 20);
    majuscule(&new->nom);

    printf("\nPrénom : ");
    lire(new->prenom, 20);
    majuscule(&new->prenom);

    printf("\nNuméro de registre national (xx.xx.xx-xxx.xx) : ");
    lire(new->regNat, 15);

    // Vérification regNat différent
    if (*nb > 0)
    {
        for (*current = *first; *current != NULL; *current = (*current)->next)
        {
            if (strcmp((*current)->regNat, new->regNat) == 0)
                n++;
        }
    }

    if (n == 0)
    {
        printf("\nSexe du patient (M/F) : ");
        lireChar(&new->sexe);

        printf("\nNuméro de téléphone : ");
        lire(new->numTel, 13);

        printf("\nDate de naissance :\n");
        // lire(new->dateN, 8);
        printf("\tJour : ");
        new->dateN.jour = lireInt(&new->dateN.jour, 2);
        printf("\tMois : ");
        new->dateN.mois = lireInt(&new->dateN.mois, 2);
        printf("\tAnnée (AAAA) : ");
        new->dateN.annee = lireInt(&new->dateN.annee, 4);

        printf("\nAdresse :\n");
        printf("\tRue : ");
        lire(new->adresse.rue, 40);
        majuscule(&new->adresse.rue);

        printf("\tNuméro : ");
        new->adresse.num = lireInt(&new->adresse.num, 3);

        printf("\tCode postal : ");
        // new->adresse.cp = lireInt(&new->adresse.cp, 4);
        lire(new->adresse.cp, 4);

        printf("\tLocalité : ");
        lire(new->adresse.ville, 20);
        majuscule(&new->adresse.ville);

        printf("\n");
        *nb++;

        // Tri
        for (*current = *first; *current != NULL; *current = (*current)->next)
        {

            if (strcmp(new->nom, (*first)->nom) < 0)
            {
                new->next = *current;
                *first = new;
                break;
            }
            else if (strcmp(new->nom, (*current)->nom) < 0)
            {
                (*last)->next = new;
                new->next = *current;
                break;
            }
            else if ((*current)->next == NULL && strcmp(new->nom, (*current)->nom) > 0)
            {
                new->next = (*current)->next;
                (*current)->next = new;
                break;
            }
            *last = *current;
        }

        //Adresse du dernier
        for (*current = *first; *current != NULL; *current = (*current)->next)
            *last = *current;
    }
    else
    {
        free(new);
        printf("Ce numéro de registre national appartient déjà à un patient du cabinet !\n");
    }
}

void ajouterCons(Patient *firstP, Patient **currentPat, Medecin *firstM, Medecin **currentMed)
{
    int i, j, jour, mois, annee, choix, choixPlage, reponse;
    char jours[7][9] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"},
         heuresHoraire[17][12] = {
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
             "16H30-17H00"
        };

    Patient *currentP;
    Medecin *currentM;

    currentP = *currentPat;
    currentM = *currentMed;

    rechercherPat(firstP, &currentP);
    printf("\n");
    rechercherMed(firstM, &currentM);

    if (currentP != NULL)
    {
        // Affichage du lundi au samedi
        for (i = 1; i <= 6; i++)
            printf("%2d - %-8s\n", i, jours[i - 1]);

        printf(" 0 - Annuler\n : ");
        choix = lireInt(&choix, 1);

        if (choix != 0) // un jour a été choisi
        {
            printf("\e[1;1H\e[2J");
            printf("\n%-8s\n********\n", jours[choix - 1]);

            printf("\n ID   Heure         Patient\n\n");
            for (j = 1; j <= 16; j++) // afficher le planning du jour choisi
            {
                printf(" %2d - %-11s   ", j, heuresHoraire[j - 1]);
                printf("%-20s  %c\n", currentM->cons[choix][j].nomPat, currentM->cons[choix][j].lettrePrenPat);
            }
            printf(" 0 - Annuler\n");
            printf("\n: ");
            choixPlage = lireInt(&choixPlage, 2);

            if (choixPlage != 0) // une case horaire a été choisie
            {
                // Gestion des rendez-vous :
                if (strcmp(currentM->cons[choix][choixPlage].nomPat, "  /                 ") != 0) // si case horaire déjà occupée
                {
                    // Demande de remplacement :
                    printf("\nATTENTION : Un rendez-vous est déjà prévu. Voulez-vous le supprimer ?\n");
                    printf(" 1 - Oui\n 2 - Non\nReponse : ");
                    reponse = lireInt(&reponse, 1);
                    if (reponse == 1) // forcer le remplacement
                    {
                        strcpy(currentM->cons[choix][choixPlage].nomPat, currentP->nom);
                        currentM->cons[choix][choixPlage].lettrePrenPat = currentP->prenom[0];
                        printf("\e[1;1H\e[2J");
                        printf("\nLe rendez-vous a été mis à jour\n");
                    }
                    else // ignorer le remplacement
                    {
                        printf("\e[1;1H\e[2J");
                        printf("\nOperation annulée\n");
                    }
                }
                else // si case horaire vide
                {
                    // Fixer le rendez-vous :
                    strcpy(currentM->cons[choix][choixPlage].nomPat, currentP->nom);
                    currentM->cons[choix][choixPlage].lettrePrenPat = currentP->prenom[0];
                }
                printf("\e[1;1H\e[2J");
                printf("\nPlanning mis à jour\n");
            }
            else
            {
                printf("\e[1;1H\e[2J");
                printf("Erreur dans la sélection de votre plage horaire\n");
            }
        }
    }
}

void afficherHoraire(Medecin *first, Medecin *currentM)
{
    int i, j, n = 0, cp = 0;
    char nom[21], prenom[21], inami[15], tmpNom[21], tmpPren[21];
    char jours[7][9] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
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

    // Recherche du médecin via son nom, si doublon --> prénom et en cas extrême numéro inami étant unique
    printf("Nom du médecin : ");
    lire(nom, 20);
    majuscule(&nom);
    printf("\n");

    printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
        "----------------------------------------------------------------------------------\n");
    for (currentM = first; currentM != NULL; currentM = currentM->next)
    {
        if (n == 0)
            cp++;

        strcpy(tmpNom, currentM->nom);
        if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0)
        {
            n++;
            printf("%-14s     %-20s  %-20s %-20s\n",
                   currentM->numInami, currentM->nom, currentM->prenom, currentM->specialite);
        }
    }
    printf("----------------------------------------------------------------------------------\n");

    if (n > 1)
    {
        cp = 0;
        n = 0;

        printf("\nPrénom du médecin : ");
        lire(prenom, 20);
        majuscule(&prenom);
        printf("\n");
    
        printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
            "----------------------------------------------------------------------------------\n");
        for (currentM = first; currentM != NULL; currentM = currentM->next)
        {
            if (n == 0)
                cp++;

            strcpy(tmpNom, currentM->nom);
            strcpy(tmpPren, currentM->prenom);
            if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(prenom, tmpPren, strlen(tmpPren)) == 0)
            {
                n++;
                printf("%-14s     %-20s  %-20s %-20s\n",
                   currentM->numInami, currentM->nom, currentM->prenom, currentM->specialite);
            }
        }
        printf("----------------------------------------------------------------------------------\n");

        if (n > 1)
        {
            cp = 0;
            n = 0;

            printf("\nEntrez le numéro inami du médecin (x/xxxxx/xx/xxx) : ");
            lire(inami, 14);
            printf("\n");

            printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
                   "----------------------------------------------------------------------------------\n");

            for (currentM = first; currentM != NULL; currentM = currentM->next)
            {
                if (n == 0)
                    cp++;

                strcpy(tmpNom, currentM->nom);
                strcpy(tmpPren, currentM->prenom);
                if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(prenom, tmpPren, strlen(tmpPren)) == 0 && strcmp(inami, currentM->numInami) == 0)
                {
                    n++;
                    printf("%-14s     %-20s  %-20s %-20s\n",
                           currentM->numInami, currentM->nom, currentM->prenom, currentM->specialite);
                }
            }
            printf("----------------------------------------------------------------------------------\n");
        }
    }

    if (n != 0)
    {
        currentM = first;
        for (i = 1; i < cp; i++)
            currentM = currentM->next;
    }
    else
    {
        printf("Personne non trouvée\n");
        currentM = NULL;
    }
    
    // Affichage du calendrier

    if (currentM != NULL)
    {    
        printf("\n             ");
        for (i = 1; i <= 6; i++)
            printf("%-8s                ", jours[i - 1]);

        printf("\n***********************************************************************************************************************************************************\n");
        for (j = 1; j <= 16; j++)
        {
            printf("%-11s  ", heuresHoraire[j - 1]);
            for (i = 1; i <= 6; i++)
            {
                printf("%-20s %c  ", currentM->cons[i][j].nomPat, currentM->cons[i][j].lettrePrenPat);
            }

            if ( j != 16)
                printf("\n\n");
            else
                printf("\n");
        }
        printf("************************************************************************************************************************************************************\n");
    }
}

void supprimerMed(Medecin **first, int *nbTot)
{
    Medecin *current, *tmp;
    int n = 0, i, found = 0, cp = 0;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];
    char inami[15];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du médecin : ");
    lire(prenom, 20);
    majuscule(prenom);

    // On recherche dans la liste
    printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
           "----------------------------------------------------------------------------------\n");
    for (current = *first; current != NULL; current = current->next)
    {
        if (cp == 0)
            n++;

        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(prenom, tmpPren, strlen(tmpPren)) == 0)
        {
            cp++;
            found = 1;
            printf("%-14s     %-20s  %-20s %-20s\n",
                           current->numInami, current->nom, current->prenom, current->specialite);
        }
    }
    printf("----------------------------------------------------------------------------------\n");

    if (cp > 1)
    {
        found = 0;
        n = 0;
        cp = 0;

        printf("\nNuméro inami du médecin (x/xxxxx/xx/xxx) : ");
        lire(inami, 14);
        printf("\n");

        printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
           "----------------------------------------------------------------------------------\n");
        for (current = *first; current != NULL; current = current->next)
        {
            if (cp == 0)
                n++;

            strcpy(tmpNom, current->nom);
            strcpy(tmpPren, current->prenom);
            if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(prenom, tmpPren, strlen(tmpPren)) == 0 && strcmp(inami, current->numInami) == 0)
            {
                cp++;
                found = 1;
                printf("%-14s     %-20s  %-20s %-20s\n",
                           current->numInami, current->nom, current->prenom, current->specialite);
            }
        }
        printf("----------------------------------------------------------------------------------\n");
    }

    // Suppression
    if (n == 1 && found)
    {
        tmp = *first;
        *first = (*first)->next;
        free(tmp);
        *nbTot--;

        printf("\nSuppression effectuée avec succès\n");
    }
    else if (found)
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

        *nbTot--;

        printf("\nSuppression effectuée avec succès\n");
    }
    else
        printf("\nPersonne non trouvée\n");
}

void supprimerPat(Patient **first, int *nbTot)
{
    Patient *current, *tmp;
    int n = 0, i, found = 0, cp = 0;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];
    char regNat[16];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du patient : ");
    lire(prenom, 20);
    printf("\n");
    majuscule(prenom);

    // On recherche dans la liste
    printf("\nRegistre national  Nom                   Prenom                Sexe  Num Tel.        Date naiss.  "
           "Rue                                       Num  CP    Ville               \n"
           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (current = *first; current != NULL; current = current->next)
    {
        if (cp == 0)
            n++;

        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);
        if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(prenom, tmpPren, strlen(tmpPren)) == 0)
        {
            cp++;
            found = 1;
            printf("%-15s    %-20s  %-20s  %c    %-14s   %02d/%02d/%4d   %-40s  %3d  %-4s  %-20s\n",
               current->regNat, current->nom, current->prenom, current->sexe, current->numTel, current->dateN.jour,
               current->dateN.mois, current->dateN.annee, current->adresse.rue, current->adresse.num,
               current->adresse.cp, current->adresse.ville);
        }
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    if (cp > 1)
    {
        found = 0;
        n = 0;
        cp = 0;

        printf("\nNuméro de registre national du patient (xx.xx.xx-xxx.xx) : ");
        lire(regNat, 15);
        printf("\n");

        printf("\nRegistre national  Nom                   Prenom                Sexe  Num Tel.        Date naiss.  "
           "Rue                                       Num  CP    Ville               \n"
           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (current = *first; current != NULL; current = current->next)
        {
            if (cp == 0)
                n++;
            
            strcpy(tmpNom, current->nom);
            strcpy(tmpPren, current->prenom);
            if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(prenom, tmpPren, strlen(tmpPren)) == 0 && strcmp(regNat, current->regNat) == 0)
            {
                cp++;
                found = 1;
                printf("%-15s    %-20s  %-20s  %c    %-14s   %02d/%02d/%4d   %-40s  %3d  %-4s  %-20s\n",
                    current->regNat, current->nom, current->prenom, current->sexe, current->numTel, current->dateN.jour,
                    current->dateN.mois, current->dateN.annee, current->adresse.rue, current->adresse.num,
                    current->adresse.cp, current->adresse.ville);
            }
        }
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    // Suppression
    if (n == 1 && found)
    {
        tmp = *first;
        *first = (*first)->next;
        free(tmp);
        *nbTot--;

        printf("\nSuppression effectuée avec succès\n");
    }
    else if (found)
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

        *nbTot--;

        printf("\nSuppression effectuée avec succès\n");
    }
    else
        printf("Personne non trouvée\n");
}

void supprimerCons(Medecin *first, Medecin **curentM)
{
    int i, j, choix, choixPlage;
    char jours[7][9] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"},
         heuresHoraire[17][12] = {
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
             "16H30-17H00"
        };

    Medecin *current = *curentM;

    rechercherMed(first, &current);
    printf("\n");

    if (current != NULL)
    {
        for (i = 1; i <= 6; i++)
            printf("%2d - %-8s\n", i, jours[i - 1]);
        
        printf(" 0 - Annuler\n : ");
        choix = lireInt(&choix, 1);

        if (choix != 0)
        {
            printf("\e[1;1H\e[2J");
            printf("\n%-8s\n********\n", jours[choix - 1]);

            printf("\n ID   Heure         Patient\n\n");
            for (j = 1; j <= 16; j++) 
            {
                printf(" %2d - %-11s   ", j, heuresHoraire[j - 1]);
                printf("%-20s  %c\n", current->cons[choix][j].nomPat, current->cons[choix][j].lettrePrenPat);
            }

            printf(" 0 - Annuler\n");
            printf("\n: ");
            choixPlage = lireInt(&choixPlage, 2);

            if (choixPlage != 0)
            {
                if (strcmp(current->cons[choix][choixPlage].nomPat, "  /                 ") != 0)
                {
                    strcpy(current->cons[choix][choixPlage].nomPat, "  /                 ");
                    current->cons[choix][choixPlage].lettrePrenPat = ' '; 
                    printf("\e[1;1H\e[2J");
                    printf("Annulation effectuée\n");
                }
                else
                    printf("Aucun rendez-vous n'est prévu le %-8s - %-11s\n", jours[choix], heuresHoraire[choixPlage]);
            }
            else
            {
                printf("\e[1;1H\e[2J");
                printf("Erreur dans la sélection de votre plage horaire\n");
            }
            
        }
        else
        {
            printf("\e[1;1H\e[2J");
            printf("Erreur dans la sélection du jour\n");
        }
    }
}

void rechercherMed(Medecin *first, Medecin **current)
{
    int n = 0, cp = 0, i;
    char nom[21], tmpNom[21], spec[21], tmpSpec[21], inam[15];

    printf("Entrez la spécialité du médecin : ");
    lire(spec, 20);
    majuscule(&spec);
    printf("\n");

    printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
           "----------------------------------------------------------------------------------\n");
    for (*current = first; *current != NULL; *current = (*current)->next)
    {
        if (n == 0)
            cp++;

        strcpy(tmpSpec, (*current)->specialite);
        if (formatAndCompare(spec, tmpSpec, strlen(tmpSpec)) == 0)
        {
            n++;
            printf("%-14s     %-20s  %-20s %-20s\n",
                   (*current)->numInami, (*current)->nom, (*current)->prenom, (*current)->specialite);
        }
    }
    printf("----------------------------------------------------------------------------------\n");

    if (n > 1)
    {
        cp = 0;
        n = 0;

        printf("\nVeuillez entrer le nom du médecin : ");
        lire(nom, 20);
        majuscule(&nom);
        printf("\n");

        printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
               "----------------------------------------------------------------------------------\n");
        for (*current = first; *current != NULL; *current = (*current)->next)
        {
            if (n == 0)
                cp++;

            strcpy(tmpNom, (*current)->nom);
            strcpy(tmpSpec, (*current)->specialite);
            if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(spec, tmpSpec, strlen(tmpSpec)) == 0)
            {
                n++;
                printf("%-14s     %-20s  %-20s %-20s\n",
                       (*current)->numInami, (*current)->nom, (*current)->prenom, (*current)->specialite);
            }
        }
        printf("----------------------------------------------------------------------------------\n");

        if (n > 1)
        {
            cp = 0;
            n = 0;

            printf("\nEntrez le numéro inami du médecin (x/xxxxx/xx/xxx) : ");
            lire(inam, 14);
            printf("\n");

            printf("\nNuméro inami       Nom                   Prénom               Spécialité          \n"
                   "----------------------------------------------------------------------------------\n");

            for (*current = first; *current != NULL; *current = (*current)->next)
            {
                if (n == 0)
                    cp++;

                strcpy(tmpSpec, (*current)->specialite);
                strcpy(tmpNom, (*current)->nom);
                if (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0 && formatAndCompare(spec, tmpSpec, strlen(tmpSpec)) == 0 && strcmp(inam, (*current)->numInami) == 0)
                {
                    n++;
                    printf("%-14s     %-20s  %-20s %-20s\n",
                           (*current)->numInami, (*current)->nom, (*current)->prenom, (*current)->specialite);
                }
            }
            printf("----------------------------------------------------------------------------------\n");
        }
    }

    if (n != 0)
    {
        *current = first;
        for (i = 1; i < cp; i++)
            *current = (*current)->next;
    }
    else
        printf("Personne non trouvée\n");
}

void rechercherPat(Patient *first, Patient **current)
{
    int n = 0, cp = 0, i;
    char nom[21], tmpNom[21], regNat[16], tmpRegNat[16];
    Date dateNaiss;

    printf("Entrez la date de naissance du patient : ");
    printf("\n\tJour : ");
    dateNaiss.jour = lireInt(&dateNaiss.jour, 2);
    printf("\tMois : ");
    dateNaiss.mois = lireInt(&dateNaiss.mois, 2);
    printf("\tAnnée : ");
    dateNaiss.annee = lireInt(&dateNaiss.annee, 4);
    printf("\n");

    printf("\nRegistre national  Nom                   Prenom                Sexe  Num Tel.        Date naiss.  "
           "Rue                                       Num  CP    Ville               \n"
           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (*current = first; *current != NULL; *current = (*current)->next)
    {
        if (n == 0)
            cp++;

        if ((*current)->dateN.jour == dateNaiss.jour && (*current)->dateN.mois == dateNaiss.mois && (*current)->dateN.annee == dateNaiss.annee)
        {
            n++;
            printf("%-15s    %-20s  %-20s  %c    %-14s   %02d/%02d/%4d   %-40s  %3d  %-4s  %-20s\n",
               (*current)->regNat, (*current)->nom, (*current)->prenom, (*current)->sexe, (*current)->numTel, (*current)->dateN.jour,
               (*current)->dateN.mois, (*current)->dateN.annee, (*current)->adresse.rue, (*current)->adresse.num,
               (*current)->adresse.cp, (*current)->adresse.ville);
        }
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    if (n > 1)
    {
        cp = 0;
        n = 0;

        printf("\nVeuillez entrer le nom du patient : ");
        lire(nom, 20);
        majuscule(&nom);
        printf("\n");

        printf("\nRegistre national  Nom                   Prenom                Sexe  Num Tel.        Date naiss.  "
           "Rue                                       Num  CP    Ville               \n"
           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (*current = first; *current != NULL; *current = (*current)->next)
        {
            if (n == 0)
                cp++;

            strcpy(tmpNom, (*current)->nom);
            if ((formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0) && ((*current)->dateN.jour == dateNaiss.jour && (*current)->dateN.mois == dateNaiss.mois && (*current)->dateN.annee == dateNaiss.annee))
            {
                n++;
                printf("%-15s    %-20s  %-20s  %c    %-14s   %02d/%02d/%4d   %-40s  %3d  %-4s  %-20s\n",
                    (*current)->regNat, (*current)->nom, (*current)->prenom, (*current)->sexe, (*current)->numTel, (*current)->dateN.jour,
                    (*current)->dateN.mois, (*current)->dateN.annee, (*current)->adresse.rue, (*current)->adresse.num,
                    (*current)->adresse.cp, (*current)->adresse.ville);
            }
        }
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        if (n > 1)
        {
            n = 0;
            cp = 0;

            printf("\nEntrez le numéro de registre national (xx.xx.xx-xxx.xx) : ");
            lire(regNat, 15);
            printf("\n");

           printf("\nRegistre national  Nom                   Prenom                Sexe  Num Tel.        Date naiss.  "
           "Rue                                       Num  CP    Ville               \n"
           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            for (*current = first; *current != NULL; *current = (*current)->next)
            {
                if (n == 0)
                    cp++;

                strcpy(tmpNom, (*current)->nom);
                if (strcmp(regNat, (*current)->regNat) == 0 && (formatAndCompare(nom, tmpNom, strlen(tmpNom)) == 0) && ((*current)->dateN.jour == dateNaiss.jour && (*current)->dateN.mois == dateNaiss.mois && (*current)->dateN.annee == dateNaiss.annee))
                {
                    n++;
                    printf("%-15s    %-20s  %-20s  %c    %-14s   %02d/%02d/%4d   %-40s  %3d  %-4s  %-20s\n",
                        (*current)->regNat, (*current)->nom, (*current)->prenom, (*current)->sexe, (*current)->numTel, (*current)->dateN.jour,
                        (*current)->dateN.mois, (*current)->dateN.annee, (*current)->adresse.rue, (*current)->adresse.num,
                        (*current)->adresse.cp, (*current)->adresse.ville);
                }
            }
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }

    if (n != 0)
    {
        *current = first;
        for (i = 1; i < cp; i++)
            *current = (*current)->next;
    }
    else
    {
        printf("Personne non trouvée\n");
    }
}

void reinitialisationRDV(Medecin *first)
{
    int i, j;
    char choix;
    Medecin *current;

    printf("Êtes-vous sûr de vouloir réinitialisation l'entièreté des consultation ? [o/n] : ");
    lireChar(&choix);

    if (choix == 'O' || choix == 'o')
    {
        for (current = first; current != NULL; current = current->next)
        {
            for (i = 1; i <= 6; i++)
            {
                for (j = 1; j <= 16; j++)
                {
                    current->cons[i][j].lettrePrenPat = ' ';
                    strcpy(current->cons[i][j].nomPat, "  /                 ");
                }
            }
        }

        printf("\e[1;1H\e[2J");
        printf("Réinitialisation effectuée\n");
    }
    else
    {
        printf("\e[1;1H\e[2J");
        printf("Opération annulée\n");
    }
}

int menuPrincipal()
{
    int choix;

    printf("\nMenu principal\n"
           "**************\n"
           "1. Médecins\n"
           "2. Patients\n"
           "3. Réinitialisation consultations\n"
           "4. Sauvegarder\n"
           "5. Quitter\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");
    printf("\e[1;1H\e[2J");

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
           "5. Afficher horaire\n"
           "6. Retour au menu principal\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");
    printf("\e[1;1H\e[2J");

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
           "5. Prendre un rendez-vous\n"
           "6. Annuler un rendez-vous\n"
           "7. Retour au menu principal\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");
    printf("\e[1;1H\e[2J");

    return choix;
}

void sauvegarde(Medecin *firstM, Patient *firstP)
{
    int i, j;
    Medecin *currentM;
    Patient *currentP;
    FILE *fMed, *fPat, *fCons;
    fMed = fopen("medecins.dat", "w");
    fPat = fopen("patients.dat", "w");
    fCons = fopen("consultations.dat", "w");

    // Save médecins
    currentM = firstM;
    while (currentM != NULL)
    {
        fprintf(fMed, "%-14s%-20s%-20s%-20s\n",
                currentM->numInami, currentM->nom, currentM->prenom, currentM->specialite);

        //Save consultations
        for (i = 1; i <= 6; i++)
        {
            for (j = 1; j <= 16; j++)
            {
                fprintf(fCons, "%02d%20s%c\n", j, currentM->cons[i][j].nomPat,currentM->cons[i][j].lettrePrenPat);
            }
        }

        currentM = currentM->next;
    }
    fclose(fMed);
    fclose(fCons);

    // Save patients
    currentP = firstP;
    while (currentP != NULL)
    {
        fprintf(fPat, "%-15s%-20s%-20s%c%-13s%02d/%02d/%4d%-40s%003d%-4s%-20s\n",
                currentP->regNat, currentP->nom, currentP->prenom, currentP->sexe, currentP->numTel, currentP->dateN.jour,
                currentP->dateN.mois, currentP->dateN.annee, currentP->adresse.rue, currentP->adresse.num,
                currentP->adresse.cp, currentP->adresse.ville);
        currentP = currentP->next;
    }
    fclose(fPat);

    //Save consultations

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

void lireChar(char *car)
{
    *car = getc(stdin);
    clearBuffer();
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

int formatAndCompare(char *chaine1, char *chaine2, int longueurChaineListe)
{
    // chaine 1 = nom, prenom
    // chaine 2 = current->nom, current->prenom

    int lenChaine1, lenChaine2 = longueurChaineListe, i = 0;
    lenChaine1 = strlen(chaine1);

    // printf("Longueur nom à vouloir supp : %d\n", lenChaine1);

    while (chaine2[lenChaine2] == 0 || chaine2[lenChaine2] == ' ')
        lenChaine2--;
    lenChaine2++;

    // printf("Longeur nom de liste chaînée = %d\n", lenChaine2);

    if (lenChaine1 == lenChaine2)
    {
        while (chaine1[i] != '\0')
            i++;

        chaine2[i] = '\0';

        return strcmp(chaine1, chaine2);
    }
    else
    {
        return 1;
    }
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
    fscanf(fdatMed, "%20s", (*currentM)->specialite);
    while (!feof(fdatMed))
    {
        *interM = malloc(sizeof(Medecin));

        fscanf(fdatMed, "%14s", (*interM)->numInami);
        fgets((*interM)->nom, 21, fdatMed);
        fgets((*interM)->prenom, 21, fdatMed);
        fscanf(fdatMed, "%20s", (*interM)->specialite);

        for (*currentM = *firstM; *currentM != NULL; *currentM = (*currentM)->next)
        {
            if (strcmp((*interM)->nom, (*firstM)->nom) <= 0)
            {
                if (strcmp((*interM)->nom, (*currentM)->nom) == 0 && strcmp((*interM)->prenom, (*firstM)->prenom) > 0)
                {
                    (*interM)->next = (*currentM)->next;
                    (*currentM)->next = *interM;
                }
                else
                {
                    (*interM)->next = *currentM;
                    *firstM = *interM;
                }
                break;
            }
            else if (strcmp((*interM)->nom, (*currentM)->nom) <= 0)
            {
                if (strcmp((*interM)->nom, (*currentM)->nom) == 0 && strcmp((*interM)->prenom, (*currentM)->prenom) > 0)
                {
                    (*interM)->next = (*currentM)->next;
                    (*currentM)->next = *interM;
                }
                else
                {
                    (*lastM)->next = *interM;
                    (*interM)->next = *currentM;
                }
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

    fclose(fdatMed);
}

void lecturePatients(Patient **firstP, Patient **currentP, Patient **interP, Patient **lastP, int *cpP)
{
    int a = 0;
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
    (*currentP)->sexe = fgetc(fdatPat);
    fscanf(fdatPat, "%13s", (*currentP)->numTel);
    fscanf(fdatPat, "%2d%*c%2d%*c%4d", &(*currentP)->dateN.jour, &(*currentP)->dateN.mois, &(*currentP)->dateN.annee);
    fgets((*currentP)->adresse.rue, 41, fdatPat);
    fscanf(fdatPat, "%3d %4s", &(*currentP)->adresse.num, &(*currentP)->adresse.cp);
    fgets((*currentP)->adresse.ville, 21, fdatPat);

    while (!feof(fdatPat))
    {
        *interP = malloc(sizeof(Patient));

        fscanf(fdatPat, "%15s", (*interP)->regNat);
        fgets((*interP)->nom, 21, fdatPat);
        fgets((*interP)->prenom, 21, fdatPat);
        (*interP)->sexe = fgetc(fdatPat);
        fscanf(fdatPat, "%13s", (*interP)->numTel);
        fscanf(fdatPat, "%2d%*c%2d%*c%4d", &(*interP)->dateN.jour, &(*interP)->dateN.mois, &(*interP)->dateN.annee);
        fgets((*interP)->adresse.rue, 41, fdatPat);
        fscanf(fdatPat, "%3d %4s", &(*interP)->adresse.num, &(*interP)->adresse.cp);
        fgets((*interP)->adresse.ville, 21, fdatPat);

        for (*currentP = *firstP; *currentP != NULL; *currentP = (*currentP)->next)
        {
            if (strcmp((*interP)->nom, (*firstP)->nom) <= 0)
            {
                if (strcmp((*interP)->nom, (*currentP)->nom) == 0 && strcmp((*interP)->prenom, (*firstP)->prenom) > 0)
                {
                    (*interP)->next = (*currentP)->next;
                    (*currentP)->next = *interP;
                }
                else
                {
                    (*interP)->next = *currentP;
                    *firstP = *interP;
                }
                break;
            }
            else if (strcmp((*interP)->nom, (*currentP)->nom) <= 0)
            {
                if (strcmp((*interP)->nom, (*currentP)->nom) == 0 && strcmp((*interP)->prenom, (*currentP)->prenom) > 0)
                {
                    (*interP)->next = (*currentP)->next;
                    (*currentP)->next = *interP;
                }
                else
                {
                    (*lastP)->next = *interP;
                    (*interP)->next = *currentP;
                }
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

    fclose(fdatPat);
}

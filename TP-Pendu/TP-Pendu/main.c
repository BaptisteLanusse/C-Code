#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char lireCaractere();

int cptNbMotsDict(char*); // Compte le nombre de mots dans le dictionnaire de mots

char* motFromIndex(char*, int); // Ressort le mot positionné à un index donné

char afficherPendu(char*, char*); // Affiche le mot en fonction des lettres trouvées et retourne 0 si toutes les lettres ont été trouvées.

int main(int argc, const char * argv[]) {
    
    const int MIN = 1;      // L'index minimal pour la sélection de mot aléatoire
    
    const int MAX_TENTATIVES = 10;  // Le nombre de tentatives avant d'avoir perdu
    
    char* FICHIER_DICTIONNAIRE = "dict.txt";    // Le fichier dictionnaire
    
    srand((unsigned int)time(NULL));
    
    int MAX = cptNbMotsDict(FICHIER_DICTIONNAIRE);   // Cette variable contient le nombre de mots dans le dictionnaire, elle sert pour en choisir un au hasard
    
    if (MAX == -1) {
        printf("Une erreur est survenue à l'ouverture du fichier\n\n");
    } else {
        int indexMotATrouver = ((rand() % (MAX - MIN + 1)) + MIN) - 1;
        
        char* motATrouver = motFromIndex(FICHIER_DICTIONNAIRE, indexMotATrouver);
        
        char lettresTrouvees[strlen(motATrouver)];  // Un tableau contenant des valeurs étant soit -1 soit 0, si toutes les lettres du mot ont été trouvées, toutes les valeurs sont à 0, si il en reste à -1, il reste des lettres à trouver
        
        for (int compteur = 0; compteur < strlen(motATrouver); compteur++) {
            lettresTrouvees[compteur] = -1;
        } // On l'initialise à -1
        
        printf("Ceci est un jeu de pendu, vous avez %d tentatives pour trouver le mot :\n", MAX_TENTATIVES);
        afficherPendu(motATrouver, lettresTrouvees);
        printf("\n");
        
        int nbTentatives = 0;
        
        char lettreToutesTrouvees = -1;
        
        do {    // A chaque tour de boucle, on lit le caractère saisi, on teste s'il appartient au mot, on affiche le nombre d'erreurs et on recommence jusqu'à avoir trouvé le mot ou fait trop d'erreurs
            
            char lettreTestee = lireCaractere();
            
            char lettreFound = -1;
            
            for (int compteur = 0; compteur < (strlen(motATrouver) - 1); compteur++) {
                if (motATrouver[compteur] == lettreTestee) {
                    lettresTrouvees[compteur] = 0;
                    lettreFound = 0;
                }
            }
            
            if (lettreFound != 0) {
                nbTentatives++;
            }
            
            printf("\n%d erreurs\n", nbTentatives);
            
            lettreToutesTrouvees = afficherPendu(motATrouver, lettresTrouvees);
            
        } while (nbTentatives < MAX_TENTATIVES && lettreToutesTrouvees != 0);
        
        if (nbTentatives == MAX_TENTATIVES) {   // On affiche le résultat
            printf("\nDommage, vous avez manqué le mot : %s\n", motATrouver);
        } else {
            printf("\nBien joué, vous avez gagné !\n\n");
        }
        
    }
    
    return 0;
}

char lireCaractere()
{
    char caractere = 0;
    
    printf("Veuillez saisir le caractère à tester, puis presser Entrée, seul le premier caractère sera pris en compte.\n");
    
    caractere = getchar(); // Lecture du premier caractère
    caractere = toupper(caractere);
    
    while (getchar() != '\n');
    
    printf("\n");
    
    return caractere;
}

int cptNbMotsDict(char* nomFichier)     // On compte le nombre de mots dans le dictionnaire
{
    int nombreDeMots = 0;
    
    FILE* fichier = NULL;
    
    fichier = fopen(nomFichier, "r");
    
    if (fichier != NULL) {
        char caractereLu = fgetc(fichier);
        
        while (caractereLu != EOF) {
            if (caractereLu == '\n') {
                nombreDeMots++;
            }
            caractereLu = fgetc(fichier);
        }
    } else {
        printf("Problème d'ouverture du fichier\n\n");
        return -1;
    }
    
    fclose(fichier);
    
    return nombreDeMots;
}

char* motFromIndex(char* nomFichier, int index)     // On récupère le mot pour un index donné
{
    char* string = malloc(15);
    
    FILE* fichier = NULL;
    
    fichier = fopen(nomFichier, "r");
    
    if (fichier != NULL) {
        int indexCourant = 0;
        
        char caractereLu = 'a';
        
        while (indexCourant != index) {
            caractereLu = fgetc(fichier);
            if (caractereLu == '\n') {
                indexCourant++;
            }
        }
        
        do {
            caractereLu = fgetc(fichier);
            int index = (int)strlen(string);
            string[index++] = caractereLu;
            string[index] = '\0';
        } while (caractereLu != '\n');
        
    } else {
        printf("Problème d'ouverture du fichier");
    }
    
    fclose(fichier);
    
    char *result = string;
    
    free(string);
    
    return result;
}

char afficherPendu(char* motATrouver, char* lettresTrouvees)       // On affiche le mot en fonction des lettres trouvées.
{
    char result = 0;
    
    for (int compteur = 0; compteur < (strlen(motATrouver) - 1); compteur++) {
        if (lettresTrouvees[compteur] == 0) {
            printf("%c", motATrouver[compteur]);
        } else {
            printf("*");
            result = -1;
        }
    }
    printf("\n");
    
    return result;
}
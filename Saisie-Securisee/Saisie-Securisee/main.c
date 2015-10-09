#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lire(char*, int);

long lireLong();

double lireDouble();

int main(int argc, const char * argv[]) {
    
    /*char nom[10];
    
    printf("Quel est votre nom ? ");
    lire(nom, 10);
    printf("Ah ! Vous vous appelez donc %s ! \n\n", nom);*/
    
    /*long age = 0;
    
    printf("Quel est votre age ? ");
    age = lireLong();
    printf("Ah ! Vous avez donc %ld ans !\n\n", age);*/
    
    double poids = 0;
    
    printf("Combien pesez-vous ? ");
    poids = lireDouble();
    printf("Ah ! Vous pesez donc %f kg !\n\n", poids);
    
    return 0;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL) // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

long lireLong()
{
    char nombreTexte[100] = {0};
    
    if (lire(nombreTexte, 100))
    {
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        return 0;
    }
    
}

double lireDouble()
{
    char nombreTexte[100] = {0};
    
    if (lire(nombreTexte, 100))
    {
        return strtod(nombreTexte, NULL);
    }
    else
    {
        return 0;
    }
}
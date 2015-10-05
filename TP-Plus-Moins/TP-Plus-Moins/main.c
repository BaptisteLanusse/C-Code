#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    
    const int MIN = 1; // Les constantes qui contiennent les valeurs minimale et maximale
    
    int MAX = 100;
    
    srand(time(NULL));
    
    int continuerPartie = 1; // Variable permettant de savoir si l'utilisateur veut continuer à jouer
    
    do {
        
        int niveauDeDifficulte = 4; // Niveau de difficulté sélectionné
        
        do {
            printf("Veuillez chosir votre niveau de difficulte:\n1 = entre 1 et 100\n2 = entre 1 et 1000\n3 = entre 1 et 10000\nVotre choix ? ");
            scanf("%d", &niveauDeDifficulte);
        } while (niveauDeDifficulte != 1 && niveauDeDifficulte != 2 && niveauDeDifficulte != 3);
        
        switch (niveauDeDifficulte) {
            case 1:
                MAX = 100;
                break;
            case 2:
                MAX = 1000;
                break;
            case 3:
                MAX = 10000;
                break;
            default:
                break;
        }
        
        int nbPropose = 0; // La variable stockant le nombre proposé par l'utilisateur
        
        int compteurDeCoups = 0; // Le compteur de coups de l'utilisateur
        
        int nbATrouver = (rand() % (MAX - MIN + 1)) + MIN; // Le nombre à trouver
        
        while (nbPropose != nbATrouver) {
            printf("Quel est le nombre ? ");
            scanf("%d", &nbPropose);
            
            if (nbPropose > nbATrouver) {
                printf("C'est moins !\n");
            } else if (nbPropose < nbATrouver) {
                printf("C'est plus !\n");
            }
            
            compteurDeCoups++;
            
        }
        
        printf("Bravo, vous avez trouve le nombre mystere en %d coups !!!\n", compteurDeCoups);
        
        printf("Voulez-vous continuer à jouer ? (0 = Non, Autre = Oui) ");
        scanf("%d", &continuerPartie);
        
    } while (continuerPartie != 0);
    
    return 0;
}

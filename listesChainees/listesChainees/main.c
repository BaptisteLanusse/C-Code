//
//  main.c
//  listesChainees
//
//  Created by Lanusse Baptiste on 13/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//

#ifndef main
#define main

#undef main

#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    
    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;
    
    return liste;
}

void insertion(Liste *liste, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nvNombre;
    
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    if (liste->premier != NULL)
    {
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    Element *actuel = liste->premier;
    
    while (actuel != NULL) {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

int main (int argc, char *argv[]){
    
    Liste *maListe = initialisation();
    
    insertion(maListe, 4);
    insertion(maListe, 8);
    insertion(maListe, 15);
    suppression(maListe);
    
    afficherListe(maListe);
    
    return 0;
}

#endif
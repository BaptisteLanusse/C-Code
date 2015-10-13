//
//  main.c
//  Piles_Files
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

/*typedef struct Pile Pile;

struct Pile
{
    Element *premier;
};

Pile *initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    return pile;
}

void empiler(Pile *pile, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    nouveau->nombre = nvNombre;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

int depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    int nombreDepile = 0;
    Element *elementDepile = pile->premier;
    
    if (pile != NULL && pile->premier != NULL)
    {
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }
    
    return nombreDepile;
}

void afficherPile(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;
    
    while (actuel != NULL) {
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }
    
    printf("\n");
}

int main(int argc, char *argv[]){
    
    Pile *maPile = initialiser();
    
    empiler(maPile, 4);
    empiler(maPile, 8);
    empiler(maPile, 15);
    empiler(maPile, 16);
    empiler(maPile, 23);
    empiler(maPile, 42);
    
    printf("\nEtat de la pile :\n");
    afficherPile(maPile);
    
    printf("Je depile %d\n", depiler(maPile));
    printf("Je depile %d\n", depiler(maPile));
    
    printf("\nEtat de la pile :\n");
    afficherPile(maPile);
    
    return 0;
}*/

/**/typedef struct File File;

struct File
{
    Element *premier;
};

File *initialiser()
{
    File *file = malloc(sizeof(*file));
    
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    return file;
}

void enfiler(File *file, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    nouveau->nombre = nvNombre;
    nouveau->suivant = NULL;
    
    if (file->premier != NULL)
    {
        Element *elementActuel = file->premier;
        while (elementActuel->suivant != NULL) {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else
    {
        file->premier = nouveau;
    }
}

int defiler(File * file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int nombreDefile = 0;
    
    if (file->premier != NULL)
    {
        Element *elementDefile = file->premier;
        
        nombreDefile = elementDefile->nombre;
        file->premier = elementDefile->suivant;
        free(elementDefile);
    }
    
    return nombreDefile;
}

void afficherFile(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = file->premier;
    
    while (actuel != NULL) {
        printf("%d ", actuel->nombre);
        actuel = actuel->suivant;
    }
    
    printf("\n\n");
}

int main(int argc, char *argv[]){
    
    File *maFile = initialiser();
    
    enfiler(maFile, 4);
    enfiler(maFile, 8);
    enfiler(maFile, 15);
    enfiler(maFile, 16);
    enfiler(maFile, 23);
    enfiler(maFile, 42);
    
    printf("\nEtat de la file :\n");
    afficherFile(maFile);
    
    printf("Je defile %d\n", defiler(maFile));
    printf("Je defile %d\n", defiler(maFile));
    
    printf("\nEtat de la file :\n");
    afficherFile(maFile);
    
    return 0;
}/**/

#endif
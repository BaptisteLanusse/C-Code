//
//  main.c
//  SoundVisualizer
//
//  Created by Lanusse Baptiste on 12/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "fmod.h"

#undef main

#define LARGEUR_FENETRE         1024
#define HAUTEUR_FENETRE         800
#define RATIO                   (HAUTEUR_FENETRE / 255.0)
#define DELAI_RAFRAICHISSEMENT  25
#define TAILLE_SPECTRE          1024

void setPixel(SDL_Surface * surface, int x, int y, Uint32 pixel);

int main (int argc, char *argv[]){
    
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    char continuer = 1;
    
    int hauteurBarre = 0, tempsActuel = 0, tempsPrecedent = 0, i = 0, j = 0;
    
    float spectre[TAILLE_SPECTRE];
    
    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_CHANNEL *musicChannel;
    FMOD_RESULT resultat;
    
    
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    
    resultat = FMOD_System_CreateSound(system, "Arctic_Monkeys_-_R_U_Mine.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }
    
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
    
    FMOD_System_GetChannel(system, 0, &musicChannel);
    
    /* Initialisation de la SDL */
    
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Visualisateur de spectre sonore", NULL);
    
    /* Boucle principale */
    
    while (continuer) {
        
        SDL_PollEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        
        /* On efface l'écran */
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        
        /* Gestion du temps */
        
        tempsActuel = SDL_GetTicks();
        
        if (tempsActuel - tempsPrecedent < DELAI_RAFRAICHISSEMENT)
        {
            SDL_Delay(DELAI_RAFRAICHISSEMENT - (tempsActuel - tempsPrecedent));
        }
        
        tempsPrecedent = SDL_GetTicks();
        
        /* Dessin du spectre sonore */
        
        FMOD_Channel_GetSpectrum(musicChannel, spectre, TAILLE_SPECTRE, 0, FMOD_DSP_FFT_WINDOW_RECT);
        
        SDL_LockSurface(ecran);
        
        for (i = 0; i < LARGEUR_FENETRE; i++)
        {
            hauteurBarre = spectre[i] * 20 * HAUTEUR_FENETRE;
            
            if (hauteurBarre > HAUTEUR_FENETRE)
                hauteurBarre = HAUTEUR_FENETRE;
            
            for (j = HAUTEUR_FENETRE - hauteurBarre; j < HAUTEUR_FENETRE; j++)
            {
                setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255 - (j / RATIO), j / RATIO, 0));
            }
        }
        
        SDL_UnlockSurface(ecran);
        
        SDL_Flip(ecran);
    }
    
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    
    switch(bpp) {
        case 1:
            *p = pixel;
            break;
            
        case 2:
            *(Uint16 *)p = pixel;
            break;
            
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
            
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}
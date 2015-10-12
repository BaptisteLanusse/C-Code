//
//  main.c
//  FMOD_Sound
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

int main(int argc, const char *argv[]){
    
    SDL_Surface *ecran = NULL, *viseur = NULL;
    SDL_Event event;
    SDL_Rect position;
    int continuer = 1;
    
    FMOD_SYSTEM *system;
    FMOD_SOUND *tir;
    FMOD_SOUND *musique;
    
    FMOD_CHANNEL *musicChannel, *effectChannel;
    
    FMOD_CHANNELGROUP *musicChannelGroup, *effectChannelGroup;
    
    FMOD_RESULT resultat;
    
    FMOD_RESULT resultatMusic;
    
    /* Création et initialisation d'un objet système */
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    
    FMOD_System_CreateChannelGroup(system, "music", &musicChannelGroup);
    FMOD_System_CreateChannelGroup(system, "effect", &effectChannelGroup);
    
    /* Chargement du son et vérification du chargement */
    resultat = FMOD_System_CreateSound(system, "pan.wav", FMOD_CREATESAMPLE, 0, &tir);
    
    resultatMusic = FMOD_System_CreateSound(system, "hype_home.mp3", FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire pan.wav\n");
        exit(EXIT_FAILURE);
    }
    
    FMOD_Sound_SetLoopCount(musique, -1);
    
    FMOD_System_PlaySound(system, musique, musicChannelGroup, 0, &musicChannel);
    
    /* Initialisation de la SDL */
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_ShowCursor(SDL_DISABLE);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du son avec FMOD", NULL);
    
    viseur = IMG_Load("viseur.png");
    
    while (continuer)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                /* Lorqu'on clique, on joue le son */
                FMOD_System_PlaySound(system, tir, effectChannelGroup, 0, &effectChannel);
                break;
            case SDL_MOUSEMOTION:
                /* Lorsqu'on déplace la souris, on place le centre du viseur à la position de la souris
                 ... D'où notamment le "viseur->w / 2" pour réussir à faire cela */
                position.x = event.motion.x - (viseur->w / 2);
                position.y = event.motion.y - (viseur->h / 2);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_p) //Si on appuie sur P
                {
                    FMOD_CHANNELGROUP *canal;
                    FMOD_BOOL etat;
                    FMOD_System_GetMasterChannelGroup(system, &canal);
                    FMOD_ChannelGroup_GetPaused(canal, &etat);
                    
                    if (etat) // Si la chanson est en pause
                        FMOD_ChannelGroup_SetPaused(canal, 0); // On enlève la pause
                    else // Sinon, elle est en cours de lecture
                        FMOD_ChannelGroup_SetPaused(canal, 1); // On active la pause
                }
                break;
        }
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(viseur, NULL, ecran, &position);
        SDL_Flip(ecran);
    }
    
    /* On ferme la SDL */
    SDL_FreeSurface(viseur);
    SDL_Quit();
    
    /* On libère le son et on ferme et libère l'objet système */
    FMOD_Sound_Release(tir);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    
    return EXIT_SUCCESS;
}
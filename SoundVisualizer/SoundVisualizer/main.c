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

int main (int argc, char *argv[]){
    
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    char continuer = 1;
    
    float spectre[512];
    
    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    
    FMOD_RESULT resultat;
    
    FMOD_CHANNEL *musicChannel;
    
    FMOD_CHANNELGROUP *musicChannelGroup;
    
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    
    FMOD_System_CreateChannelGroup(system, "musique", &musicChannelGroup);
    
    resultat = FMOD_System_CreateSound(system, "hype_home.mp3", FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire hype_home.mp3\n");
        exit(EXIT_FAILURE);
    }
    
    FMOD_Sound_SetLoopCount(musique, -1);
    
    FMOD_System_PlaySound(system, musique, musicChannelGroup, 0, &musicChannel);
    
    SDL_Init(SDL_INIT_VIDEO);
    
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Visualisateur de spectre sonore", NULL);
    
    while (continuer) {
        
        //FMOD_Channel_GetSpectrum(musicChannel, spectre, 512, 0, FMOD_DSP_FFT_WINDOW_RECT);
        
        SDL_WaitEvent(&event);
        
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
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_Flip(ecran);
    }
    
    SDL_Quit();
    
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    
    return EXIT_SUCCESS;
}
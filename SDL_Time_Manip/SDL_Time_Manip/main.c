//
//  main.c
//  SDL_Time_Manip
//
//  Created by Lanusse Baptiste on 12/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//

#include <stdio.h>
#include "SDL.h"

#undef main

#define FPS 60
#define TIMER 1000 / FPS

Uint32 bougerZozor(Uint32 intervalle, void *parametre);

int main(int argc, const char * argv[]) {
    
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event;
    SDL_TimerID timer;
    char continuer = 1;
    
    char versLaDroite = 1, versLeBas = 1;
    
    char pause = 0;
    
    int tempsPrecedent = 0, tempsActuel = 0;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    timer = SDL_AddTimer(30, bougerZozor, &positionZozor);
    
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du temps en SDL", NULL);
    
    zozor = SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));
    
    positionZozor.x = ecran->w / 2 - zozor->w / 2;
    positionZozor.y = ecran->h / 2 - zozor->h / 2;
    
    SDL_EnableKeyRepeat(10, 10);
    
    while (continuer) {
        
        SDL_PollEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_p:
                        pause = !pause;
                        break;
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
                break;
        }
        
        tempsActuel = SDL_GetTicks();
        
        if (tempsActuel - tempsPrecedent > TIMER)
        {
            if (!pause) {
                if (positionZozor.x + zozor->w == ecran->w) {
                    versLaDroite = 0;
                }else if (positionZozor.x == 0) {
                    versLaDroite = 1;
                }
                
                if (positionZozor.y + zozor->h == ecran->h) {
                    versLeBas = 0;
                } else if (positionZozor.y == 0) {
                    versLeBas = 1;
                }
                
                if (versLaDroite) {
                    positionZozor.x++;
                } else {
                    positionZozor.x--;
                }
                
                if (versLeBas) {
                    positionZozor.y++;
                } else {
                    positionZozor.y--;
                }
            }
            
            tempsPrecedent = tempsActuel;
        }
        else
        {
            SDL_Delay(TIMER - (tempsActuel - tempsPrecedent));
        }
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_Flip(ecran);
        
    }
    
    SDL_RemoveTimer(timer);
    SDL_FreeSurface(zozor);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

Uint32 bougerZozor(Uint32 intervalle, void *parametre)
{
    SDL_Rect *positionZozor = parametre;
    positionZozor->x++;
    
    return intervalle;
}
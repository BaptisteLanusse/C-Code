//
//  main.c
//  SDL_TTF_Test
//
//  Created by Lanusse Baptiste on 12/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//

#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"

#undef main

int main(int argc, const char *argv[]){
    SDL_Surface *ecran = NULL, *texte = NULL;
    SDL_Rect position;
    SDL_Event event;
    
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    
    char continuer = 1;
    
    TTF_Init();
    
    SDL_Init(SDL_INIT_VIDEO);
    
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Ecrire du texte", NULL);
    
    police = TTF_OpenFont("AlphaWood.ttf", 65);
    
    texte = TTF_RenderText_Blended(police, "This is a test", couleurNoire);
    
    while (continuer) {
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
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        
        position.x = ecran->w / 2 - texte->w / 2;
        position.y = ecran->h / 2 - texte->h / 2;
        
        SDL_BlitSurface(texte, NULL, ecran, &position);
        
        SDL_Flip(ecran);
        
    }
    
    SDL_FreeSurface(texte);
    SDL_Quit();
    
    TTF_CloseFont(police);
    TTF_Quit();
    
    return EXIT_SUCCESS;
}
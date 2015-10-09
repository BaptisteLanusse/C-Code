//
//  editeur.c
//  MarioSokoban
//
//  Created by Lanusse Baptiste on 09/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//

#include <stdio.h>
#include "editeur.h"

void editeur(SDL_Surface* ecran){
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL;
    SDL_Rect position;
    SDL_Event event;
    
    char continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    char objetActuel = MUR, i = 0, j = 0;
    char carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    
    // Chargement des objets et du niveau
    mur = IMG_Load("images/mur.jpg");
    caisse = IMG_Load("images/caisse.jpg");
    objectif = IMG_Load("images/objectif.png");
    mario = IMG_Load("images/mario_bas.gif");
    
    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);
    
    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                    clicGaucheEnCours = 1;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:
                if (clicGaucheEnCours)
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                }
                else if (clicDroitEnCours)
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                    case SDLK_c:
                        chargerNiveau(carte);
                        break;
                    case SDLK_KP1:
                        objetActuel = MUR;
                        break;
                    case SDLK_KP2:
                        objetActuel = CAISSE;
                        break;
                    case SDLK_KP3:
                        objetActuel = OBJECTIF;
                        break;
                    case SDLK_KP4:
                        objetActuel = MARIO;
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        
        for (i = 0; i < NB_BLOCS_LARGEUR; i++)
        {
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;
                
                switch (carte[i][j]) {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                    case MARIO:
                        SDL_BlitSurface(mario, NULL, ecran, &position);
                        break;
                }
            }
        }
        
        SDL_Flip(ecran);
        
    }
    
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);
}
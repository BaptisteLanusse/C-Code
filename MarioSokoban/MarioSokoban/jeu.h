//
//  jeu.h
//  MarioSokoban
//
//  Created by Lanusse Baptiste on 09/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//

#ifndef jeu_h
#define jeu_h

#include "SDL.h"
#include "SDL_image.h"
#include "constantes.h"

void jouer(SDL_Surface* ecran);

void deplacerJoueur(char[][NB_BLOCS_HAUTEUR], SDL_Rect*, char);

void deplacerCaisse(char*, char*);

#endif /* jeu_h */

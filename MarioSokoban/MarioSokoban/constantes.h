//
//  constantes.h
//  MarioSokoban
//
//  Created by Lanusse Baptiste on 09/10/2015.
//  Copyright © 2015 Baptiste Lanusse. All rights reserved.
//
// Définit les constantes pour la totalité du programme

#ifndef constantes_h
#define constantes_h

#define TAILLE_BLOC         34
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum {HAUT, BAS, GAUCHE, DROITE};
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif /* constantes_h */

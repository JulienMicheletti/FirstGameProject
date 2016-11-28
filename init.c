#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

sprite		init_sprite(sprite sp)
{  
  sp.mur = IMG_Load("sprites/mur.png");
  sp.bloc = IMG_Load("sprites/bloc.png");
  sp.heros[BAS] = IMG_Load("sprites/Devant.png");
  sp.heros[GAUCHE] = IMG_Load("sprites/gauche.png");
  sp.heros[HAUT] = IMG_Load("sprites/derriere.png");
  sp.heros[DROITE] = IMG_Load("sprites/Droite.png");
  sp.fin = IMG_Load("sprites/objectif.png");
  sp.vide = IMG_Load("sprites/sol.png");
  sp.piege = IMG_Load("sprites/piege.gif");
  sp.piegeON = IMG_Load("sprites/piegeon.png");
  return (sp);
}

compteur	init_compteur(compteur count)
{
  count.continuer = 1;
  count.i = 0;
  count.j = 0;
  count.check = 0;
  count.select = 0;
  return (count);
}

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

sprite		init_sprite(sprite sp)
{  
  sp.mur = IMG_Load("sprites/mur.png");
  sp.bloc = SDL_LoadBMP("sprites/bloc1.bmp");
  sp.heros[BAS] = SDL_LoadBMP("sprites/devant.bmp");
  sp.heros[GAUCHE] = SDL_LoadBMP("sprites/gauche1.bmp");
  sp.heros[HAUT] = SDL_LoadBMP("sprites/arriere.bmp");
  sp.heros[DROITE] = SDL_LoadBMP("sprites/droite.bmp");
  sp.fin = SDL_LoadBMP("sprites/porteF.bmp");
  sp.finouvert = SDL_LoadBMP("sprites/porteO.bmp");
  SDL_SetColorKey(sp.finouvert, SDL_SRCCOLORKEY, SDL_MapRGB(sp.finouvert->format, 0, 0, 0));
  sp.vide = IMG_Load("sprites/sol1.png");
  sp.piege = IMG_Load("sprites/piege.png");
  sp.piegeON = SDL_LoadBMP("sprites/arbre.bmp");
  sp.levier = SDL_LoadBMP("sprites/levier.bmp");
  SDL_SetColorKey(sp.levier, SDL_SRCCOLORKEY, SDL_MapRGB(sp.levier->format, 255, 255, 255));
  sp.levierON = SDL_LoadBMP("sprites/levierON.bmp");
  return (sp);
}

compteur	init_compteur(compteur count)
{
  count.continuer = 1;
  count.i = 0;
  count.j = 0;
  count.check = 0;
  count.select = 0;
  count.checklevier = 0;
  return (count);
}


SDL_Rect	PositionJoueur(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect posPlayer)
{
  int	i = 0, j = 0;
  
  for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
      for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
  	{
  	  if (carte[i][j] == HEROS)
  	    {
  	      posPlayer.x = i;
  	      posPlayer.y = j;
  	      carte[i][j] = VIDE;
  	    }
  	}
    }
  return(posPlayer);
}

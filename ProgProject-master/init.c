#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

sprite		init_sprite(sprite sp)
{  
  sp.mur = IMG_Load("sprites/mur.png");
  sp.bloc = IMG_Load("sprites/bloc1.png");
  sp.heros[BAS] = IMG_Load("sprites/devant.png");
  sp.heros[GAUCHE] = IMG_Load("sprites/gauche1.png");
  sp.heros[HAUT] = IMG_Load("sprites/arriere.png");
  sp.heros[DROITE] = IMG_Load("sprites/droite.png");
  sp.fin = IMG_Load("sprites/porteF.png");
  sp.finouvert = IMG_Load("sprites/porteO.png");
  sp.vide = IMG_Load("sprites/sol1.png");
  sp.piege = IMG_Load("sprites/piege.png");
  sp.piegeON = IMG_Load("sprites/arbre.png");
  sp.levier = IMG_Load("sprites/levier.png");
  sp.levierON = IMG_Load("sprites/levierON.png");
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

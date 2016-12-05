#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

sprite		init_sprite(sprite sp) //Initialisation des sprites
{  
  sp.mur = IMG_Load("sprites/mur1.png");
  sp.bloc = SDL_LoadBMP("sprites/bloc1.bmp");
  sp.heros[BAS] = SDL_LoadBMP("sprites/devant.bmp");
  sp.heros[GAUCHE] = SDL_LoadBMP("sprites/gauche1.bmp");
  sp.heros[HAUT] = SDL_LoadBMP("sprites/arriere.bmp");
  sp.heros[DROITE] = SDL_LoadBMP("sprites/droite.bmp");
  sp.heros[HAUTP] = SDL_LoadBMP("sprites/devant_p.bmp");
  sp.heros[BASP] = SDL_LoadBMP("sprites/arriere_p.bmp");
  sp.heros[GAUCHEP] = SDL_LoadBMP("sprites/gauche_p.bmp");
  sp.heros[DROITEP] = SDL_LoadBMP("sprites/droit_p.bmp");
  sp.fin = SDL_LoadBMP("sprites/porteF.bmp");
  sp.finouvert = SDL_LoadBMP("sprites/porteO.bmp");
  sp.vide = IMG_Load("sprites/sol1.png");
  sp.piege = IMG_Load("sprites/piege.png");
  sp.piegeON = SDL_LoadBMP("sprites/arbre.bmp");
  sp.levier = SDL_LoadBMP("sprites/levier.bmp");
  sp.levierON = SDL_LoadBMP("sprites/levierON.bmp");
  sp.casse = SDL_LoadBMP("sprites/casse.bmp");
  sp.pioche = SDL_LoadBMP("sprites/pioche.bmp");
  sp.coffre = SDL_LoadBMP("sprites/coffre.bmp");
  SDL_SetColorKey(sp.piegeON, SDL_SRCCOLORKEY, SDL_MapRGB(sp.piegeON->format, 255, 255, 255));
  return (sp);
}

compteur	init_compteur(compteur count) //Initialisation des compteurs utilisés dans le prog
{
  count.continuer = 1;
  count.i = 0;
  count.j = 0;
  count.check = 0;
  count.select = 0;
  count.checklevier = 0;
  count.checkpioche = 0;
  return (count);
}


SDL_Rect	PositionJoueur(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect posPlayer) //On cherche dans le double tableau la position du joueur
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

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"
#include "level.h"


void	play(SDL_Surface *ecran)
{
  SDL_Surface	*heros[4] = {NULL};
  SDL_Surface	*mur = NULL, *herosActuel = NULL;
  SDL_Rect	pos, posPlayer;
  SDL_Event	event;
  int	continuer = 1, i = 0, j = 0;
  int	carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

  //chargement des sprites
  
  mur = IMG_Load("mur.png");
  heros[BAS] = IMG_Load("heros_avant.gif");
  heros[GAUCHE] = IMG_Load("heros_gauche.gif");
  heros[HAUT] = IMG_Load("heros_arrière.gif");
  heros[DROITE] = IMG_Load("heros_droite.gif");
  
  herosActuel = heros[BAS];
  if (!chargerNiveau(carte))
    exit(EXIT_FAILURE);
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
  SDL_EnableKeyRepeat(100, 100);
  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
  	{
  	case SDL_QUIT:
  	  continuer = 0;
  	  break;
  	case SDL_KEYDOWN:
  	  switch(event.key.keysym.sym)
  	    {
  	    case SDLK_ESCAPE:
  	      continuer = 0;
  	      break;
  	    case SDLK_UP:
  	      herosActuel = heros[HAUT];
  	      moovePlayer(carte, &posPlayer, HAUT);
  	      break;
  	    case SDLK_DOWN:
  	      herosActuel = heros[BAS];
  	      moovePlayer(carte, &posPlayer, BAS);
  	      break;
  	    case SDLK_LEFT:
  	      herosActuel = heros[GAUCHE];
  	      moovePlayer(carte, &posPlayer, GAUCHE);
  	      break;
  	    case SDLK_RIGHT:
  	      herosActuel = heros[DROITE];
  	      moovePlayer(carte, &posPlayer, DROITE);
  	      break;
  	    }
  	  break;
  	}
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
	{
	  for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
	    {
	      pos.x = i * TAILLE_BLOC;
	      pos.y = j * TAILLE_BLOC;
	      switch(carte[i][j])
		{
		case MUR:
		  SDL_BlitSurface(mur, NULL, ecran, &pos);
		  break;
		}
	    }
	}
      pos.x = posPlayer.x * TAILLE_BLOC;
      pos.y = posPlayer.y * TAILLE_BLOC;
      SDL_SetColorKey(herosActuel, SDL_SRCCOLORKEY, SDL_MapRGB(herosActuel->format, 0, 0, 0));
      SDL_BlitSurface(herosActuel, NULL, ecran, &pos);
      SDL_Flip(ecran);
    }
  
  SDL_EnableKeyRepeat(0, 0);
  SDL_FreeSurface(mur);
  for(i = 0 ; i < 4 ; i++)
    SDL_FreeSurface(heros[i]);
}

void	moovePlayer(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
  switch(direction)
    {
    case HAUT:
      if (pos->y - 1 < 0)
	break;
      if (carte[pos->x][pos->y - 1] == MUR)
	break;
      pos->y--;
      break;
    case BAS:
      if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
	break;
      if (carte[pos->x][pos->y + 1] == MUR)
	break;
      pos->y++;
      break;
    case GAUCHE:
      if (pos->x - 1 < 0)
	break;
      if (carte[pos->x - 1][pos->y] == MUR)
	break;
      pos->x--;
      break;
    case DROITE:
      if (pos->x + 1 > NB_BLOCS_LARGEUR)
	break;
      if (carte[pos->x + 1][pos->y] == MUR)
	break;
      pos->x++;
      break;
    }
}

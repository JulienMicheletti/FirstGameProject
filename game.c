#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"
#include "level.h"

void	moovebloc(int *first, int *second)
{
  if (*first == BLOC)
    {
      *second = BLOC;
      *first = VIDE;
    }
}

void	play(SDL_Surface *ecran)
{
  SDL_Surface	*heros[4] = {NULL};
  SDL_Surface	*mur = NULL, *herosActuel = NULL, *fin = NULL, *bloc = NULL, *vide = NULL;
  SDL_Rect	pos, posPlayer;
  SDL_Event	event;
  int	continuer = 1, i = 0, j = 0, check = 0, select = 0;
  int	carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

  mur = IMG_Load("sprites/mur.png");
  bloc = IMG_Load("sprites/bloc.png");
  heros[BAS] = IMG_Load("sprites/Devant.png");
  heros[GAUCHE] = IMG_Load("sprites/gauche.png");
  heros[HAUT] = IMG_Load("sprites/derriere.png");
  heros[DROITE] = IMG_Load("sprites/Droite.png");
  fin = IMG_Load("sprites/objectif.png");
  vide = IMG_Load("sprites/sol.png");

  herosActuel = heros[BAS];
  if (!chargerNiveau(carte, select))
    exit(EXIT_FAILURE);
  posPlayer = PositionJoueur(carte, posPlayer);
  while (continuer)
    {
      SDL_PollEvent(&event);
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
  	}
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      check = 0;
      for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
      	{
      	  for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
      	    {
      	      pos.x = i * TAILLE_BLOC;
      	      pos.y = j * TAILLE_BLOC;
	      if (carte[i][j] == MUR)
		SDL_BlitSurface(mur, NULL, ecran, &pos);
	      if (carte[i][j] == FIN)
		{
		  SDL_BlitSurface(fin, NULL, ecran, &pos);
		  check = 1;
		}
	      if (carte[i][j] == BLOC)
		SDL_BlitSurface(bloc, NULL, ecran, &pos);
	      if (carte[i][j] == VIDE)
		SDL_BlitSurface(vide, NULL, ecran, &pos);
	      
      	    }
      	}
       if (!check)
      	{
      	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      	  select++;
      	  if (select == 3)
      	    continuer = 0;
      	  chargerNiveau(carte, select);
      	  posPlayer = PositionJoueur(carte, posPlayer);
      	}
       SDL_Delay(15);
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
  if (direction == HAUT)
    {
      if (pos->y - 1 < 0)
	return;
      else if (carte[pos->x][pos->y - 1] == MUR)
	return;
      else if (carte[pos->x][pos->y - 1] == FIN)
	carte[pos->x][pos->y - 1] = VIDE;
      if (carte[pos->x][pos->y - 1] == BLOC && (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR || carte[pos->x][pos->y - 2] == BLOC))
	return;
      moovebloc(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
      pos->y--;
      return;
    }
  else if (direction == BAS)
    {
      if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
	return;
      else if (carte[pos->x][pos->y + 1] == MUR)
	return;
      else if (carte[pos->x][pos->y + 1] == FIN)
	carte[pos->x][pos->y + 1] = VIDE;
      if (carte[pos->x][pos->y + 1] == BLOC && (pos->y + 2 < 0 || carte[pos->x][pos->y + 2] == MUR || carte[pos->x][pos->y + 2] == BLOC))
	return;
      moovebloc(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
      pos->y++;
      return;
    }
  else if (direction == GAUCHE)
    {
      if (pos->x - 1 < 0)
	return;
      else if (carte[pos->x - 1][pos->y] == MUR)
        return;
      else if (carte[pos->x - 1][pos->y] == FIN)
	carte[pos->x - 1][pos->y] = VIDE;
      if (carte[pos->x - 1][pos->y] == BLOC && (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR || carte[pos->x - 2][pos->y] == BLOC))
	return;
      moovebloc(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
      pos->x--;
      return;
    }
  else if (direction == DROITE)
    {
      if (pos->x + 1 > NB_BLOCS_LARGEUR)
	return;
      else if (carte[pos->x + 1][pos->y] == MUR)
	return;
      else if (carte[pos->x + 1][pos->y] == FIN)
	carte[pos->x + 1][pos->y] = VIDE;
      if (carte[pos->x + 1][pos->y] == BLOC && (pos->x + 2 < 0 || carte[pos->x + 2][pos->y] == MUR || carte[pos->x + 2][pos->y] == BLOC))
	return;
      moovebloc(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
      pos->x++;
      return;
    }
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

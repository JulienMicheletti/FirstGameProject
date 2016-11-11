#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"
#include "level.h"

SDL_Rect	PositionP(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect posPacerelle)
{
  int	i = 0, j = 0;
  
  for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
      for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
  	{
  	  if (carte[i][j] == PACERELLE)
  	    {
  	      posPacerelle.x = i;
  	      posPacerelle.y = j;
  	      carte[i][j] = VIDE;
  	    }
  	}
    }
  return(posPacerelle);
}

void	play(SDL_Surface *ecran)
{
  SDL_Surface	*heros[4] = {NULL};
  SDL_Surface	*mur = NULL, *herosActuel = NULL, *fin = NULL, *pacerelle = NULL;
  SDL_Rect	pos, posPlayer, posP, posF;
  SDL_Event	event;
  int	continuer = 1, i = 0, j = 0, check = 0, select = 0;
  int	now = 0, prev = 0;
  int	carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

  mur = IMG_Load("mur.png");
  pacerelle = IMG_Load("mur.png");
  heros[BAS] = IMG_Load("heros_avant.gif");
  heros[GAUCHE] = IMG_Load("heros_gauche.gif");
  heros[HAUT] = IMG_Load("heros_arrière.gif");
  heros[DROITE] = IMG_Load("heros_droite.gif");
  fin = IMG_Load("objectif.png");

  herosActuel = heros[BAS];
  if (!chargerNiveau(carte, select))
    exit(EXIT_FAILURE);
  posPlayer = PositionJoueur(carte, posPlayer);
  posP = PositionP(carte, posP);
  SDL_EnableKeyRepeat(100, 100);
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
      	      switch(carte[i][j])
      		{
      		case MUR:
      		  SDL_BlitSurface(mur, NULL, ecran, &pos);
      		  break;
		case FIN: 
		  SDL_BlitSurface(fin, NULL, ecran, &pos);
		  check = 1;
      		  break;
		case PACERELLE:
		  SDL_BlitSurface(pacerelle, NULL, ecran, &pos);
		  break;
      		}
      	    }
      	}
	now = SDL_GetTicks();
	if (now - prev > 30)
	  {
	    posP.x++;
	    prev = now;
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
      posF.x = posP.x * TAILLE_BLOC;
      posF.y = posP.y * TAILLE_BLOC;
      pos.x = posPlayer.x * TAILLE_BLOC;
      pos.y = posPlayer.y * TAILLE_BLOC;
      SDL_SetColorKey(pacerelle, SDL_SRCCOLORKEY, SDL_MapRGB(pacerelle->format, 0, 0, 0));
      SDL_BlitSurface(pacerelle, NULL, ecran, &posF);
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
      else if (carte[pos->x][pos->y - 1] == MUR)
	break;
      else if (carte[pos->x][pos->y] == FIN)
	{
	  carte[pos->x][pos->y] = VIDE;
	  break;
	}
      pos->y--;
      break;
    case BAS:
      if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
	break;
      else if (carte[pos->x][pos->y + 1] == MUR)
	break;
      else if (carte[pos->x][pos->y] == FIN)
	{
	  carte[pos->x][pos->y] = VIDE;
	  break;
	}
      pos->y++;
      break;
    case GAUCHE:
      if (pos->x - 1 < 0)
	break;
      else if (carte[pos->x - 1][pos->y] == MUR)
	break;
      else if (carte[pos->x][pos->y] == FIN)
	{
	  carte[pos->x][pos->y] = VIDE;
	  break;
	}
      pos->x--;
      break;
    case DROITE:
      if (pos->x + 1 > NB_BLOCS_LARGEUR)
	break;
      else if (carte[pos->x + 1][pos->y] == MUR)
	break;
      else if (carte[pos->x][pos->y] == FIN)
	{
	  carte[pos->x][pos->y] = VIDE;
	  break;
	}
      pos->x++;
      break;
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

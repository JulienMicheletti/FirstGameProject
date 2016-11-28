#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

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
  sprite	sp;
  compteur	count;
  SDL_Rect	pos, posPlayer;
  SDL_Event	event;
  int	carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

  count = init_compteur(count);
  sp = init_sprite(sp);
  sp.herosActuel = sp.heros[BAS];
  if (!chargerNiveau(carte, count.select))
    exit(EXIT_FAILURE);
  posPlayer = PositionJoueur(carte, posPlayer);
  while (count.continuer)
    {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT)
  	  count.continuer = 0;
      else if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    count.continuer = 0;
	  else if (event.key.keysym.sym == SDLK_UP)
	    {
  	      sp.herosActuel = sp.heros[HAUT];
	      moovePlayer(carte, &posPlayer, HAUT);
	    }
	  else if (event.key.keysym.sym == SDLK_DOWN)
	    {
  	      sp.herosActuel = sp.heros[BAS];
	      moovePlayer(carte, &posPlayer, BAS);
	    }
	  else if (event.key.keysym.sym == SDLK_LEFT)
	    {
  	      sp.herosActuel = sp.heros[GAUCHE];
	      moovePlayer(carte, &posPlayer, GAUCHE);
	    }
	  else if (event.key.keysym.sym == SDLK_RIGHT)
	    {
  	      sp.herosActuel = sp.heros[DROITE];
	      moovePlayer(carte, &posPlayer, DROITE);
	    }
  	}
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      count.check = 0;
      for (count.i = 0 ; count.i < NB_BLOCS_LARGEUR ; count.i++)
      	{
      	  for (count.j = 0 ; count.j < NB_BLOCS_HAUTEUR ; count.j++)
      	    {
      	      pos.x = count.i * TAILLE_BLOC;
      	      pos.y = count.j * TAILLE_BLOC;
	      if (carte[count.i][count.j] == MUR)
		SDL_BlitSurface(sp.mur, NULL, ecran, &pos);
	      if (carte[count.i][count.j] == FIN)
		{
		  SDL_BlitSurface(sp.fin, NULL, ecran, &pos);
		  count.check = 1;
		}
	      if (carte[count.i][count.j] == BLOC)
		SDL_BlitSurface(sp.bloc, NULL, ecran, &pos);
	      if (carte[count.i][count.j] == VIDE)
		SDL_BlitSurface(sp.vide, NULL, ecran, &pos);
	      if (carte[count.i][count.j] == PIEGE)
	      	SDL_BlitSurface(sp.piege, NULL, ecran, &pos);
	      if (carte[count.i][count.j] == PIEGEON)
	      	SDL_BlitSurface(sp.piegeON, NULL, ecran, &pos);
	      
      	    }
      	}
       if (!count.check)
      	{
      	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      	  count.select++;
	  printf("%d\n", count.select);
      	  if (count.select == 3)
      	    count.continuer = 0;
      	  chargerNiveau(carte, count.select);
      	  posPlayer = PositionJoueur(carte, posPlayer);
      	}
       SDL_Delay(15);
       pos.x = posPlayer.x * TAILLE_BLOC;
       pos.y = posPlayer.y * TAILLE_BLOC;
       SDL_SetColorKey(sp.herosActuel, SDL_SRCCOLORKEY, SDL_MapRGB(sp.herosActuel->format, 0, 0, 0));
       SDL_BlitSurface(sp.herosActuel, NULL, ecran, &pos);
       SDL_Flip(ecran);
    }
  SDL_EnableKeyRepeat(0, 0);
  SDL_FreeSurface(sp.mur);
  for(count.i = 0 ; count.i < 4 ; count.i++)
    SDL_FreeSurface(sp.heros[count.i]);
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
      else if (carte[pos->x][pos->y - 1] == BLOC && (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR || carte[pos->x][pos->y - 2] == BLOC))
	return;
      else if (carte[pos->x][pos->y] == PIEGE)
	carte[pos->x][pos->y] = PIEGEON;
      else if (carte[pos->x][pos->y - 1] == PIEGEON)
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
      else if (carte[pos->x][pos->y + 1] == BLOC && (pos->y + 2 < 0 || carte[pos->x][pos->y + 2] == MUR || carte[pos->x][pos->y + 2] == BLOC))
	return;
      else if (carte[pos->x][pos->y] == PIEGE)
	carte[pos->x][pos->y] = PIEGEON;
      else if (carte[pos->x][pos->y + 1] == PIEGEON)
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
      else if (carte[pos->x - 1][pos->y] == BLOC && (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR || carte[pos->x - 2][pos->y] == BLOC))
	return;
      else if (carte[pos->x][pos->y] == PIEGE)
	carte[pos->x][pos->y] = PIEGEON;
      else if (carte[pos->x - 1][pos->y] == PIEGEON)
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
      else if (carte[pos->x][pos->y] == PIEGE)
	carte[pos->x][pos->y] = PIEGEON;
      else if (carte[pos->x + 1][pos->y] == PIEGEON)
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

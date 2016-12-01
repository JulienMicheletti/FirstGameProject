#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

void	moovebloc(int *first, int *second)
{
  if (*first == BLOC && *second == VIDE)
    {
      *second = BLOC;
      *first = VIDE;
    }
}


void	mooveUP(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, compteur count)
{
  if (pos->y - 1 < 0)
    return;
  else if (carte[pos->x][pos->y - 1] == MUR)
    return;
  else if (carte[pos->x][pos->y - 1] == FIN)
    {
      if (count.checklevier == 1)
	carte[pos->x][pos->y - 1] = VIDE;
      else
	return;
    }
  else if (carte[pos->x][pos->y - 1] == BLOC && (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] != VIDE))
    return;
      else if (carte[pos->x][pos->y] == PIEGE)
	{
	  carte[pos->x][pos->y] = PIEGEON;
	  return;
	}
      else if (carte[pos->x][pos->y - 1] == PIEGEON)
	return;
      else if (carte[pos->x][pos->y - 1] == LEVIER || carte[pos->x][pos->y - 1] == LEVIERON)
	{
	  carte[pos->x][pos->y - 1] = LEVIERON;
	  return;
	}
      moovebloc(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
      pos->y--;
      return;
}

void	mooveDOWN(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, compteur count)
{
  if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
    return;
  else if (carte[pos->x][pos->y + 1] == MUR)
    return;
  else if (carte[pos->x][pos->y + 1] == FIN)
    {
      if (count.checklevier == 1)
	carte[pos->x][pos->y + 1] = VIDE;
      else
	return;
    }
  else if (carte[pos->x][pos->y + 1] == BLOC && (pos->y + 2 < 0 || carte[pos->x][pos->y + 2] != VIDE))
    return;
  else if (carte[pos->x][pos->y] == PIEGE)
    carte[pos->x][pos->y] = PIEGEON;
  else if (carte[pos->x][pos->y + 1] == PIEGEON)
    return;
  else if (carte[pos->x][pos->y + 1] == LEVIER || carte[pos->x][pos->y + 1] == LEVIERON)
    {
      carte[pos->x][pos->y + 1] = LEVIERON;
      return;
    }
  moovebloc(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
  pos->y++;
  return;
}

void	mooveLEFT(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, compteur count)
{
  if (pos->x - 1 < 0)
    return;
  else if (carte[pos->x - 1][pos->y] == MUR)
    return;
  else if (carte[pos->x - 1][pos->y] == FIN)
    {
      if (count.checklevier == 1)
	carte[pos->x - 1][pos->y] = VIDE;
      else
	return;
    }
  else if (carte[pos->x - 1][pos->y] == BLOC && (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] != VIDE))
    return;
  else if (carte[pos->x][pos->y] == PIEGE)
    carte[pos->x][pos->y] = PIEGEON;
  else if (carte[pos->x - 1][pos->y] == PIEGEON)
    return;
  else if (carte[pos->x - 1][pos->y] == LEVIER || carte[pos->x - 1][pos->y] == LEVIERON)
    {
      carte[pos->x - 1][pos->y] = LEVIERON;
      return;
    }
  moovebloc(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
  pos->x--;
  return;
}
void	mooveRIGHT(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, compteur count)
{
  if (pos->x + 1 > NB_BLOCS_LARGEUR)
    return;
  else if (carte[pos->x + 1][pos->y] == MUR)
    return;
  else if (carte[pos->x + 1][pos->y] == FIN)
    {
      if (count.checklevier == 1)
	carte[pos->x + 1][pos->y] = VIDE;
      else
	return;
    }
  if (carte[pos->x + 1][pos->y] == BLOC && (pos->x + 2 < 0 || carte[pos->x + 2][pos->y] != VIDE))
    return;
  else if (carte[pos->x][pos->y] == PIEGE)
    carte[pos->x][pos->y] = PIEGEON;
  else if (carte[pos->x + 1][pos->y] == PIEGEON)
    return;
  else if (carte[pos->x + 1][pos->y] == LEVIER || carte[pos->x + 1][pos->y] == LEVIERON)
    {
      carte[pos->x + 1][pos->y] = LEVIERON;
      return;
    }
  moovebloc(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
  pos->x++;
  return;
}

void	moovePlayer(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction, compteur count)
{
  if (direction == HAUT)
    mooveUP(carte, pos, count);
  else if (direction == BAS)
    mooveDOWN(carte, pos, count);
  else if (direction == GAUCHE)
    mooveLEFT(carte, pos, count);
  else if (direction == DROITE)
    mooveRIGHT(carte, pos, count);
    
}

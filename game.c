#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"

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
	exit(1);
      if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    exit(1);
	  if (event.key.keysym.sym == SDLK_UP)
	    {
  	      sp.herosActuel = sp.heros[HAUT];
	      moovePlayer(carte, &posPlayer, HAUT, count);
	    }
	  else if (event.key.keysym.sym == SDLK_DOWN)
	    {
  	      sp.herosActuel = sp.heros[BAS];
	      moovePlayer(carte, &posPlayer, BAS, count);
	    }
	  else if (event.key.keysym.sym == SDLK_LEFT)
	    {
  	      sp.herosActuel = sp.heros[GAUCHE];
	      moovePlayer(carte, &posPlayer, GAUCHE, count);
	    }
	  else if (event.key.keysym.sym == SDLK_RIGHT)
	    {
  	      sp.herosActuel = sp.heros[DROITE];
	      moovePlayer(carte, &posPlayer, DROITE, count);
	    }
  	}
      /* SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); */
      count.check = 0;
      for (count.i = 0 ; count.i < NB_BLOCS_LARGEUR ; count.i++)
      	{
      	  for (count.j = 0 ; count.j < NB_BLOCS_HAUTEUR ; count.j++)
	    {
      	      pos.x = count.i * TAILLE_BLOC;
      	      pos.y = count.j * TAILLE_BLOC;
	      if (carte[count.i][count.j] == MUR)
	      	SDL_BlitSurface(sp.mur, NULL, ecran, &pos);
	      else if (carte[count.i][count.j] == FIN)
	      	{
		  if (count.checklevier == 1)
		    SDL_BlitSurface(sp.finouvert, NULL, ecran, &pos);
		  else
		    SDL_BlitSurface(sp.fin, NULL, ecran, &pos);
	      	  count.check = 1;
		}
	      else if (carte[count.i][count.j] == BLOC)
	      	SDL_BlitSurface(sp.bloc, NULL, ecran, &pos);
	      else if (carte[count.i][count.j] == VIDE)
	      	SDL_BlitSurface(sp.vide, NULL, ecran, &pos);
	      else if (carte[count.i][count.j] == PIEGE)
	      	SDL_BlitSurface(sp.piege, NULL, ecran, &pos);
	      else if (carte[count.i][count.j] == PIEGEON)
		  SDL_BlitSurface(sp.piegeON, NULL, ecran, &pos);
	      else if (carte[count.i][count.j] == LEVIER)
		  SDL_BlitSurface(sp.levier, NULL, ecran, &pos);
	      else if (carte[count.i][count.j] == LEVIERON)
		{
		  SDL_BlitSurface(sp.levierON, NULL, ecran, &pos);
		  count.checklevier = 1;
		}
      	    }
      	}
       if (!count.check)
      	{
      	  count.select++;
      	  if (count.select == 3)
      	    count.continuer = 0;
      	  chargerNiveau(carte, count.select);
      	  posPlayer = PositionJoueur(carte, posPlayer);
	  count.checklevier = 0;
      	}
       SDL_Delay(25);
       pos.x = posPlayer.x * TAILLE_BLOC;
       pos.y = posPlayer.y * TAILLE_BLOC;
       SDL_SetColorKey(sp.herosActuel, SDL_SRCCOLORKEY, SDL_MapRGB(sp.herosActuel->format, 255, 255, 255));
       SDL_BlitSurface(sp.herosActuel, NULL, ecran, &pos);
       SDL_Flip(ecran);
    }
  SDL_FreeSurface(sp.mur);
  for(count.i = 0 ; count.i < 4 ; count.i++)
    SDL_FreeSurface(sp.heros[count.i]);
}

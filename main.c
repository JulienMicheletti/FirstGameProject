#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "game.h"
#include "level.h"

int	main(int ac, char **av)
{
  SDL_Surface	*ecran = NULL, *texte = NULL;
  SDL_Rect	position;
  TTF_Font	*police = NULL;
  SDL_Color	blanc = {255, 255, 255};
  SDL_Event	event;
  int		continuer = 1;
  
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  TTF_Init();
  ecran = SDL_SetVideoMode(WIDHT, LENGTH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("My game", NULL);
  police = TTF_OpenFont("typo/house.ttf", 100);
  texte = TTF_RenderText_Blended(police, "The Game", blanc);
  while (continuer)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	continuer = 0;
      else if (event.type == SDL_KEYDOWN)
	{
      	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    continuer = 0;
	  else if (event.key.keysym.sym == SDLK_a)
	    play(ecran);
	}
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      position.x = 60;
      position.y = 370;
      SDL_BlitSurface(texte, NULL, ecran, &position);
      SDL_Flip(ecran);
    }
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_FreeSurface(texte);
  SDL_Quit;
  SDL_Quit();
  return EXIT_SUCCESS;
}

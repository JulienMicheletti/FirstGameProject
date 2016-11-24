#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"
#include "level.h"

int	main(int ac, char **av)
{
  SDL_Surface	*ecran = NULL;
  SDL_Event	event;
  int		continuer;
  
  continuer = 1;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  ecran = SDL_SetVideoMode(WIDHT, LENGTH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("My game", NULL);
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
      	    case SDLK_ESCAPE: //Arrêt du jeu
      	      continuer = 0;
      	      break;
	    case SDLK_a:
	      play(ecran);
      	      break;
      	    }
      	  break;
	}
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      SDL_Flip(ecran);
    }
  SDL_Quit();
  return EXIT_SUCCESS;
}

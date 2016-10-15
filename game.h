#ifndef	DEF_GAME
#define	DEF_GAME

void	play(SDL_Surface *ecran);
void	moovePlayer(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
int	chargerNiveau(int carte[][NB_BLOCS_HAUTEUR]);

#endif

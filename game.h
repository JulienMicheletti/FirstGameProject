#ifndef	DEF_GAME
#define	DEF_GAME

void	play(SDL_Surface *ecran);
void	moovePlayer(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
int	chargerNiveau(int carte[][NB_BLOCS_HAUTEUR], int);
SDL_Rect	PositionJoueur(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], SDL_Rect posPlayer);
FILE*	selectNiveau(FILE* fichier, int);
sprite		init_sprite(sprite sp);
compteur	init_compteur(compteur count);




#endif

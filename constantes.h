#ifndef	DEF_CONSTANTES
#define	DEF_CONSTANTES

#define TAILLE_BLOC		32
#define	NB_BLOCS_LARGEUR	24
#define NB_BLOCS_HAUTEUR	24
#define WIDHT			TAILLE_BLOC * NB_BLOCS_LARGEUR
#define LENGTH			TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum{HAUT, BAS, GAUCHE, DROITE};
enum{VIDE, MUR, HEROS, FIN, BLOC, PIEGE, PIEGEON};

typedef struct sprite sprite;
struct	sprite
{
  SDL_Surface	*mur;
  SDL_Surface	*herosActuel;
  SDL_Surface	*heros[4];
  SDL_Surface	*fin;
  SDL_Surface	*bloc;
  SDL_Surface	*vide;
  SDL_Surface	*piege;
  SDL_Surface	*piegeON;
};

typedef struct compteur compteur;
struct	compteur
{
  int	continuer;
  int	j;
  int	i;
  int	check;
  int	select;
};
  
#endif

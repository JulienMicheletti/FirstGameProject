#ifndef	DEF_CONSTANTES
#define	DEF_CONSTANTES

#define TAILLE_BLOC		32
#define	NB_BLOCS_LARGEUR	24
#define NB_BLOCS_HAUTEUR	24
#define WIDHT			TAILLE_BLOC * NB_BLOCS_LARGEUR
#define LENGTH			TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum{HAUT, BAS, GAUCHE, DROITE, HAUTP, BASP, DROITEP, GAUCHEP};
enum{VIDE, MUR, HEROS, FIN, BLOC, PIEGE, LEVIER, CASSE, PIOCHE, PIEGEON, LEVIERON};

typedef struct sprite sprite;
struct	sprite
{
  SDL_Surface	*mur;
  SDL_Surface	*herosActuel;
  SDL_Surface	*heros[8];
  SDL_Surface	*fin;
  SDL_Surface	*finouvert;
  SDL_Surface	*bloc;
  SDL_Surface	*vide;
  SDL_Surface	*piege;
  SDL_Surface	*piegeON;
  SDL_Surface	*levier;
  SDL_Surface	*levierON;
  SDL_Surface	*pioche;
  SDL_Surface	*casse;
};

typedef struct compteur compteur;
struct	compteur
{
  int	continuer;
  int	j;
  int	i;
  int	check;
  int	select;
  int	checklevier;
  int	checkpioche;
};
  
#endif

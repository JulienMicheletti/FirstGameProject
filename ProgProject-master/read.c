#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "game.h"
#include "IA.h"

FILE*	selectNiveau(FILE* fichier, int select)
{
  if (select == 0)
	{
    fichier = fopen("niveaux/niveau.lvl", "r");
		initEnemies("niveaux/LvL01_Enemies.lvl");
	}
  else if (select == 1)
    fichier = fopen("niveaux/niveau2.lvl", "r");
  return (fichier);
}

int	chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int select)
{
  char	*chaine;
  char	*stock;
  int	taille = 0;
  FILE*	fichier = NULL;
  int	i = 0, j = 0, len;

  chaine = (char*)malloc((10000) * sizeof(char));
  stock = (char*)malloc((10000) * sizeof(char));
  fichier = selectNiveau(fichier, select);
  if (fichier == NULL)
    exit(1);
  while (fgets(chaine, NB_BLOCS_LARGEUR, fichier) != NULL)
    {
      len = strlen(chaine);
      chaine[(len - 1)] = '\0';
      strcat(stock, chaine);
    }
  for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
      for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
	{
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '0')
	    niveau[j][i] = 0;
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '1')
	    niveau[j][i] = 1;
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '2')
	    niveau[j][i] = 2;
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '3')
	    niveau[j][i] = 3;
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '4')
	    niveau[j][i] = 4;
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '5')
	    niveau[j][i] = 5;
	  if (stock[(i * NB_BLOCS_LARGEUR) + j] == '6')
	    niveau[j][i] = 6;
	  
	}
    }
  fclose(fichier);
  return 1;
}

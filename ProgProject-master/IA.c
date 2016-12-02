// Include
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"

#include "IA.h"

//!\ Ce qui était supposé être un lacier est desormais un fantome /!\

// Fonctions
//TODO : fonction deplacer
//TODO : fonction attaquer

int monsterHere(int x, int y)
{
	int i;
	for (i=0; i<=MAXMONSTERS-1; i++)
	{
		if (listEnemies[i].posX == x && listEnemies[i].posY == y && listEnemies[i].type != EnemyNotInit)
		{return (i);}
	}
	return (MAXMONSTERS);
}

int canWalk(int carte[][NB_BLOCS_HAUTEUR], int x, int y)
{
	if (carte[x][y]==VIDE)
	{
		if (monsterHere(x, y) != MAXMONSTERS)
		{
			return (1);
		}
	}
	return(0);
}

// Cherche les ennemis sur la carte pour les initialiser
int initEnemies(char enemyFile[])
{
	
	FILE* fichier = open(enemyFile, 'r');
	int i;
	for (i = 0; i <= MAXMONSTERS-1; i++)
	{
		int a, x, y;
		fscanf(fichier, "%d %d %d", a, x, y);
			switch (a) 
			{
				case EnemyZombie :
					listEnemies[i] = (enemy) {.type = EnemyZombie, .posX = x, .posY = y, .health = EnemyZombieHealth, .strenght = EnemyZombieStrenght, .range = EnemyZombieRange, .score = EnemyZombieScore};
					//TODO afficher sprites
					break;
				case EnemyLance : 
					listEnemies[i] = (enemy) {.type = EnemyLance, .posX = x, .posY = y, .health = EnemyLanceHealth, .strenght = EnemyLanceStrenght, .range = EnemyLanceRange, .score = EnemyLanceScore};
					break;
				case EnemyMage : 
					listEnemies[i] = (enemy) {.type = EnemyMage, .posX = x, .posY = y, .health = EnemyMageHealth, .strenght = EnemyMageStrenght, .range = EnemyMageRange, .score = EnemyMageScore};
					break;
				default :
					listEnemies[i] = (enemy) {.type = EnemyNotInit, .posX = 0, .posY = 0, .health = EnemyNotInitHealth, .strenght = EnemyNotInitStrenght, .range = EnemyNotInitRange, .score = EnemyNotInitScore};
			}
			fclose(fichier);
	}
	return(0);
}

// On cherche des ennemis pour les activer. A lancer a chaque cycle
int initPathfinding(int carte[][NB_BLOCS_HAUTEUR])
{
	int i;
	for (i = 0; i <= MAXMONSTERS-1; i++)
	{
		if (listEnemies[i].type != EnemyNotInit)
		{
			startPathfinding (carte[][NB_BLOCS_HAUTEUR], listEnemies[i].posX, listEnemies[i].posY, listEnemies[i].range, listEnemies[i].type);
		}
	}
}

// Verifie si le joueur est a portée de l'ennemi
char isInRange (int carte[][NB_BLOCS_HAUTEUR], int posX, int posY, int range)
{
	int i;
	for (i=0; i<=range; i++)
	{
		int canBeN = 1;
		int canBeS = 1;
		int canBeE = 1;
		int canBeO = 1;
		
		// sizeof(carte)/sizeof(carte)[0] : nombre de lignes
		// sizeof(carte)[0]/sizeof(carte)[0][0] : nombre de colones
		
		if (posX-i>=0 && canBeN == 1) // Verification depassement de tableau et si peut être au nord
		{
			if (canWalk(carte, posX-i, posY) == 0 )
			{
				canBeN = 0; // Mur, ne peut pas être au nord
			}
			else if (posPlayer.x == posX-i && posPlayer.y == posY) // Si joueur
			{
				return ('N'); // Joueur trouvé
			}
		}
		if (posX+i<=(sizeof(carte)/sizeof(carte)[0] -1) && canBeS == 1)
		{
			if (canWalk(carte, posX+i, posY) == 0 )
			{
				canBeS = 0;
			}
			else if (posPlayer.x == posX+i && posPlayer.y == posY)
			{
				return ('S');
			}
		}
		if (posY+i<=((sizeof(carte)[0]/sizeof(carte)[0][0])-1) && canBeE == 1)
		{
			if (canWalk(carte, posX, posY+i) == 1 )
			{
				canBeE = 0;
			}
			else if (posPlayer.x == posX && posPlayer.y == posY+i)
			{
				return ('E');
			}
		}
		if (posY-i>=0 && canBeO == 1)
		{
			if (canWalk(carte, posX, posY-i) == 0 )
			{
				canBeO = 0;
			}
			else if (posPlayer.x == posX && posPlayer.y == posY-i)
			{
				return ('O');
			}
		}
	}
	return ('A'); // Aucune direction (joueur non trouvé)
}

//TODO deplacer les spritesavec les nouvelles cordonnées.
int deplaceEnemy(int posX, int posY, char dir)
{
	int i;
	// Cherche monstre avec les cordonnées indiquées en parametre
	for(i = 0; i <= MAXMONSTERS-1; i++)
	{
		if(listEnemies.posX == posX && listEnemies.posY == posY){break;}
	}
	
	switch (dir) 
	{
		case 'N' :
			listEnemies[i].posX = posX-1
			break;
			
		case 'S' :
			listEnemies[i].posX = posX+1
			break;
			
		case 'E' :
			listEnemies[i].posY = posY+1
			break;
			
		case 'O' :
			listEnemies[i].posY = posY-1
			break;
			
		default :
			break;
	}
	return(0);
}

int startPathfinding (int carte[][NB_BLOCS_HAUTEUR], int posX, int posY, int range, int type)
{
	
	int resN, resS, resE, resO;
	
	char dir = isInRange(carte, posX, posY, range);
	
	if (dir != 'A') // Si déjà à portée
	{
		initAtt(carte, type, range, dir, posX, posY);
		return (0);
	}
	
	// Chercher joueur
	resN = pathfinding(carte, posX-1, posY, constTTL, 0, 'N', 'S', range);
	resS = pathfinding(carte, posX+1, posY, constTTL, 0, 'S', 'N', range);
	resE = pathfinding(carte, posX, posY+1, constTTL, 0, 'O', 'E', range);
	resO = pathfinding(carte, posX, posY-1, constTTL, 0, 'E', 'O', range);
	
	
	if (resS + resN + resE + resO == 0) // Si coincé ou trop loin
	{
		return (0);
	}
	
	// On vérifie la direction du chemin le plus court
	if (resS<=resN && resS<=resE && resS<=resO)
	{
		deplaceEnemy(posX, posY, 'N');
		return (0);
	}
	else if (resN<=resS && resN<=resE && resN<=resO)
	{
		deplaceEnemy(posX, posY, 'S');
		return (0);
	}
	else if (resE<=resS && resE<=resN && resE<=resO)
	{
		deplaceEnemy(posX, posY, 'E');
		return (0);
	}
	else
	{
		deplaceEnemy(posX, posY, 'O');
		return (0);
	}
}

int pathfinding (int carte[][NB_BLOCS_HAUTEUR], int posX, int posY, int TTL, int round, char dir, char lastDir, int range)
{

	int resA, resB, resC;
	
	if (dir == lastDir)	// Tourne dans la même direction
	{
		round++;
		if (round >= 4){return (0);} // Tourne en rond
	}
	else {round == 0;}
	
	// Joueur trouvé
	if (range >= 3 && isInRange(carte, posX, posY, range) != 'A'){return (TTL);} // Ameloire l'IA distance
	if (range <= 3 && posPlayer.x == posX && posPlayer.y == posY){return (TTL);} // Plus rapide et tout aussi adapté pour les ennemeis CaC
	
	if (canWalk(carte, posX, posY) == 0){return (0);}
	
	if (TTL == 0) {return (0);} // Trop loin
	
	// "Deplacement" de la vérification
	
	switch (dir) 	// On ne revient pas en arriere
	{
		case 'N' :
			resA = pathfinding (carte, posX-1, posY, TTL-1, round, 'N', dir, range);
			resB = pathfinding (carte, posX, posY+1, TTL-1, round, 'E', dir, range);
			resC = pathfinding (carte, posX, posY-1, TTL-1, round, 'O', dir, range);
			break;
			
		case 'S' :
			resA = pathfinding (carte, posX+1, posY, TTL-1, round, 'S', dir, range);
			resB = pathfinding (carte, posX, posY+1, TTL-1, round, 'E', dir, range);
			resC = pathfinding (carte, posX, posY-1, TTL-1, round, 'O', dir, range);
			break;
			
		case 'E' :
			resA = pathfinding (carte, posX-1, posY, TTL-1, round, 'N', dir, range);
			resB = pathfinding (carte, posX+1, posY, TTL-1, round, 'S', dir, range);
			resC = pathfinding (carte, posX, posY+1, TTL-1, round, 'E', dir, range);
			break;
			
		case 'O' :
			resA = pathfinding (carte, posX-1, posY, TTL-1, round, 'N', dir, range);
			resB = pathfinding (carte, posX+1, posY, TTL-1, round, 'S', dir, range);
			resC = pathfinding (carte, posX, posY-1, TTL-1, round, 'O', dir, range);
			break;
			
		default :
			return (0); // Erreur, innutile de continuer
	}	
	
	if (resA >= resB) // On retourne le resultat avec le plus grand TTL
	{
		if (resA >= resC) {return (resA);}
	}
	else if (resB >= resC) {return (resB);}
	else {return (resC);}
	
	
	return (0);
}

int initAtt (int carte[][NB_BLOCS_HAUTEUR], int type, int range, char dir, int posX, int posY)
{
	switch (type)
	{
		case EnemyZombie : 
			zombieAtt(dir, posX, posY);
			break;
		case EnemyLance :
			spearAtt(carte, dir, posX, posY);
			break;
		case EnemyMage :
			fireBall(carte, range, dir, posX, posY);
			break;
		default :
			return (0);
	}
	return (0);
}

int zombieAtt (char dir, int posX, int posY)
{
	switch (dir)
	{
		case 'N' :
			//TODO orienter l'ennemi vers le joueur
			if (posPlayer.x == posX-1 && posPlayer.y == posY)
			{
				//TODO ajouter un petit delais avant l'attaque
				//TODO infliger degat joueur
			}
			break;
		case 'S' :
			//TODO orienter l'ennemi vers le joueur

			if (posPlayer.x == posX+1 && posPlayer.y == posY)
			{
				//TODO ajouter un petit delais avant l'attaque
				//TODO infliger degat joueur
			}
			break;
		case 'E' :
			//TODO orienter l'ennemi vers le joueur

			if (posPlayer.x == posX && posPlayer.y == posY+1)
			{
				//TODO ajouter un petit delais avant l'attaque
				//TODO infliger degat joueur
			}
			break;
		case 'O' :
			//TODO orienter l'ennemi vers le joueur

			if (posPlayer.x == posX && posPlayer.y == posY-1)
			{
				//TODO ajouter un petit delais avant l'attaque
				//TODO infliger degat joueur
			}
			break;
		default :
			return (0);
	}
	return (0);
}

// sizeof(carte)/sizeof(carte)[0] : nombre de lignes
// sizeof(carte)[0]/sizeof(carte)[0][0] : nombre de colones

int spearAtt (int carte[][NB_BLOCS_HAUTEUR], char dir, int posX, int posY)
{
	switch(dir)
	{
		case 'N' :
			//TODO orienter l'ennemi vers le joueur
			if (posPlayer.x == posX-1 && posPlayer.y == posY)
			{
				//TODO infliger degat joueur
			}
			else if(posX-2 >= 0) // Verification debordement tableau
			{
				if (posPlayer.x == posX-2 && posPlayer.y == posY)
				{
					//TODO afficher ectoplasme entre joueur et fantome
					//TODO infliger degat joueur
				}
			}
			break;
			
		case 'S' :
			//TODO orienter l'ennemi vers le joueur

			if (posPlayer.x == posX+1 && posPlayer.y == posY)
			{
				//TODO infliger degat joueur
			}
			else if(posX+2 <= sizeof(carte)/sizeof(carte)[0] -1)
			{
				if (posPlayer.x == posX+2 && posPlayer.y == posY)
				{
					//TODO afficher ectoplasme entre joueur et fantome
					//TODO infliger degat joueur
				}
			}
			break;
			
		case 'E' :
			//TODO orienter l'ennemi vers le joueur

			if (posPlayer.x == posX && posPlayer.y == posY+1)
			{
				//TODO infliger degat joueur
			}
			else if(posY+2 <= sizeof(carte)[0]/sizeof(carte)[0][0] -1)
			{
				if (posPlayer.x == posX && posPlayer.y == posY+2)
				{
					//TODO afficher ectoplasme entre joueur et fantome
					//TODO infliger degat joueur
				}
			}
			break;
			
		case 'O' :
			//TODO orienter l'ennemi vers le joueur

			if (posPlayer.x == posX && posPlayer.y == posY-1)
			{
				//TODO infliger degat joueur
			}
			else if(posY-2 >= 0)
			{
				if (posPlayer.x == posX && posPlayer.y == posY-2)
				{
					//TODO afficher ectoplasme entre joueur et fantome
					//TODO infliger degat joueur
				}
			}
			break;
			
		default :
			return (0);
	}
	return (0);
}

int fireBall (int carte[][NB_BLOCS_HAUTEUR], int range, char dir, int posX, int posY)
{
	switch (dir)
	{
		case 'N' :
			//TODO faire apparaitre une boule de feu orientée vers le nord à posX-1, posY
			moveFireBall(carte, range, dir, posX, posY, -1, 0);
			break;
		case 'S' :
			//TODO faire apparaitre une boule de feu orientée vers le sud à posX+1, posY
			moveFireBall(carte, range, dir, posX, posY, 1, 0);
			break;
		case 'E' :
			//TODO faire apparaitre une boule de feu orientée vers l'est à posX, posY+1
			moveFireBall(carte, range, dir, posX, posY, 0, 1);
			break;
		case 'O' :
			//TODO faire apparaitre une boule de feu orientée vers l'ouest à posX, posY-1
			moveFireBall(carte, range, dir, posX, posY, 0, -1);
			break;
		default :
			return (0);
	}
	return (0);
}

// sizeof(carte)/sizeof(carte)[0] : nombre de lignes
// sizeof(carte)[0]/sizeof(carte)[0][0] : nombre de colones
int moveFireBall (int carte[][NB_BLOCS_HAUTEUR], int range, char dir, int posX, int posY, int modX, int modY)
{
	int i=0;
	for (i=0; (i<=range)
		&& (posX+i*modX >= 0) && (posY+i*modY >= 0)
		&& (posX+i*modX <= sizeof(carte)/sizeof(carte)[0] -1)
		&& (posY+i*modY <= sizeof(carte)[0]/sizeof(carte)[0][0] -1);
		i++)
	{
		//TODO : ajouter un timer pour éviter un déplacement d'une case/frame
		//TODO déplacer boule de feu
		
		if (canWalk(carte, posX+i*modX, posY+i*modY ) == 0 || (posPlayer.x == posX+i*modX && posPlayer.y == posY+i*modY))
		{
			//TODO detruire boule de feu
			if (posPlayer.x == posX+i*modX && posPlayer.y == posY+i*modY)
			{
				//TODO infliger degat joueur
			}
		}
	}
}

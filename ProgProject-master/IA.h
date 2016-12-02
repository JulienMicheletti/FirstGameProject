// Define

#define constTTL 					16

// Les valeurs ci-dessous ne seront peut être pas gardés ici à l'avenir
#define EnemyNotInitHealth			0
#define EnemyNotInitStrenght		0
#define EnemyNotInitRange				0
#define EnemyNotInitScore				0

#define EnemyZombieHealth				9
#define EnemyZombieStrenght			5
#define EnemyZombieRange				1
#define EnemyZombieScore				10

#define EnemyLanceHealth				7
#define EnemyLanceStrenght			3
#define EnemyLanceRange					2
#define EnemyLanceScore					15

#define EnemyMageHealth					7
#define EnemyMageStrenght				6
#define EnemyMageRange					5
#define EnemyMageScore					20

// Structures

typedef struct
{
	int type;
	int posX;
	int posY;
	int health;
	int strenght;
	int range;
	int score;
}enemy;

// Var
enemy listEnemies[MAXMONSTERS];

// Fonctions
//TODO : fonction deplacer
//TODO : fonction attaquer

// Verifie si un monstre est present sur une case donnée et renvoie sa position dans le tableau des monstres, renvouse MAXMONSTERS si aucun ennemi n'a été trouvé.
int monsterHere(int x, int y);

//Verifie si un monstre peut marcher sur une case.
int canWalk(int carte[][NB_BLOCS_HAUTEUR], int x, int y);

// Cherche les ennemis sur la carte pour les initialiser
int intitEnemies(char enemyFile[]);

// On cherche des ennemis pour les activer. A lancer a chaque cycle
int initPathfinding(int carte[][NB_BLOCS_HAUTEUR]);

// Verifie si le joueur est a portee de l'ennemi
char isInRange (int carte[][NB_BLOCS_HAUTEUR], int posX, int posY, int range);

int deplaceEnemy(int posX, int posY, char dir)

int startPathfinding (int carte[][NB_BLOCS_HAUTEUR], int posX, int posY, int range, int type);

// Recursif
int pathfinding (int carte[][NB_BLOCS_HAUTEUR], int posX, int posY, int TTL, int round, char dir, char lastDir, int range);

int initAtt (int carte[][NB_BLOCS_HAUTEUR], int type, int range, char dir, int posX, int posY);

int zombieAtt (char dir, int posX, int posY);

// Lancier remplacé par le fantôme
int spearAtt (int carte[][NB_BLOCS_HAUTEUR], char dir, int posX, int posY);

int fireBall (int carte[][NB_BLOCS_HAUTEUR], int range, char dir, int posX, int posY);

int moveFireBall (int carte[][NB_BLOCS_HAUTEUR], int range, char dir, int posX, int posY, int modX, int modY);

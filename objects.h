#include <time.h> 

struct Missile{
	int xDest;   //Where the missile is going
	int yDest; 
	double xStart; 
	double yStart; 
	double x; 
	double y; 
	double xVel; 
	double yVel; 
	int isAlive; 
};


struct Explosion{
	double r; 
	double x; 
	double y; 
	double maxR;  //Max radius the explosion will have 
	double minR; 
	double startR; 
	int isAlive; 
	double rVel; 
};

struct City{
	int health; 
	int isAlive; 
};

typedef struct City city; 
typedef struct Missile missile; 
typedef struct Explosion explosion; 




void shootMissile(missile * myMissile);
void updateMyMissiles(missile *myMissile, explosion * explosions);
void drawMyMissiles(missile *myMissile);
void startExplosion(int x, int y, explosion * explosions);
void updateExplosions(explosion * explosions);
void drawExplosions(explosion * explosions);
void updateEnemyMissiles(missile *enemyMissiles, explosion * explosions, time_t *timeSinceMissile); 
void drawEnemyMissiles(missile * enemyMissiles); 
int checkCollision(explosion exp, missile m);




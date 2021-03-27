#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "numbers.h"
#include <stdio.h>
#include "letters.h"
#include <limits.h>
#define WIDTH 600
#define HEIGHT 500

#ifndef M_PI
#define M_PI 3.1415
#endif

int numCities = 6;
int numEnemies = 15;
int numTowers = 3;
int numMissiles = 15;
int numExplosions = 20;
int initialAmmo = 4 + 3 + 2 + 1;

int keysShoot[] = {
    'a', 's', 'd'
};

struct Explosion
{
    double r; //The radius of the explosion
    double x; //The location of the explosion
    double y;
    double maxR; //Max radius the explosion will have
    double minR;
    double startR; //The starting radius of the explosion
    int isAlive;   //If the explosion is active
    double rVel;   //Rate at which the radius is changing
};

struct Missile
{
    int xDest; //Where the missile is going
    int yDest;
    double xStart; //Where the missile is coming from
    double yStart;
    double x; //The current location of the missile
    double y;
    double xVel; //The velocity of the missile
    double yVel;
    int isAlive; //If the missile is currently active
};

struct Missile_Node
{
    struct Missile *m;
};

struct City
{
    int x; //Location of the city
    int y;
    int isAlive; //If the city is active
};

struct Tower
{
    int x; //Location of the tower
    int y;
    int ammo;
    int isAlive; //If the tower is active
};

//Construct typedefs for each of the structures so that they are more easily called
typedef struct City city;
typedef struct Missile missile;
typedef struct Explosion explosion;
typedef struct Tower tower;

void drawCity(int x, int y);
void drawBackground(void);
void drawCities(city *cities);
void drawLand(void);
void mainMenu(void);
void initializeStructures(tower towers[], city cities[], missile enemyMissiles[], missile myMissiles[], explosion explosions[]);
void shootMissile(tower towers[], missile *myMissiles);
void updateMyMissiles(missile myMissiles[], explosion explosions[]);
void drawMyMissiles(missile myMissiles[]);
void startExplosion(missile *m, explosion explosions[]);
void updateExplosions(explosion explosions[]);
void drawExplosions(explosion explosions[]);
void drawCircle(int xpos, int ypos, float r);
void updateEnemyMissiles(missile *myMissile, tower towers[], city *cities, missile *enemyMissiles, explosion explosions[], time_t *timeSinceMissile, int *score, time_t difficulty);
void drawEnemyMissiles(missile *enemyMissiles);
void updateObjects(tower towers[], city *cities, missile *enemyMissiles, missile *myMissile, explosion explosions[], time_t *timeSinceMissile, int *score, time_t difficulty);
int checkGameOver(city *cities);
void drawMissileTower(int x, int y);
void drawTowers(tower towers[]);
void drawAmmo(tower towers[]);
void gameOver(int score);
void drawGameOver(int score);
void drawMainMenu(void);
void saveScore(int score);

//Main function for the game:
int main(void)
{
    gfx_open(WIDTH, HEIGHT, "MISSILE COMMAND");

    time_t timeSinceMissile = time(NULL); //Used to delay the firing of the enemy missiles
    time_t difficulty = time(NULL);       //Used to calculate speed of missiles

    mainMenu(); //Set up the main menu

    int gameLoop = 1; //Continue the game if this is true.
    int score = 0;    //will be used to calculate the user's score

    //Initialize structures

    tower towers[numTowers];
    city cities[numCities];
    missile enemyMissiles[numEnemies];
    missile myMissiles[numMissiles];
    explosion explosions[numExplosions];

    //Set up all of the structures:
    initializeStructures(towers, cities, enemyMissiles, myMissiles, explosions);

    //While this is running, the game works
    while (gameLoop)
    {
        if (gfx_event_waiting())
        {
            char c = gfx_wait();
            switch (c)
            {
            case 'q':
                gameLoop = 0;
                break;
            default:
                for (int i = 0; i < numTowers; i++) {
                    if (keysShoot[i] == c) {
                        shootMissile(&towers[i], myMissiles);
                        break;
                    }
                }
            }
        }
        drawBackground(); //Draw the background of the game
        updateObjects(towers, cities, enemyMissiles, myMissiles, explosions, &timeSinceMissile, &score, difficulty);
        draw_number(40, 40, 50, score);
        gfx_flush(); //Update the graphics
        usleep(10000);

        if (checkGameOver(cities))
        {
            gameLoop = 0;
        }
    }
    gameOver(score);
}

//Draws a city at a given location

void drawCity(int x, int y)
{
    gfx_color(0, 0, 255);
    int i;
    for (i = x; i < x + 30; i++)
    {                              //Draw a base that is 30 pixels wide, starting at x
        gfx_line(i, y, i, y + 10); //Base is 10 pixels high.
    }
    int j;
    for (j = x; j < x + 5; j++)
    {
        gfx_line(j, y, j, y - 10); //Draw chimney thing
    }
}

//Draws a missileTower at a given location
void drawMissileTower(int x, int y)
{
    gfx_color(0, 255, 0);
    int i;
    for (i = x; i < x + 20; i++)
    {                              //Draw a base that is 20 pixels wide, starting at x
        gfx_line(i, y, i, y + 10); //Base is 10 pixels high.
    }

    int j;
    for (j = x + 8; j < x + 12; j++)
    {
        gfx_line(j, y, j, y - 10);
    }
}

//Draws the array of towers
void drawTowers(tower towers[])
{
    int i, x;
    for (i = 0; i < numTowers; i++)
    {
        if (towers[i].isAlive)
        {
            drawMissileTower(towers[i].x, HEIGHT * 5 / 6);
        }
    }
}

//Draws the array of ammo under towers
void drawAmmo(tower towers[])
{
    int i, x;
    for (i = 0; i < numTowers; i++)
    {
        int x = towers[i].x;
        int y = HEIGHT * 5 / 6 + 20;
        int ammo = towers[i].ammo;
        gfx_color(0, 0, 0);
        draw_number(x, y, 15, ammo);
        if (ammo <= 0)
        {
            drawWord("none", x, y + 40, 12, 5);
        }
        else if (ammo <= 5)
        {
            drawWord("low", x, y + 40, 12, 8);
        }
    }
}

//Draws the background (essentially just the ground.)
void drawBackground(void)
{
    gfx_clear();
    gfx_color(255, 0, 0);
    drawLand();
}

//Draw the array of the cities given
void drawCities(city cities[])
{
    int i;
    for (i = 0; i < numCities; i++)
    {
        if (cities[i].isAlive)
        {
            drawCity(cities[i].x, HEIGHT * 5 / 6);
        }
    }
}

//Draws a rectangle at the bottom of the screen
void drawLand(void)
{
    int i;
    for (i = HEIGHT * 5 / 6; i < HEIGHT; i++)
    {
        gfx_line(0, i, WIDTH - 1, i);
    }
}

void saveScore(int score)
{
    FILE *f;
    f = fopen("scores.txt", "a");
    if (f == NULL)
        printf("Unable to open file\n");
    else
    {
        puts("Enter your initials");
        char word[100];
        scanf("%s", word);
        fprintf(f, "%s -- %d\n", word, score);
        fclose(f);
    }
}

void drawMainMenu(void)
{
    gfx_clear();
    drawWord("missile", 100, 100, 50, 20);
    gfx_color(255, 0, 0);
    drawWord("command", 120, 200, 50, 20);
    gfx_color(255, 255, 255);
    drawWord("press", 100, 400, 50, 20);
    drawS(280, 400, 50, 20);
    gfx_flush();
}

// Display a Game Over screen with the score
void gameOver(int score)
{
    drawGameOver(score);
    /*char c; 
    while(c != 'y' && c!='n'){
	c= gfx_wait();
    	if(c == 'y'){
		saveScore(score);
	}
    }*/
    gfx_wait();
}

void drawGameOver(int score)
{
    gfx_clear();
    gfx_color(255, 0, 0);
    drawWord("game", 200, 120, 100, 40);
    drawWord("over", 200, 240, 100, 40);
    gfx_color(0, 255, 0);
    drawWord("your score", 50, 340, 50, 20);
    draw_number(400, 290, 50, score);
    //gfx_color(255,255,255);
    //drawWord("save score? [y/n]",50,440,50,20);
}

void mainMenu(void)
{
    int main = 1;

    while (main)
    {
        drawMainMenu();
        char c = gfx_wait();

        switch (c)
        {
        case 'q':
            exit(0);
            break;
        case 's':
            main = 0;
            gfx_xpos();
            gfx_ypos();
            break;
        }
    }
}

//Initializes all of the arrays for the cities and missiles
void initializeStructures(tower towers[], city *cities, missile *enemyMissiles, missile *myMissiles, explosion explosions[])
{
    size_t i;
    for (i = 0; i < numCities / 2; i++)
    {
        cities[i].x = WIDTH / 10 * (i + 2);
        cities[i].y = HEIGHT * 5 / 6;
        cities[i].isAlive = 1;
    }

    for (i = numCities / 2; i < numCities; i++)
    {
        cities[i].x = WIDTH / 10 * (i + 3);
        cities[i].y = HEIGHT * 5 / 6;
        cities[i].isAlive = 1;
    }

    for (i = 0; i < numEnemies; i++)
    {
        enemyMissiles[i].x = -100;
        enemyMissiles[i].y = -100;
        enemyMissiles[i].xVel = 0;
        enemyMissiles[i].yVel = 0;
        enemyMissiles[i].isAlive = 0;
    }

    for (i = 0; i < numTowers; i++)
    {
        towers[i].isAlive = 1;
        towers[i].x = WIDTH / 10 + ((i * 4) * WIDTH / 10);
        towers[i].y = HEIGHT * 5 / 6;
        towers[i].ammo = initialAmmo;
    }
    
    for (i = 0; i < numMissiles; i++)
    {
        myMissiles[i].x = -100;
        myMissiles[i].y = -100;
        myMissiles[i].xDest = 0;
        myMissiles[i].yDest = 0;
        myMissiles[i].xVel = 0;
        myMissiles[i].yVel = 0;
        myMissiles[i].isAlive = 0;
    }

    for (i = 0; i < numExplosions; i++)
    {
        explosions[i].maxR = 50;
        explosions[i].r = 25;
        explosions[i].isAlive = 0;
        explosions[i].rVel = 1;
    }
}

void drawCircle(int xpos, int ypos, float r)
{
    gfx_color(255, 174, 66);
    float i = 0;
    float angle = (M_PI * 2) / 100;
    float x1, x2, y1, y2;

    for (i = 0; i < 2 * M_PI; i += angle)
    {
        x1 = r * cos(i) + xpos;
        y1 = r * -sin(i) + ypos;
        x2 = r * cos(i + angle) + xpos;
        y2 = r * -sin(i + angle) + ypos;
        gfx_line(x1, y1, x2, y2);
    }
}

void drawCross(int xpos, int ypos, float r)
{
    gfx_line(xpos - r, ypos - r, xpos + r, ypos + r);
    gfx_line(xpos + r, ypos - r, xpos - r, ypos + r);
}

//Shoot a missile from the user
void shootMissile(tower *tower, missile myMissiles[])
{
    if (!tower->isAlive || tower->ammo <= 0)
    {
        return;
    }
    for (int i = 0; i < numMissiles; i++) {
        missile *myMissile = &myMissiles[i];
        if (myMissile->isAlive)
        {
            continue;
        }
        tower->ammo--;

        double xStart = tower->x + 5;
        double yStart = 5 * HEIGHT / 6;
        myMissile->xDest = gfx_xpos();
        myMissile->yDest = gfx_ypos();
        myMissile->isAlive = 1;
        myMissile->y = yStart;
        myMissile->xStart = xStart;
        myMissile->x = xStart;
        myMissile->yStart = yStart;
        double x = myMissile->xDest - xStart;
        double y = yStart - myMissile->yDest;
        double missileSpeed = 2.0;
        myMissile->yVel = (-y / sqrt(pow(y, 2) + pow(x, 2))) * missileSpeed;
        myMissile->xVel = (x / sqrt(pow(y, 2) + pow(x, 2))) * missileSpeed;
        return;
    }
    // out of missiles memory
}

//Update the position of the user's missile
void updateMyMissiles(missile myMissiles[], explosion *explosions)
{
    for (int i = 0; i < numMissiles; i++) {
        missile *myMissile = &myMissiles[i];
        if (myMissile->isAlive == 1)
        {
            myMissile->x += myMissile->xVel;
            myMissile->y += myMissile->yVel;

            if (myMissile->y <= myMissile->yDest)
            { //If the missile is at/past the point that the user clicked, the missile explodes
                myMissile->isAlive = 0;
                startExplosion(myMissile, explosions);
            }
        }
    }
}

//Draw the player's missile
void drawMyMissiles(missile *myMissiles)
{
    for (int i = 0; i < numMissiles; i++) {
        missile *myMissile = &myMissiles[i];
        if (myMissile->isAlive == 1)
        {
            gfx_color(0, 0, 255);
            gfx_line(myMissile->xStart, myMissile->yStart, myMissile->x, myMissile->y);
            gfx_color(0, 255, 0);
            drawCross(myMissile->xDest, myMissile->yDest, 5);
        }
    }
}

//Shoots a missile after a certain amount of time.
void startEnemyMissile(tower towers[], city cities[], missile enemyMissiles[], time_t *timeSinceMissile, time_t difficulty)
{
    int i, t, destIsValid = 0, destIsTower = 0;
    for (i = 0; i < numEnemies; i++)
    {
        if (enemyMissiles[i].isAlive == 0)
        {
            double speed = 30; //difftime(time(NULL), difficulty);
            double diff = difftime(time(NULL), *timeSinceMissile);
            if (diff >= 1)
            { //Enough time has passed that it is good to shoot another missile:

                *timeSinceMissile = time(NULL); //Reset the timer
                enemyMissiles[i].isAlive = 1;   //Set the missile to be active
                enemyMissiles[i].yStart = 0;
                enemyMissiles[i].xStart = rand() % 600;
                enemyMissiles[i].yDest = HEIGHT * 5 / 6;

                while (!destIsValid)
                {
                    destIsTower = 0;
                    t = rand() % (numCities + numTowers);

                    if (t >= numCities) {
                        destIsTower = 1;
                        t -= numCities;
                    }
                    
                    if (destIsTower)
                    {
                        if (towers[t].isAlive)
                        {
                            destIsValid = 1;
                            enemyMissiles[i].xDest = towers[t].x + 5;
                        }
                    }
                    else
                    {
                        if (cities[t].isAlive)
                        {
                            destIsValid = 1;
                            enemyMissiles[i].xDest = cities[t].x + 5;
                        }
                    }
                }

                enemyMissiles[i].y = enemyMissiles[i].yStart;
                enemyMissiles[i].x = enemyMissiles[i].xStart;
                double x = enemyMissiles[i].xDest - enemyMissiles[i].xStart;
                double y = enemyMissiles[i].yStart - enemyMissiles[i].yDest;
                enemyMissiles[i].yVel = speed / 100 * (-y / sqrt(pow(y, 2) + pow(x, 2)));
                enemyMissiles[i].xVel = speed / 100 * (x / sqrt(pow(y, 2) + pow(x, 2)));
            }
        }
    }
}

//Updates each enemy missile's position and status
void updateEnemyMissiles(missile myMissiles[], tower towers[], city *cities, missile *enemyMissiles, explosion explosions[], time_t *timeSinceMissile, int *score, time_t difficulty)
{

    int i, t = 0, isTower = 0;
    for (i = 0; i < numEnemies; i++)
    {
        missile *missile = &enemyMissiles[i];
        if (enemyMissiles[i].isAlive == 1)
        {
            enemyMissiles[i].x += enemyMissiles[i].xVel;
            enemyMissiles[i].y += enemyMissiles[i].yVel;

            if (enemyMissiles[i].x >= WIDTH || enemyMissiles[i].x <= 0)
            {
                enemyMissiles[i].isAlive = 0;
            }
            else
            {
                checkGroundCollision(missile, towers, cities, explosions, score);
                checkExplosionsCollision(missile, explosions, score);
            }
        }
        else
        {

            enemyMissiles[i].x = 0;
            enemyMissiles[i].y = 0;
        }
    }
}

//If the enemy missile is alive, draw it as a blue line.
void drawEnemyMissiles(missile *enemyMissiles)
{
    int i;
    for (i = 0; i < numEnemies; i++)
    {
        if (enemyMissiles[i].isAlive == 1)
        {
            gfx_color(255, 50, 50);
            gfx_line(enemyMissiles[i].xStart, enemyMissiles[i].yStart, enemyMissiles[i].x, enemyMissiles[i].y);
            gfx_color(255, 255, 255);
            gfx_point(enemyMissiles[i].x, enemyMissiles[i].y);
        }
    }
}

//Begin an explosion at the specified point
void startExplosion(missile *m, explosion explosions[])
{
    for (int i = 0; i < numExplosions; i++) {
        explosion *exp = &explosions[i];
        if (exp->isAlive) {
            continue;
        }
        exp->x = m->x;
        exp->y = m->y;
        exp->rVel = 1;
        exp->isAlive = 1;
        exp->r = 25;
        return;
    }
}

//If the explosion is active (isAlive == 1), alter its radius by the value rVel.
void updateExplosions(explosion explosions[])
{
    for (int i = 0; i < numExplosions; i++)
    {
        explosion *exp = &explosions[i];
        if (exp->isAlive)
        {
            exp->r += exp->rVel;

            if (exp->r >= exp->maxR)
            {
                exp->rVel = -1 * abs(exp->rVel);
            }
            else if (exp->r <= 1)
            {
                exp->isAlive = 0;
            }
        }
    }
}

//Draw the explosions that are active.
void drawExplosions(explosion explosions[])
{
    for (int i = 0; i < numEnemies; i++)
    {
        explosion *exp = &explosions[i];
        if (exp->isAlive)
        {
            drawCircle(exp->x, exp->y, exp->r);
        }
    }
}

int checkGroundCollision(missile *m, tower towers[], city cities[], explosion explosions[], int *score)
{
    //Checks for collisions with cities
    int j;
    for (j = 0; j < numCities; j++)
    {
        if (m->x >= cities[j].x - 10 && m->y >= cities[j].y && m->x <= cities[j].x + 42)
        {
            cities[j].isAlive = 0;
            m->isAlive = 0;
            startExplosion(m, explosions);
            return 1;
        }
    }

    //Checks for collisions with missile towers
    for (j = 0; j < numTowers; j++)
    {
        if (m->x > towers[j].x - 2 && m->x < towers[j].x + 30 && m->y >= towers[j].y)
        {
            towers[j].isAlive = 0;
            m->isAlive = 0;
            startExplosion(m, explosions);
            return 1;
        }
    }
    return 0;
}

int checkExplosionCollision(missile *m, explosion *exp, explosion explosions[], int *score)
{
    if (exp->isAlive == 0 || m->isAlive == 0) {
        return 0;
    }
    float d = pow(pow(m->x - exp->x, 2) + pow(m->y - exp->y, 2), .5);
    if (d <= exp->r)
    {
        startExplosion(m, explosions);
        *score = *score + 10;
        m->isAlive = 0;
        return 1;
    }
    return 0;
}

int checkExplosionsCollision(missile *m, explosion explosions[], int *score)
{
    for (int i = 0; i < numEnemies; i++)
    {
        explosion *exp = &explosions[i];
        if (checkExplosionCollision(m, exp, explosions, score) == 1) {
            return 1;
        }
    }
    return 0;
}

//Updates all of the objects on the screen
void updateObjects(tower towers[], city *cities, missile *enemyMissiles, missile *myMissiles, explosion *explosions, time_t *timeSinceMissile, int *score, time_t difficulty)
{
    startEnemyMissile(towers, cities, enemyMissiles, timeSinceMissile, difficulty);
    updateEnemyMissiles(myMissiles, towers, cities, enemyMissiles, explosions, timeSinceMissile, score, difficulty);
    updateExplosions(explosions);
    updateMyMissiles(myMissiles, explosions);

    drawTowers(towers);
    drawAmmo(towers);
    drawCities(cities);
    drawExplosions(explosions);
    drawEnemyMissiles(enemyMissiles);
    drawMyMissiles(myMissiles);
}

//Checks if the game is over (if all cities have been destroyed
int checkGameOver(city *cities)
{
    int i;
    for (i = 0; i < numCities; i++)
    {
        if (cities[i].isAlive)
        {
            return 0;
        }
    }
    return 1;
}

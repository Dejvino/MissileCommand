#include "objects.h"
#include <time.h> 


void shootMissile(missile * myMissile){
	
	if(myMissile->isAlive == 0){

			
		myMissile->isAlive = 1; 	
		myMissile->xDest = gfx_xpos(); 
		myMissile->yDest = gfx_ypos();
		double xStart,yStart = 5*HEIGHT/6;  
		
		if(myMissile->xDest >= 2*WIDTH/3){
			xStart = 5*WIDTH/6; 
		}else if (myMissile->xDest <= WIDTH/3){
			xStart = WIDTH/6;
		}else{
			xStart = WIDTH/2; 
		}
		myMissile->y = yStart;    myMissile->xStart =xStart;
		myMissile->x = xStart;    myMissile->yStart = yStart; 

		double x = myMissile->xDest - xStart; 
		double y = yStart -myMissile->yDest; 
		
		myMissile->yVel = (-y/sqrt(pow(y,2)+pow(x,2)))*4; 
		myMissile->xVel = (x/sqrt(pow(y,2)+pow(x,2)))*4;
		return; 
	}
	
	
}



void updateMyMissiles(missile *myMissile, explosion * explosions){
	if(myMissile->isAlive==1){
			if(myMissile->y <= myMissile->yDest){
				myMissile->isAlive = 0;
				startExplosion(myMissile->x, myMissile->y, explosions); 
			}
		
			myMissile->x += myMissile->xVel; 
			myMissile->y += myMissile->yVel; 	
	}
}


void drawMyMissiles(missile *myMissile){
	if(myMissile->isAlive == 1){	
		gfx_color(0,0,255); 
		gfx_line(myMissile->xStart,myMissile->yStart,myMissile->x,myMissile->y); 
	}
}


void startExplosion(int x, int y, explosion * explosions){
	int i; 
	for(i=0;i<3;i++){
		if(explosions[i].isAlive == 0){
			explosions[i].x = x; 
			explosions[i].y = y; 
			explosions[i].rVel = 1; 
			explosions[i].isAlive = 1; 
			return; 
		}
	}
	
	
}


void updateEnemyMissiles(missile *enemyMissiles, explosion* explosions, time_t *timeSinceMissile){
	int i; 
	for(i=0; i<15;i++){
		if(enemyMissiles[i].isAlive == 0){
			double diff = difftime(time(NULL),*timeSinceMissile);
			if(diff>=1){
				*timeSinceMissile = time(NULL); 
				enemyMissiles[i].isAlive = 1; 
				enemyMissiles[i].yStart = 0; 
				enemyMissiles[i].xStart = rand()% (int) WIDTH; 
				enemyMissiles[i].xDest = rand()% (int) WIDTH; 
				enemyMissiles[i].yDest = HEIGHT*5/6;
				enemyMissiles[i].y = enemyMissiles[i].yStart; 
				enemyMissiles[i].x = enemyMissiles[i].xStart; 


				double x = enemyMissiles[i].xDest - enemyMissiles[i].xStart; 
				double y = enemyMissiles[i].yStart -enemyMissiles[i].yDest; 
			
				
				

				enemyMissiles[i].yVel =  (-y/sqrt(pow(y,2)+pow(x,2))); 
				enemyMissiles[i].xVel =  (x/sqrt(pow(y,2)+pow(x,2)));
				return;
			 }
		}
		else if(enemyMissiles[i].isAlive == 1){
			enemyMissiles[i].x+=enemyMissiles[i].xVel; 
			enemyMissiles[i].y+=enemyMissiles[i].yVel; 
			if(enemyMissiles[i].x >= WIDTH || enemyMissiles[i].y >=HEIGHT*5/6 || enemyMissiles[i].x <= 0){
				enemyMissiles[i].isAlive = 0; 			
			}
			else{
				int j; 
				for(j=0;j<3;j++){
					if(checkCollision(explosions[j],enemyMissiles[i])){
						enemyMissiles[i].isAlive = 0; 
					}
				}
			}
			
		}
	}
} 
void drawEnemyMissiles(missile * enemyMissiles){
	int i; 
	for(i=0; i<15;i++){
		if(enemyMissiles[i].isAlive == 1){
			printf("%f         %f\n",enemyMissiles[i].x,enemyMissiles[i].y); 
			gfx_line(enemyMissiles[i].xStart,enemyMissiles[i].yStart,enemyMissiles[i].x,enemyMissiles[i].y); 
		}
	}
}

void updateExplosions(explosion * explosions){
	int i; 
	for(i=0;i<3;i++){
		if(explosions[i].isAlive == 1){
			explosions[i].r += explosions[i].rVel;
			if(explosions[i].r >= explosions[i].maxR){
				explosions[i].rVel*=-1; 
			}
			else if(explosions[i].r <= explosions[i].minR){
				explosions[i].isAlive = 0; 
			}	
		}
	}
}
void drawExplosions(explosion * explosions){
	int i; 
	for(i=0;i<3;i++){
		if(explosions[i].isAlive == 1){
			drawCircle(explosions[i].x, explosions[i].y,explosions[i].r); 
		}
	}
}
int checkCollision(explosion exp, missile m){
	float i; 
	for(i=0;i<2*M_PI;i+=0.01){
		int x1 = exp.r * cos(i) + exp.x; 
		int y1 = exp.r * -sin(i) + exp.y;
		if((int)m.x == x1 && (int)m.y >= y1){
			return 1; 
		}
		
	}
	return 0; 

}



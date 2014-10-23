
//John F. Lake, Jr. 
//CSE 20211 Final Project 
//Car Game 
//game.c 


#include "gfx.h" 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 

#define WIDTH 500
#define HEIGHT 600


struct car{
       int xPos;
       int yPos;
       int xVel;
       int yVel;
       int isAlive;
       int Orientation;
};

struct bullet{
       int xPos;
       int yPos;
       int xVel;
       int yVel;
       int isAlive;
       int Orientation;
       int isShot;

};

void drawGrass(void);
void mainMenu(void);
void drawMainMenu(void);

//Main function for the game: 
int main(void){
	
	  struct car cars[10]; 
	  struct bullet bullets[10]; 
	  struct car myCar; 
	  struct bullet myBullet; 

	  //initializeVariables(cars,bullets, &myCar, &myBullet); 
          gfx_open(WIDTH,HEIGHT,"GAMENAME");
	  mainMenu(); 
	  gfx_clear(); 
	  drawGrass();  
          int stillGoing = 1; 
          while(stillGoing){
		if(gfx_event_waiting()){
			char c = gfx_wait(); 
			switch(c){
				case 'q': 
					stillGoing = 0; 
					break; 

			}
		}
          }
}


void drawGrass(void){
     gfx_color(0,255,0); 
     double i; 
     for(i=0;i<WIDTH/6;i++){
          gfx_line(i,0,i,HEIGHT-1);
     }
     for(i=WIDTH*5/6;i<WIDTH-1;i++){
          gfx_line(i,0,i,HEIGHT-1);
     }
}
void mainMenu(void){
	int mainMenu = 1; 
	while(mainMenu){
		drawMainMenu(); 
		
			char c= gfx_wait(); 
			switch(c){
				case 'q':
					exit(0); 
					break; 	
				case 's':
					mainMenu = 0;
					break; 

			} 
		
	}
}

void drawMainMenu(void){
	gfx_line(50,50,50,100); 
	gfx_line(50,64,64,64); 
	gfx_line(64,50,64,100); //H
	
	gfx_line(68,64,80,64); 
	gfx_line(68,64,68,80); 
	gfx_line(68,80,80,80); 
	gfx_line(80,64,80,80); //O

	gfx_line(84,80,84,60);
	gfx_line(78,60,90,60); //T

	gfx_line(50,130,50,180); 
	gfx_line(50,130,75,130); 
	gfx_line(50,155,75,155); 
	gfx_line(75,130,75,155); //P

	gfx_line(80,180,80,155); 
	gfx_line(80,180,105,180); 
	gfx_line(105,180,105,155); //U
	
	gfx_line(110,180,110,155); 
	gfx_line(110,155,120,155); //R
	
	gfx_line(125,180,140,180); 
	gfx_line(140,180,140,170); 
	gfx_line(140,170,125,170); 
	gfx_line(125,170,125,160); 
	gfx_line(125,160,140,160); //S

	gfx_line(145,180,145,155); 
	gfx_line(145,180,170,180); 
	gfx_line(170,180,170,155); //U

	gfx_line(175,180,175,155); 
	gfx_point(175,150); //I

	gfx_line(180,180,180,140);
	gfx_line(160,140,190,140); //T
	

}


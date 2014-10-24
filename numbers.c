#include <stdio.h>
#include "gfx.h"
#include <math.h>


void draw_zero(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y);
    gfx_line(x+width/3,y+height/5,x+width*2/3,y+height/5);
    gfx_line(x+width*2/3,y+height/5,x+width*2/3,y+height*4/5);
    gfx_line(x+width*2/3,y+height*4/5,x+width/3,y+height*4/5);
    gfx_line(x+width/3,y+height*4/5,x+width/3,y+height/5);
}

void draw_one(int x, int y, int height){
    int width = height/4;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y);
    
}

void draw_two(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height*3/5);
    gfx_line(x+width,y+height*3/5,x+width/3,y+height*3/5);
    gfx_line(x+width/3,y+height*3/5,x+width/3,y+height*4/5);
    gfx_line(x+width/3,y+height*4/5,x+width,y+height*4/5);
    gfx_line(x+width,y+height*4/5,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y+height*2/5);
    gfx_line(x,y+height*2/5,x+width*2/3,y+height*2/5);
    gfx_line(x+width*2/3,y+height*2/5,x+width*2/3,y+height/5);
    gfx_line(x+width*2/3,y+height/5,x,y+height/5);
    gfx_line(x,y+height/5,x,y);
    
}

void draw_three(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y+height*4/5);
    gfx_line(x,y+height*4/5,x+width*2/3,y+height*4/5);
    gfx_line(x+width*2/3,y+height*4/5,x+width*2/3,y+height*3/5);
    gfx_line(x+width*2/3,y+height*3/5,x,y+height*3/5);
    gfx_line(x,y+height*3/5,x,y+height*2/5);
    gfx_line(x,y+height*2/5,x+width*2/3,y+height*2/5);
    gfx_line(x+width*2/3,y+height*2/5,x+width*2/3,y+height/5);
    gfx_line(x+width*2/3,y+height/5,x,y+height/5);
    gfx_line(x,y+height/5,x,y);
    
}

void draw_four(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width/3,y);
    gfx_line(x+width/3,y,x+width/3,y+height*2/5);
    gfx_line(x+width/3,y+height*2/5,x+width*2/3,y+height*2/5);
    gfx_line(x+width*2/3,y+height*2/5,x+width*2/3,y);
    gfx_line(x+width*2/3,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x+width*2/3,y+height);
    gfx_line(x+width*2/3,y+height,x+width*2/3,y+height*3/5);
    gfx_line(x+width*2/3,y+height*3/5,x,y+height*3/5);
    gfx_line(x,y+height*3/5,x,y);
    
}

void draw_five(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height/5);
    gfx_line(x+width,y+height/5,x+width/3,y+height/5);
    gfx_line(x+width/3,y+height/5,x+width/3,y+height*2/5);
    gfx_line(x+width/3,y+height*2/5,x+width,y+height*2/5);
    gfx_line(x+width,y+height*2/5,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y+height*4/5);
    gfx_line(x,y+height*4/5,x+width*2/3,y+height*4/5);
    gfx_line(x+width*2/3,y+height*4/5,x+width*2/3,y+height*3/5);
    gfx_line(x+width*2/3,y+height*3/5,x,y+height*3/5);
    gfx_line(x,y+height*3/5,x,y);
    
}

void draw_six(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height/5);
    gfx_line(x+width,y+height/5,x+width/3,y+height/5);
    gfx_line(x+width/3,y+height/5,x+width/3,y+height*2/5);
    gfx_line(x+width/3,y+height*2/5,x+width,y+height*2/5);
    gfx_line(x+width,y+height*2/5,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y);
    gfx_line(x+width/3,y+height*3/5,x+width*2/3,y+height*3/5);
    gfx_line(x+width*2/3,y+height*3/5,x+width*2/3,y+height*4/5);
    gfx_line(x+width*2/3,y+height*4/5,x+width/3,y+height*4/5);
    gfx_line(x+width/3,y+height*4/5,x+width/3,y+height*3/5);
    
}

void draw_seven(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x+width*2/3,y+height);
    gfx_line(x+width*2/3,y+height,x+width*2/3,y+height/5);
    gfx_line(x+width*2/3,y+height/5,x,y+height/5);
    gfx_line(x,y+height/5,x,y);
    
}

void draw_eight(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y);
    gfx_line(x+width/3,y+height/5,x+width*2/3,y+height/5);
    gfx_line(x+width*2/3,y+height/5,x+width*2/3,y+height*2/5);
    gfx_line(x+width*2/3,y+height*2/5,x+width/3,y+height*2/5);
    gfx_line(x+width/3,y+height*2/5,x+width/3,y+height/5);
    gfx_line(x+width/3,y+height*3/5,x+width*2/3,y+height*3/5);
    gfx_line(x+width*2/3,y+height*3/5,x+width*2/3,y+height*4/5);
    gfx_line(x+width*2/3,y+height*4/5,x+width/3,y+height*4/5);
    gfx_line(x+width/3,y+height*4/5,x+width/3,y+height*3/5);
    
}

void draw_nine(int x, int y, int height){
    int width = height/2;
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x+width,y+height,x,y+height);
    gfx_line(x,y+height,x,y+height*4/5);
    gfx_line(x,y+height*4/5,x+width*2/3,y+height*4/5);
    gfx_line(x+width*2/3,y+height*4/5,x+width*2/3,y+height*3/5);
    gfx_line(x+width*2/3,y+height*3/5,x,y+height*3/5);
    gfx_line(x,y+height*3/5,x,y);
    gfx_line(x+width/3,y+height/5,x+width*2/3,y+height/5);
    gfx_line(x+width*2/3,y+height/5,x+width*2/3,y+height*2/5);
    gfx_line(x+width*2/3,y+height*2/5,x+width/3,y+height*2/5);
    gfx_line(x+width/3,y+height*2/5,x+width/3,y+height/5);
    
}

void draw_plus(int x, int y, int height){
    int width = height/2;
    gfx_line(x+width,y,x+width,y+height);
    gfx_line(x,y+height/2,x+height,y+height/2);
    
}

void draw_digit(int x, int y, int height, char n){
    switch(n){
        case '1': draw_one(x,y,height); break;
        case '2': draw_two(x,y,height); break;
        case '3': draw_three(x,y,height); break;
        case '4': draw_four(x,y,height); break;
        case '5': draw_five(x,y,height); break;
        case '6': draw_six(x,y,height); break;
        case '7': draw_seven(x,y,height); break;
        case '8': draw_eight(x,y,height); break;
        case '9': draw_nine(x,y,height); break;
        case '0': draw_zero(x,y,height); break;
        default: draw_plus(x,y,height); break;
    }
}

void draw_number(int x, int y, int height, int n){
    if(n == 0){ draw_zero(x,y,height); return;}
    int width = height/2;
    int divisor = 1, subtracted;
    char c;
    if (n < 0){
        gfx_line(x,y+5,x+5,y+5);
        n *= -1;
        x += 10;
     }
    while(divisor <= n){ divisor *= 10;}
    do{
        divisor /= 10;
        c = (n / divisor) + 48;
        draw_digit(x,y,height,c);
        x += (width*5/4);
        subtracted = (n/divisor) * divisor;
        n = n - subtracted;
    } while(divisor != 1);
}


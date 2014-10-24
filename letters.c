//letters.c:

#include "gfx.h"


void drawM(int x, int y, int height, int width){

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width/2,y);

    gfx_line(x+width/2,y,x+width,y-height);

    gfx_line(x+width,y-height,x+width,y);

}

void drawI(int x, int y, int height, int width){
    gfx_line(x,y-height, x+width, y-height);
    gfx_line(x,y,x+width,y);
    gfx_line(x+(width/2), y, x+(width/2), y-height);
}

void drawS(int x, int y, int height, int width){

    gfx_line(x,y,x+width,y);

    gfx_line(x+width,y,x+width,y-height/2);

    gfx_line(x+width,y-height/2,x,y-height/2);

    gfx_line(x,y-height/2,x,y-height);

    gfx_line(x,y-height,x+width,y-height);

}

void drawL(int x, int y, int height, int width){

    gfx_line(x,y,x+width,y);

    gfx_line(x,y,x,y-height);

}

void drawE(int x, int y, int height, int width){

    gfx_line(x,y,x+width,y);

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height/2,x+width,y-height/2);

    gfx_line(x,y-height,x+width,y-height);

}

void drawC(int x, int y, int height, int width){

    gfx_line(x,y,x+width,y);

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width,y-height);

}

void drawG(int x, int y, int height, int width){
    gfx_line(x,y,x+width,y);

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width,y-height);
    gfx_line(x+width, y, x+width, y-(height/3));
    gfx_line(x+width, y-(height/3), x+(width/2), y-(height/3));
}


void drawV(int x, int y, int height, int width){
    gfx_line(x+(width/2), y, x, y-height);
    gfx_line(x+(width/2), y, x+width, y-height);
}


void drawO(int x, int y, int height, int width){

    gfx_line(x,y,x+width,y);

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width,y-height);

    gfx_line(x+width,y,x+width,y-height);

}

void drawA(int x, int y, int height, int width){

    gfx_line(x,y,x+width/2,y-height);

    gfx_line(x+width/2,y-height,x+width,y);

    gfx_line(x+width/4,y-height/2,x+3*width/4,y-height/2);

}

void drawN(int x, int y, int height, int width){

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width,y);

    gfx_line(x+width,y,x+width,y-height);

}

void drawP(int x, int y, int height, int width){

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width,y-height);

    gfx_line(x+width,y-height,x+width,y-height/2);

    gfx_line(x,y-height/2,x+width,y-height/2);

}

void drawR(int x, int y, int height, int width){

    gfx_line(x,y,x,y-height);

    gfx_line(x,y-height,x+width,y-height);

    gfx_line(x+width,y-height,x+width,y-height/2);

    gfx_line(x,y-height/2,x+width,y-height/2);

    gfx_line(x,y-height/2,x+width,y);

}

void drawT(int x, int y, int height, int width){

    gfx_line(x,y,x,y-height);

    gfx_line(x-width/2,y-height,x+width/2,y-height);

}

void drawD(int x, int y, int height, int width){

    gfx_line(x,y,x+width,y);

    gfx_line(x+width/5,y,x+width/5,y-height);

    gfx_line(x,y-height,x+width,y-height);

    gfx_line(x+width,y,x+width,y-height);

}

void drawQuestionMark(int x, int y, int height, int width){
    gfx_line(x, y-(height*2/3), x, y-height);
    gfx_line(x, y-height, x+width, y-height);
    gfx_line(x+width, y-height, x+width, y-(height/2));
    gfx_line(x+width, y-(height/2), x+(width/2), y-(height/2));
    gfx_line(x+(width/2), y-(height/2), x+(width/2), y-(height/3));
    gfx_line(x+(width/2), y-(height/6), x+(width/2), y);
}

void drawLeftBracket(int x, int y, int height, int width){
    gfx_line(x+(width/2),y, x, y);
    gfx_line(x, y, x, y-height);
    gfx_line(x, y-height, x+(width/2), y-height);
}

void drawRightBracket(int x, int y, int height, int width){
    gfx_line(x+(width/2), y, x+width, y);
    gfx_line(x+width, y, x+width, y-height);
    gfx_line(x+width, y-height, x+(width/2), y-height);
}

void drawY(int x, int y, int height, int width){
    gfx_line(x+(width/2), y, x+(width/2), y-(height*2/3));
    gfx_line(x+(width/2), y-(height*2/3), x, y-height);
    gfx_line(x+(width/2), y-(height*2/3), x+width, y-height);
}

void drawSlash(int x, int y, int height, int width){
    gfx_line(x,y,x+width,y-height);
}

void drawU(int x, int y, int height, int width){
    gfx_line(x,y-height,x,y);
    gfx_line(x,y,x+width,y);
    gfx_line(x+width,y,x+width,y-height);
}

// A limited case-switch function for the letters used in this game
void draw_letter(char c, int x, int y, int height, int width){
    switch(c){
        case 'm': drawM(x,y,height,width); break;
        case 'i': drawI(x,y,height,width); break;
        case 's': drawS(x,y,height,width); break;
        case 'l': drawL(x,y,height,width); break;
        case 'e': drawE(x,y,height,width); break;
        case 'c': drawC(x,y,height,width); break;
        case 'o': drawO(x,y,height,width); break;
        case 'a': drawA(x,y,height,width); break;
        case 'n': drawN(x,y,height,width); break;
        case 'd': drawD(x,y,height,width); break;
        case 'p': drawP(x,y,height,width); break;
        case 'r': drawR(x,y,height,width); break;
        case 'g': drawG(x,y,height,width); break;
        case 'v': drawV(x,y,height,width); break;
        case 'y': drawY(x,y,height,width); break;
        case 'u': drawU(x,y,height,width); break;
        case '?': drawQuestionMark(x,y,height,width); break;
        case '[': drawLeftBracket(x,y,height,width); break;
        case ']': drawRightBracket(x,y,height,width); break;
        case '/': drawSlash(x,y,height,width); break;
    }
}

void drawWord(char word[], int x, int y, int height, int width){
    char c;
    int i = 0, offset = width+10;
    tolower(word);
    for(i = 0; word[i]; i++){
        draw_letter(word[i], x, y, height, width);
        x += offset;
    }
}







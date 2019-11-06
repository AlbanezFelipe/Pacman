#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "pacman.h"
#include "map.h"
#include "controls.h"
#include "character.h"

int textureX = 0;
int textureY = 0;

SDL_Rect collisor = {0,0,8,8};

enum direction pacmanDirection;

bool super;

const int superTimer = 1000;

//Debug

void printCollisor(SDL_Renderer *r){
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);

    SDL_Rect c = collisor;
    c.x = collisor.x * 2.5f;
    c.y = collisor.y * 2.5f;
    c.h = 8 * 2.5f;
    c.w = 8 * 2.5f;

    SDL_Rect cc = collisor;
    cc.x = (collisor.x+8) * 2.5f;
    cc.y = collisor.y * 2.5f;
    cc.h = 8 * 2.5f;
    cc.w = 8 * 2.5f;

    SDL_RenderDrawRect(r, &c);
    SDL_RenderDrawRect(r, &cc);
}

void updateTexture(){
    textureX = collisor.x -3;
    textureY = collisor.y -3;
}

void startPacman(void){
    collisor.x=108;
    collisor.y=208;
    pacmanDirection = stopped;
    updateTexture();
    super = false;
}

int reverseModule(int n){
    return n%8 > 4 ? 8 - (n%8) : n%8;
}

void fixForceMove(bool axis){
    int *m = !axis ? &collisor.x : &collisor.y;

    int out = *(m)%8;
    if(out < 5){
        *m -= out;
    }else{
        *m += reverseModule(out);
    }
}


bool validateMove(bool axis, bool reverse){
    /*
     * axis    = True  = X
     * axis    = False = y
     * reverse = True  = Plus
     * reverse = False = Minus
     */
    const int force = 3; //0 to no force moves and 3 to allow all force moves

    const int m = 4;// constant for calculation, do not change this

    enum tile t = *(getTileOnMap(
         axis ? !reverse ? collisor.x+m : collisor.x-m : collisor.x,
        !axis ? !reverse ? collisor.y+m : collisor.y-m : collisor.y
    , true, !reverse));

    return (t != block && t != ghostGate) &&
    ((reverseModule(collisor.x) <= force) || axis) &&
    ((reverseModule(collisor.y) <= force) || !axis);
}

void getCoin(){
    enum tile *currentTile = getTileOnMap(collisor.x,collisor.y,true,true);
    if(*currentTile == coin){
        *currentTile = empty;
    } else
    if(*currentTile == superCoin){
        *currentTile = empty;
        super = true;
    }
}

void updateSuperTimer(){
    static int superCounter = 0;
    if(super && superCounter < superTimer){
        superCounter++;
    }else{
        superCounter=0;
        super = false;
    }
}

void controlPacman(){

    if(collisor.x <= -16){
        collisor.x = 239;
    }
    if(collisor.x >= 240){
        collisor.x = -15;
    }

    bool moved = false;

    if(keyArrowUp || pacmanDirection == up){
        if(validateMove(false, true)){
            collisor.y--;
            fixForceMove(false);
            pacmanDirection=up;
            moved = true;
        }
    }

    if(keyArrowDown || pacmanDirection == down){
        if(validateMove(false, false)){
            collisor.y++;
            fixForceMove(false);
            pacmanDirection=down;
            moved = true;
        }
    }

    if(keyArrowRight || pacmanDirection == right){
        if(validateMove(true, false)){
            collisor.x++;
            fixForceMove(true);
            pacmanDirection=right;
            moved = true;
        }
    }

   if(keyArrowLeft || pacmanDirection == left){
        if(validateMove(true, true)){
            collisor.x--;
            fixForceMove(true);
            pacmanDirection=left;
            moved = true;
        }
    }

    if(!moved){
        pacmanDirection = stopped;
    }

    updateTexture();
    getCoin();

    updateSuperTimer();

}


//For Drawing
int getPacmanX(){
    return textureX;
}

int getPacmanY(){
    return textureY;
}

const SDL_Rect * getPacmanCollider(void){
    return &collisor;
}

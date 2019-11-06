#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "pacman.h"
#include "ghost.h"
#include "character.h"

static const int tileDraw = 8; //Width and Height of each tile

static const int animationPerFrame = 100; // milliseconds

unsigned int currentTime, lastTime=0;

bool animationCounter = false;

void updateAnimationTextures(){
    animationCounter = !animationCounter;
}

void listenerAnimationTextures(){
    animationCounter = false;
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + animationPerFrame) {
        updateAnimationTextures();
        lastTime = currentTime;
    }
}

void drawTop(){
    return;
}

void drawArena(SDL_Renderer *renderer, SDL_Texture *texture, const float *scale){

    //Set Texture Section
    SDL_Rect section = {
        0, //0 for full arena and 228 for empty arena
        0,
        tileDraw, //Constant of Texture 8 = 1 Tile 224 = Full Arena
        tileDraw  //Constant of Texture 8 = 1 Tile 248 = Full Arena
    };

    //Set Dimensions
    SDL_Rect dimension = {
        0,
        (tileDraw * 3) * (*scale), // Jump 3 Tiles for Top
        tileDraw  * (*scale),
        tileDraw  * (*scale)
    };

    enum tile *map = getMap();

    for(int i=3; i < 34; i++){

        if(i > 3){
            section.x = 0;
            section.y += tileDraw;

            dimension.x = 0;
            dimension.y += tileDraw * (*scale);
        }

        for(int j=0; j < 28; j++){

            if(j > 0){
                section.x += tileDraw;
                dimension.x += tileDraw * (*scale);
            }

            //Check for coins
            if(*(map + (i * 28 + j)) == empty){
                section.x += 228;
                SDL_RenderCopy(renderer, texture, &section, &dimension); //no coins
                section.x -= 228;
            }else{
                SDL_RenderCopy(renderer, texture, &section, &dimension); //with coins
            }
        }
    }
}

void drawBottom(){
    return;
}

void drawPacman(SDL_Renderer *renderer, SDL_Texture *texture, const float *scale){

    static int pacmanAnimationCounter = 0;
    /*
     * 0 = First Sprite
     * 1 = Second Sprite
     * 2 = Third Sprite
     */

    if(animationCounter && pacmanDirection != stopped){
        pacmanAnimationCounter = pacmanAnimationCounter == 2 ? 0 : pacmanAnimationCounter + 1;
    }

    //Set Texture Section
    SDL_Rect section = {
        457 + (pacmanDirection != stopped ? pacmanAnimationCounter * 16 : 32), // x Pacman on Texture / Pacman 1 = 456 / Pacman 2 = 456+17
        1   + (pacmanAnimationCounter < 2 && pacmanDirection != stopped ? (((int)pacmanDirection) * 16) : 0),      // y Pacman on Texture
        13,     // Width of Pacman on Texture
        13      // Height of Pacman on Texture
    };

    //Set Dimensions
    SDL_Rect dimension = {
        getPacmanX()  * (*scale), // x Pacman on Screen
        getPacmanY()  * (*scale), // y Pacman on Screen
        pacmanWidth   * (*scale), // Width of Pacman on Screen
        pacmanHeight  * (*scale)  // Height of Pacman on Screen
    };

    SDL_RenderCopy(renderer, texture, &section, &dimension);
}

void drawGhosts(SDL_Renderer *renderer, SDL_Texture *texture, const float *scale){

    static int ghostsAnimationCounter[4] = {0, 0, 0, 0};

    for(int i=0; i < 4; i++){

        if(animationCounter && (*(getGhostsDirection() + i)) != stopped){
            ghostsAnimationCounter[i] = ghostsAnimationCounter[i] == 1 ? 0 : ghostsAnimationCounter[i] + 1;
        }

        SDL_Rect section = {
            457 +
                (
                (*(getDeadGhost()+i)) ? 128 + ((*(getGhostsDirection() + i)) * 16) //If Ghost is Dead
                :
                super ? 128 + (ghostsAnimationCounter[i] * 16) // If Pacman on super
                :
                (ghostsAnimationCounter[i] * 16) +
                ((*(getGhostsDirection() + i)) != stopped ? ( (*(getGhostsDirection() + i)) * 32): 0) //Default
                ),

            65 + ( !*(getDeadGhost()+i) ? (!super ? (16 * i) : 0) : 16),
            14,
            14
        };
        //Set Dimensions
        SDL_Rect dimension = {
            *(getGhostsTexturesX()+i)  * (*scale),
            *(getGhostsTexturesY()+i)  * (*scale),
            14   * (*scale),
            14  * (*scale)
        };

        SDL_RenderCopy(renderer, texture, &section, &dimension);
    }
}

void drawAll(SDL_Renderer *renderer, SDL_Texture *texture, const int *screenWidth, const int *screenHeight, const float *scale){

    //Dimension of texture
    //Width:  680
    //Height: 248
    drawArena(renderer, texture, scale);
    drawPacman(renderer, texture, scale);
    drawGhosts(renderer, texture, scale);
    listenerAnimationTextures();
   // printf("%d\n", pacmanDirection);
}

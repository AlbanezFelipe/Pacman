#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "draw.h"
#include "map.h"
#include "controls.h"
#include "pacman.h"
#include "ghost.h"
#include "collisionIntersection.h"

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

void startGame(void);

//Debug
void lineCut(SDL_Renderer *r, float scale, int width, int height){
    int frameCut = 8 * scale;

    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    for(int counter = 0;counter < width;counter += frameCut){
        SDL_RenderDrawLine(r, counter,0,counter, height);

    }
    for(int counter = 0;counter < height;counter += frameCut){
        SDL_RenderDrawLine(r, 0,counter,width, counter);
    }

}

int main(int argc, char **argv)
{
    //Game Dimension
    const float scale = 2.5f;
    const int width = 224 * scale;
    const int height = 288 * scale;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * texture = initialize_texture_from_file("pacman.png", renderer);

    //Background Color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    startGame();

    while(isRunning)
    {
        //Update events
        eventListener();

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        controlPacman();
        controlGhost();

        // Draw Game
        drawAll(renderer, texture, &width, &height, &scale);

        if(isMapClear()){
            startGame();//youWin()
        }

        int ghostIndex = wasPacmanCaught(getPacmanCollider(), getGhostsCollider());
        if(ghostIndex != -1){
            if(super)
                killGhost(ghostIndex);
            else
                startGame();
        }

        //SDL_Rect r1= {0,0,8,8};
        //SDL_Rect r2 = {8,8,8,8};
        //if(){
        //    printf("%d",SDL_HasIntersection(&r1,&r2));
        //}

        //printCollisor(renderer);

        //SDL_RenderDrawLine(renderer, 200,200,600, 600);
        //lineCut(renderer, scale, width, height);
        //printGhostsCollider(renderer);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

void startGame(void){
    //Spawn Pacman
    startPacman();

    //Spawn Ghosts
    startGhosts();

    //Start Map
    initializeMap();

}

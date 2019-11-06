#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "controls.h"

SDL_Event event;

bool isRunning = true;

bool keyArrowUp    = false;
bool keyArrowDown  = false;
bool keyArrowRight = false;
bool keyArrowLeft  = false;

void eventListener(void){

    // Process events
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if(event.type == SDL_KEYDOWN){
            keyArrowUp    = event.key.keysym.sym == SDLK_UP;
            keyArrowDown  = event.key.keysym.sym == SDLK_DOWN;
            keyArrowRight = event.key.keysym.sym == SDLK_RIGHT;
            keyArrowLeft  = event.key.keysym.sym == SDLK_LEFT;

        } else{
            keyArrowUp    = false;
            keyArrowDown  = false;
            keyArrowRight = false;
            keyArrowLeft  = false;
        }
    }
}

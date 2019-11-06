#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int wasPacmanCaught(const SDL_Rect * pacman, const SDL_Rect * ghosts){
    for(int i=0; i < 4; i++){
        if(SDL_HasIntersection(pacman, ghosts + i)){
            return i;
        }
    }
    return -1;
}

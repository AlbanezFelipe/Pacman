#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "character.h"
#include "controls.h"
#include "map.h"
#include "utils.h"

static const int nOfGhosts = 4;

int ghostTextureX[4];
int ghostTextureY[4];
SDL_Rect ghostCollider[4];
enum direction ghostDirection[4];

bool ghostDead[4];

void printGhostsCollider(SDL_Renderer *r){
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    for(int i=0; i < 4; i++){
        SDL_Rect c = ghostCollider[i];
        c.x = c.x * 2.5f;
        c.y = c.y * 2.5f;
        c.h = 8 * 2.5f;
        c.w = 8 * 2.5f;

        SDL_RenderDrawRect(r, &c);
    }
}

void updateGhostsTexture(){
    for(int i=0; i < 4; i++){
        ghostTextureX[i] = ghostCollider[i].x - 3;
        ghostTextureY[i] = ghostCollider[i].y - 3;
    }
}

void startGhosts(void){
    ghostCollider[0].x = 108;//108
    ghostCollider[0].y = 64;//112

    ghostCollider[1].x = 92;
    ghostCollider[1].y = 136;

    ghostCollider[2].x = 108;
    ghostCollider[2].y = 136;

    ghostCollider[3].x = 124;
    ghostCollider[3].y = 136;

    for(int i=0; i < 4; i++){
        ghostDirection[i] = stopped;
        ghostCollider[i].w = 8;
        ghostCollider[i].h = 8;
        ghostDead[i] = false;
    }
    updateGhostsTexture();

}

bool ghostValidateMove(bool axis, bool reverse, int i){
    return *(getTileOnMap(
         axis ? !reverse ? (ghostCollider[i].x)+8 : (ghostCollider[i].x)-1 : ghostCollider[i].x,
        !axis ? !reverse ? (ghostCollider[i].y)+8 : (ghostCollider[i].y)-1 : ghostCollider[i].y,
        false, false)) != block;
}

void controlGhost(void){

    for(int j = 0; j < 4; j++){

    if(ghostCollider[0].x <= -16){
        ghostCollider[0].x = 239;
    }
    if(ghostCollider[0].x >= 240){
        ghostCollider[0].x = -15;
    }

    bool moved  = false;
    static bool mUp[4]    = {false, false, false, false};
    static bool mDown[4]  = {false, false, false, false};
    static bool mRight[4] = {false, false, false, false};
    static bool mLeft[4]  = {false, false, false, false};
    enum direction n = stopped;
    if(
       (ghostCollider[j].x % 8 == 0 && (ghostDirection[j] == right || ghostDirection[j] == left || ghostDirection[j] == stopped)) ||
       (ghostCollider[j].y % 8 == 0 && (ghostDirection[j] == up || ghostDirection[j] == down || ghostDirection[j] == stopped))
    ){
            mUp[j] = ghostValidateMove(false, true,j);
            mDown[j] = ghostValidateMove(false, false,j);
            mRight[j] = ghostValidateMove(true, false,j);
            mLeft[j] = ghostValidateMove(true, true,j);

/*
        printf("up: %d\n", mUp);
    printf("down: %d\n", mDown);
    printf("right: %d\n", mRight);
    printf("left: %d\n", mLeft);
*/

        int r = randomNumber(0,4);
        //printf("%d\n", r);
        bool arr[4] = {mRight[j], mLeft[j], mUp[j], mDown[j]};
        int i = 0;

        if(!ghostDead[j]){
            while(n == stopped){
                if(r == i){
                    if(arr[i]){
                        n = i;
                        break;
                    }else{
                        r++;
                        if(r >= 4){
                            r = 0;
                        }
                    }

                }
                i++;
                if(i >= 4){
                    i=0;
                }
            }
        }
        else{
            if(ghostCollider[j].y > 100 && ghostCollider[j].y < 132 &&
               ghostCollider[j].x > 84  && ghostCollider[j].x < 140&& false){
                printf("inside");
            }
            else{
                    //104,88 120.96
                int xD = ghostCollider[j].x-108;
                int yD = ghostCollider[j].y - 120;
                printf("xD: %d\n",xD);
                printf("yD: %d\n",yD);
                if(mUp[j] && ghostCollider[j].y >= 96 && ghostCollider[j].y >= 88){
                    n = up;
                }
                else if(mDown[j] && ghostCollider[j].y < 120 && ghostDirection[j] != up && ghostDirection[j] != down &&  yD > xD){
                    n=down;
                }
                else if(mRight[j] && ghostCollider[j].x < 108 && ghostDirection[j] != left && ghostDirection[j] != right &&  yD < xD){
                    n=right;
                }
                else if(mLeft[j] && ghostCollider[j].x > 108 &&  ghostDirection[j] != right && ghostDirection[j] != left &&  yD < xD){
                    n=left;
                }
                else{
                    printf("a");
                    if(mUp[j]) n = up;
                    if(mDown[j]) n = down;
                    if(mRight[j]) n = right;
                    if(mLeft[j]) n = left;
                }
                printf("n: %d\n",n);
            }
        }
    }

    if(n == up || ghostDirection[j] == up){
        if(mUp[j] && ghostCollider[j].x % 8 == 0){
            ghostCollider[j].y--;
            ghostDirection[j] = up;
            moved = true;
        }
    }

    if(n == down || ghostDirection[j] == down){
        if(mDown[j] && ghostCollider[j].x % 8 == 0){
            ghostCollider[j].y++;
            ghostDirection[j] = down;
            moved = true;
        }
    }

    if(n == right ||  ghostDirection[j] == right){
        if(mRight[j] && ghostCollider[j].y % 8 == 0){
            ghostCollider[j].x++;
            ghostDirection[j] = right;
            moved = true;
        }
    }

   if(n == left ||  ghostDirection[j] == left){
        if(mLeft[j] && ghostCollider[j].y % 8 == 0){
            //printf("a");
            ghostCollider[j].x--;
            ghostDirection[j] = left;
            moved = true;
        }
    }

    if(!moved){
        ghostDirection[j] = stopped;

    }

    }

    updateGhostsTexture();
}

void killGhost(int index){
    ghostDead[index] = true;
    //startGhosts();
}

bool * getDeadGhost(void){
    return &ghostDead[0];
}

int * getGhostsTexturesX(void){
    return &ghostTextureX[0];
}

int * getGhostsTexturesY(void){
    return &ghostTextureY[0];
}

SDL_Rect * getGhostsCollider(void){
    return &ghostCollider[0];
}

enum direction * getGhostsDirection(void){
    return &ghostDirection[0];
}

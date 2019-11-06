#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "map.h"

enum tile map[36][28];

/*
 * This function is only use for debug
 * It was useful for make map
 */
void printMap(void){
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 28; j++){
            if(map[i][j]==empty){
                printf(".");
            }
            if(map[i][j]==block){
                printf("#");
            }
            if(map[i][j]==coin){
                printf("o");
            }
            if(map[i][j]==ghostGate){
                printf("H");
            }
            if(map[i][j]==superCoin){
                printf("*");
            }
        }
        printf("\n");
    }
}

void initializeMap(void){

    //All coins, Top and Bottom sections
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 28; j++){
            if(i < 3 || i > 33){
                map[i][j] = empty;
            }
            else{
                /*
                 * This is just for avoid defining common tiles like coins,
                 * Some tiles will be overwrite later
                 */
                map[i][j] = coin;
            }
        }
    }

    //Top and Bottom Wall
    for(int i = 0; i < 28; i++){
        map[3][i] = block;
        map[33][i] = block;
    }

    //Left and Right Wall
    for(int i = 4; i < 34; i++){
        if(i != 17){
            map[i][0] = block;
            map[i][27] = block;
        }
    }

    //Rectangles on top of arena

    for(int i=2; i < 6; i++){

        //First Rectangle(Small)
        map[5][i] = block;
        map[6][i] = block;
        map[7][i] = block;

        //Second Rectangle(big)
        map[5][i+5] = block;
        map[6][i+5] = block;
        map[7][i+5] = block;

        if(i==5){
            map[5][i+6] = block;
            map[6][i+6] = block;
            map[7][i+6] = block;
        }

        //Third Rectangle(big)
        map[5][i+14] = block;
        map[6][i+14] = block;
        map[7][i+14] = block;

        if(i==5){
            map[5][i+15] = block;
            map[6][i+15] = block;
            map[7][i+15] = block;
        }

        //Fourth Rectangle(Small)
        map[5][i+20] = block;
        map[6][i+20] = block;
        map[7][i+20] = block;

        //others rectangles
        map[9][i] = block;
        map[10][i] = block;

        map[9][i+20] = block;
        map[10][i+20] = block;
    }

    //Other Line

    for(int i=4; i < 8; i++){
        map[i][13] = block;
        map[i][14] = block;
    }

    //Lines, like this draft
    /*
     * ########
     * ooo##ooo
     * ooo##ooo
     * ooo##ooo
     * ooo##ooo
     */
     int l[] = {9, 21, 27};
     for(int j=0; j < 3; j++){
         for(int i=10; i < 18; i++){
            map[l[j]][i] = block;
            map[l[j]+1][i] = block;
            if(i > 12 && i < 15){
                map[l[j]+2][i] = block;
                map[l[j]+3][i] = block;
                map[l[j]+4][i] = block;
            }
         }
     }

     //Another Lines
     /*
     * ##oooooo
     * ##oooooo
     * ##oooooo
     * #####ooo
     * #####ooo
     * ##oooooo
     * ##oooooo
     * ##oooooo
     */
     for(int i = 9; i < 17; i++){
        map[i][7] = block;
        map[i][8] = block;

        map[i][19] = block;
        map[i][20] = block;

        if(i > 11 && i < 14){
            map[i][9] = block;
            map[i][10] = block;
            map[i][11] = block;

            map[i][16] = block;
            map[i][17] = block;
            map[i][18] = block;
        }
     }

     //Ghost Area
     for(int j=15; j < 20; j++){
         for(int i=10; i < 18; i++){
            if((i==13 || i==14) && j==15){
                map[j][i] = ghostGate;
            }
            else if(i == 10 || i == 17 || j==15 || j==19){
                map[j][i] = block;
            }
            else {
                map[j][i] = empty;
            }
         }
     }

     //Rectangles on Middle
     for(int j=12; j<17;j++){
         for(int i=1; i<6; i++){
            map[j][i] = block;
            map[j+6][i] = block;
            map[j][i+21] = block;
            map[j+6][i+21] = block;
         }
     }

     //Horizontal Rectangles on Bottom
     for(int i=7; i< 12; i++){
        map[24][i] = block;
        map[25][i] = block;
        map[24][i+9] = block;
        map[25][i+9] = block;
     }

     //Vertical Rectangles on Bottom
     for(int i=18; i < 23; i++){
        map[i][7] = block;
        map[i][8] = block;
        map[i][19] = block;
        map[i][20] = block;
     }

     //Bottom Lines
     for(int i=2; i < 26; i++){
        map[30][i] = block;
        map[31][i] = block;
        if((i>6 && i<9) || (i>18 && i<21)){
            map[29][i] = block;
            map[28][i] = block;
            map[27][i] = block;
        }

        if(i==11){
            i=15;
        }
     }

     //Others Bottom Lines
     for(int i=24; i < 29; i++){
        map[i][4] = block;
        map[i][5] = block;
        map[i][22] = block;
        map[i][23] = block;
     }

     //Others
     for(int i=2; i < 4; i++){
        map[24][i] = block;
        map[25][i] = block;

        map[24][i+22] = block;
        map[25][i+22] = block;
     }

     for(int i=1;i < 3;i++){
        map[27][i] = block;
        map[28][i] = block;

        map[27][i+24] = block;
        map[28][i+24] = block;
     }

     //empty spaces
     for(int j=14; j <21; j++){
         for(int i=9; i < 19; i++){
            if(j == 14 || j == 20 || i==9 || i==18)
                map[j][i] = empty;
         }
     }
     map[21][9]  = empty;
     map[22][9]  = empty;
     map[21][18] = empty;
     map[22][18] = empty;
     map[13][12] = empty;
     map[12][12] = empty;
     map[13][15] = empty;
     map[12][15] = empty;

     for(int i = 0; i < 28; i++){
        if((i < 9 && i != 6) || (i > 18 && i != 21))
            map[17][i] = empty;
     }

    //Super Coins
    map[6][1] = superCoin;
    map[6][26] = superCoin;
    map[26][1] = superCoin;
    map[26][26] = superCoin;

    //printMap();
}

enum tile * getMap(void){
    return (void *) &map[0][0];
}

enum tile * getTileOnMap(int x, int y, bool getRounded,bool forceReverse){
    int xTile = getRounded ? (int) round((x / 8.0f) + (forceReverse ? 0.1f : -0.1f)) : (x - (x%8)) / 8;
    int yTile = getRounded ? (int) round((y / 8.0f) + (forceReverse ? 0.1f : -0.1f)) : (y - (y%8)) / 8;

    if(xTile < 0 || xTile > 27){
        return &map[0][0];
    }

    return &map[yTile][xTile];
}

bool isMapClear(void){
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 28; j++){
            if(map[i][j] == coin || map[i][j] == superCoin){
                return false;
            }
        }
    }
    return true;
}

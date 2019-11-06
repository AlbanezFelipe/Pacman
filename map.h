#pragma once

enum tile {
    block,
    empty,
    coin,
    superCoin,
    ghostGate
};

void printMap(void);
void initializeMap(void);
enum tile * getMap(void);
enum tile * getTileOnMap(int x, int y, bool getRounded,bool forceReverse);
bool isMapClear(void);

#pragma once

void startGhosts(void);
void controlGhost(void);

int * getGhostsTexturesX(void);
int * getGhostsTexturesY(void);
void printGhostsCollider(SDL_Renderer *r);
SDL_Rect * getGhostsCollider(void);
//static const int nOfGhosts = 4;
enum direction * getGhostsDirection(void);
void killGhost(int index);

bool * getDeadGhost(void);

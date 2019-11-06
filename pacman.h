#pragma once

static const int pacmanWidth = 13;  // Width of Pacman Texture
static const int pacmanHeight = 13; // Height of Pacman Texture

int getPacmanX(void); // location of Texture
int getPacmanY(void); // location of Texture

void startPacman(void);   // Initialize Pacman on map
void controlPacman(void); // Update Pacman
void printCollisor(SDL_Renderer *r); //Debug

const SDL_Rect * getPacmanCollider(void);

extern enum direction pacmanDirection;

extern bool super;


#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

//Handle rotation of pac-man
float getRotation(Player *plr);

//Handle player behavior
void handlePlayer(Player *plr, Color* img, Texture2D* pacman);

#endif
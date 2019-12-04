#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H
void handlePlayer(Player *plr, Color* img, Texture2D* pacman);
float getRotation(Player *plr);
void move(Player *plr);
#endif
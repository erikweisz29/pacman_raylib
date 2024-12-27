#include "main.h"
#include "enemies.h"

#ifndef RENDER_H
#define RENDER_H
void renderBackground(int gamestate, Texture2D* bg);
void drawMenu(int menustate, bool debug);
void drawPont(Point** points);
void drawPacman(Player *plr, Texture2D *pacman);
float getRotation(Player* plr);
void getPlusXY(Player *plr, bool *plusX, bool *plusY);
void drawEnemies(Enemies *emys, Texture2D textureArr[4][5]);
#endif
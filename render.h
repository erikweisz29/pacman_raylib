#include "main.h"
#include "enemies.h"

#ifndef RENDER_H
#define RENDER_H
void renderBackground(int gamestate, Texture2D* bg);
void drawMenu(int menustate, bool debug);
void drawPont(Pont** pontok);
void drawPacman(Player *plr, Texture2D *pacman);
float getRotation(Player* plr);
void getPlusXY(Player *plr, bool *plusX, bool *plusY);
void drawEnemies(Enemies *emys, EnemiesPng* enemyTextures);
#endif
#include "main.h"

#ifndef PONT_H
#define PONT_H
bool colorCmp(Color clr1, Color clr2);
bool checkPont(int x, int y, Color img[]);
void initPont(Pont*** pontok);
void handlePoints(Player *plr, Pont **pontok, int* score);
#endif
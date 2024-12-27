#include "main.h"
#include "raylib.h"

#ifndef PONT_H
#define PONT_H
static const int width = 600/20;
static const int height = 581/20;

//Color comparer function
bool colorCmp(Color clr1, Color clr2);

//Checks if a given point is black in a given image
bool checkPoint(int x, int y, Color img[]);

//Initialize points
void initPoint(Point*** data);

//Handle points
void handlePoints(Player *plr, Point **pontok, int* score);
#endif
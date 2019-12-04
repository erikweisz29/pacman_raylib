#include <stdio.h>

#ifndef MENU_H
#define MENU_H
bool HandleMenu(int menustate, bool* debug);
void handleScoreboard(enum GameEnd gameend, int score, Texture2D *bg_used, Eredmeny eredmeny[]);
#endif
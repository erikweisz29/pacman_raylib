#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

//Lehetseges iranyok adatszerkezete
typedef struct PossibleDir {
    bool l;
    bool r;
    bool u;
    bool d;
} PossibleDir;

//Szellem koruli pontok tavolsaga a jatekoshoz
typedef struct Tavolsag {
    int up;
    int down;
    int left;
    int right;
} Tavolsag;

//Szellem adatstrukturaja
typedef struct Enemy {
    Player plr;
    PossibleDir pDir;
} Enemy;

//A negy szellem ebben az adatstrukturaban van, hogy egyutt at lehessen adni oket
typedef struct Enemies {
    Enemy blue;
    Enemy red;
    Enemy orange;
    Enemy pink;
} Enemies;

void handleRed(Enemy* emy, Player* plr, Color* img, bool* init);
void handlePink(Enemy* emy, Player* plr, Color* img, bool* init);
void handleBlue(Enemy* emy, Enemy* red, Player* plr, Color* img, bool* init);
void handleOrange(Enemy* emy, Player* plr, Color* img, bool* init);

bool checkDeath(Enemies *emys, Player *plr);

#endif
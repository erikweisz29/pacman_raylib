#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

//Data structure for possible directions
typedef struct PossibleDir {
    bool l;
    bool r;
    bool u;
    bool d;
} PossibleDir;

//Szellem koruli pontok tavolsaga a jatekoshoz
typedef struct EnemyPlayerDistance {
    int up;
    int down;
    int left;
    int right;
} EnemyPlayerDistance;

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

//Handle movement for red enemy - simply tries to move toward player
void handleRed(Enemy* emy, Player* plr, Color* img, bool* init);

//Handle movement for pink enemy - first, gets out of ghost box, then tries to move in front of the player
void handlePink(Enemy* emy, Player* plr, Color* img, bool* init);

//Handle movement for blue enemy:
// - first, tries to get out of ghost box
// - then, draws a line from the red enemy's position to the player's position, doubles it, and heads there
// - therefore, as the red enemy gets closer to the player, the blue enemy gets closer as well.
void handleBlue(Enemy* emy, Enemy* red, Player* plr, Color* img, bool* init);

//Handle movement for orange enemy:
// - First, tries to get out of ghost box
// - then, if it's close to the player: tries to run back to the center of the map
// - otherwise, heads towards the player
void handleOrange(Enemy* emy, Player* plr, Color* img, bool* init);

//Check if player died
bool checkDeath(Enemies *emys, Player *plr);

#endif
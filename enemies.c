#include "raylib.h"
#include "main.h"
#include "player.h"
#include "enemies.h"
#include "point.h"
#include <math.h>
#include <stdio.h>

//Set possible directions for enemies
void setPossibleDir(Enemy* emy, Color* img) {
    if (checkPoint(emy->plr.rec.x, emy->plr.rec.y + 20, img) && checkPoint(emy->plr.rec.x + 19, emy->plr.rec.y + 20, img)) {
        emy->pDir.d = true;
    } else emy->pDir.d = false;

    if (checkPoint(emy->plr.rec.x, emy->plr.rec.y - 1, img) && checkPoint(emy->plr.rec.x + 19, emy->plr.rec.y - 1, img)) {
        emy->pDir.u = true;
    } else emy->pDir.u = false;

    if (checkPoint(emy->plr.rec.x - 1, emy->plr.rec.y, img) && checkPoint(emy->plr.rec.x - 1, emy->plr.rec.y + 19, img)) {
        emy->pDir.l = true;;
    } else emy->pDir.l = false;

    if (checkPoint(emy->plr.rec.x + 20, emy->plr.rec.y, img) && checkPoint(emy->plr.rec.x + 20, emy->plr.rec.y + 19, img)) {
        emy->pDir.r = true;
    } else emy->pDir.r = false;
}

//Calculate distance between two points
int distance(int kezdetX, int kezdetY, int celX, int celY) {
    return (int) sqrt(pow(celX - kezdetX, 2) + pow(celY - kezdetY, 2));
}

//Get the direction for the shortest possible path
Dir minDir(PossibleDir pDir, EnemyPlayerDistance tav) {
    int min = 99999;
    Dir minDir = NONE;

    if (pDir.l && tav.left < min) {
        min = tav.left;
        minDir = LEFT;
    }
    if (pDir.r && tav.right < min) {
        min = tav.right;
        minDir = RIGHT;
    }
    if (pDir.d && tav.down < min) {
        min = tav.down;
        minDir = DOWN;
    }
    if (pDir.u && tav.up < min) {
        min = tav.up;
        minDir = UP;
    }

    return minDir;
}

EnemyPlayerDistance getEnemyPlayerDistance(Enemy* emy, int celX, int celY) {
    EnemyPlayerDistance tav = {-1, -1, -1, -1};
    
    tav.down = distance(emy->plr.rec.x, emy->plr.rec.y + 20, celX, celY);
    tav.up = distance(emy->plr.rec.x, emy->plr.rec.y - 20, celX, celY);
    tav.left = distance(emy->plr.rec.x - 20, emy->plr.rec.y, celX, celY);
    tav.right = distance(emy->plr.rec.x + 20, emy->plr.rec.y, celX, celY);

    return tav;
}

//Pathfinding for enemies
void pathfind(Enemy* emy, int celX, int celY, Color* img) {
    setPossibleDir(emy, img);

    EnemyPlayerDistance dist = getEnemyPlayerDistance(emy, celX, celY);
    Dir min = minDir(emy->pDir, dist);
    
    if (min != NONE && emy->plr.lastDir != min) {
        emy->plr.lastDir = emy->plr.dir;
        emy->plr.dir = min;
    }
}

//Check movement for enemies
void checkEnemyMove(Enemy* emy, Color* img) {
    //Switching between left and right sides
    if (emy->plr.rec.x < 5) {
        emy->plr.rec.x = 595;
    }

    if (emy->plr.rec.x > 595) {
        emy->plr.rec.x = 5;
    }

    switch (emy->plr.dir) {
        case UP:
            if (!checkPoint(emy->plr.rec.x, emy->plr.rec.y-1, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = UP;
            }
            break;

        case DOWN:
            if (!checkPoint(emy->plr.rec.x, emy->plr.rec.y+20, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = DOWN;
            }
            break;

        case RIGHT:
            if (!checkPoint(emy->plr.rec.x+20, emy->plr.rec.y, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = RIGHT;
            }
            break;

        case LEFT:
            if (!checkPoint(emy->plr.rec.x-1, emy->plr.rec.y, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = LEFT;
            }
            break;

        case NONE:
            break;
    }
}

//Movement for enemies
void moveEnemy(Enemy* emy) {
    switch (emy->plr.dir) {
        case UP:
            emy->plr.rec.y--;
            break;

        case DOWN:
            emy->plr.rec.y++;
            break;

        case RIGHT:
            emy->plr.rec.x++;
            break;

        case LEFT:
            emy->plr.rec.x--;
            break;

        case NONE:
            break;
    }
}

void handleRed(Enemy* emy, Player* plr, Color* img, bool* init) {
    pathfind(emy, plr->rec.x, plr->rec.y, img);
    checkEnemyMove(emy, img);
    moveEnemy(emy);
}

void handlePink(Enemy* emy, Player* plr, Color* img, bool* init) {
    if (*init &&
        emy->plr.rec.y >= 220 &&
        emy->plr.rec.y <= 320) 
        {
        if (emy->plr.rec.y == 220) {
            *init = false;
            pathfind(emy, plr->rec.x, plr->rec.y, img);
        }
        else {
            emy->plr.rec.y--;
        }
    }
    else {
        switch (plr->dir) {
            case UP:
                pathfind(emy, plr->rec.x, plr->rec.y - 20, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;

            case DOWN:
                pathfind(emy, plr->rec.x, plr->rec.y + 20, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;

            case LEFT:
                pathfind(emy, plr->rec.x + 20, plr->rec.y, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;

            case RIGHT:
                pathfind(emy, plr->rec.x - 20, plr->rec.y, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;
            
            case NONE:
                break;
        }
    }
}

void handleBlue(Enemy* emy, Enemy* red, Player* plr, Color* img, bool* init) {
    if (*init) {
        if (emy->plr.rec.x == 290) {
            if (emy->plr.rec.y == 220) {
                *init = false;
                pathfind(emy, plr->rec.x, plr->rec.y, img);
            } else emy->plr.rec.y--;
        } else emy->plr.rec.x++;
    }
    else {
        double celX = 0, celY = 0;
        double twoTileX = 0, twoTileY = 0;

        switch(plr->dir) {
            case UP:
                twoTileX = plr->rec.x;
                twoTileY = plr->rec.y - 20;
                celX = red->plr.rec.x + ((twoTileX - red->plr.rec.x) * 2);
                celY = red->plr.rec.y + ((twoTileY - red->plr.rec.y) * 2);
                break;

            case DOWN:
                twoTileX = plr->rec.x;
                twoTileY = plr->rec.y + 20;
                celX = red->plr.rec.x + ((twoTileX - red->plr.rec.x) * 2);
                celY = red->plr.rec.y + ((twoTileY - red->plr.rec.y) * 2);
                break;

            case LEFT:
                twoTileX = plr->rec.x - 20;
                twoTileY = plr->rec.y;
                celX = red->plr.rec.x + ((twoTileX - red->plr.rec.x) * 2);
                celY = red->plr.rec.y + ((twoTileY - red->plr.rec.y) * 2);
                break;

            case RIGHT:
                twoTileX = plr->rec.x + 20;
                twoTileY = plr->rec.y;
                celX = red->plr.rec.x + ((twoTileX - red->plr.rec.x) * 2);
                celY = red->plr.rec.y + ((twoTileY - red->plr.rec.y) * 2);
                break;

            case NONE:
                break;
        }

        pathfind(emy, celX, celY, img);
        checkEnemyMove(emy, img);
        moveEnemy(emy);
    }
}

void handleOrange(Enemy* emy, Player* plr, Color* img, bool* init) {
    if (*init) {
        if (emy->plr.rec.x == 290) {
            if (emy->plr.rec.y == 220) {
                *init = false;
                pathfind(emy, plr->rec.x, plr->rec.y, img);
            } else emy->plr.rec.y--;
        } else emy->plr.rec.x--;
    }
    else {
        if (distance(emy->plr.rec.x, emy->plr.rec.y, plr->rec.x, plr->rec.y) > 80) {
            pathfind(emy, plr->rec.x, plr->rec.y, img);
            checkEnemyMove(emy, img);
            moveEnemy(emy);
        }
        else {
            pathfind(emy, 290, 220, img);
            checkEnemyMove(emy, img);
            moveEnemy(emy);
        }
    }
}

bool checkDeath(Enemies* emys, Player* plr) {
    if        (CheckCollisionRecs(emys->blue.plr.rec, plr->rec)) {
        return true;
    } else if (CheckCollisionRecs(emys->red.plr.rec, plr->rec)) {
        return true;
    } else if (CheckCollisionRecs(emys->orange.plr.rec, plr->rec)) {
        return true;
    } else if (CheckCollisionRecs(emys->pink.plr.rec, plr->rec)) {
        return true;
    }
    return false;
}
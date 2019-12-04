#include "raylib.h"
#include "main.h"
#include "player.h"
#include "enemies.h"
#include "pont.h"
#include <math.h>
#include <stdio.h>

#include "debugmalloc.h"

//Szellemek lehetseges iranyainak megadasa
void getPossibleDir(Enemy* emy, Color* img) {
    if (checkPont(emy->plr.rec.x, emy->plr.rec.y + 20, img) && checkPont(emy->plr.rec.x + 19, emy->plr.rec.y + 20, img)) {
        emy->pDir.d = true;
    } else emy->pDir.d = false;

    if (checkPont(emy->plr.rec.x, emy->plr.rec.y - 1, img) && checkPont(emy->plr.rec.x + 19, emy->plr.rec.y - 1, img)) {
        emy->pDir.u = true;
    } else emy->pDir.u = false;

    if (checkPont(emy->plr.rec.x - 1, emy->plr.rec.y, img) && checkPont(emy->plr.rec.x - 1, emy->plr.rec.y + 19, img)) {
        emy->pDir.l = true;;
    } else emy->pDir.l = false;

    if (checkPont(emy->plr.rec.x + 20, emy->plr.rec.y, img) && checkPont(emy->plr.rec.x + 20, emy->plr.rec.y + 19, img)) {
        emy->pDir.r = true;
    } else emy->pDir.r = false;
}

//Ket pont kozotti tavolsag kiszamitasa
int tavSzamit(int kezdetX, int kezdetY, int celX, int celY) {
    return (int) sqrt(pow(celX - kezdetX, 2) + pow(celY - kezdetY, 2));
}

//Legrovidebb uthoz valo irany kivalasztasa
Dir tavMin(PossibleDir pDir, Tavolsag tav) {
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

void utvalaszt(Enemy* emy, int celX, int celY, Color* img) {
    getPossibleDir(emy, img);
    Tavolsag tav = {-1, -1, -1, -1};
    
    tav.down = tavSzamit(emy->plr.rec.x, emy->plr.rec.y + 20, celX, celY);
    
    tav.up = tavSzamit(emy->plr.rec.x, emy->plr.rec.y - 20, celX, celY);
    
    tav.left = tavSzamit(emy->plr.rec.x - 20, emy->plr.rec.y, celX, celY);
    
    tav.right = tavSzamit(emy->plr.rec.x + 20, emy->plr.rec.y, celX, celY);

    Dir min = tavMin(emy->pDir, tav);
    
    if (min != NONE && emy->plr.lastDir != min) {
        emy->plr.lastDir = emy->plr.dir;
        emy->plr.dir = min;
    }
}

//Szellemek mozgasanak ellenorzese
void checkEnemyMove(Enemy* emy, Color* img) {
    //Bal es jobb oldalt valo valtas
    if (emy->plr.rec.x < 5) {
        emy->plr.rec.x = 595;
    }

    if (emy->plr.rec.x > 595) {
        emy->plr.rec.x = 5;
    }

    switch (emy->plr.dir) {
        case UP:
            if (!checkPont(emy->plr.rec.x, emy->plr.rec.y-1, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = UP;
            }
            break;

        case DOWN:
            if (!checkPont(emy->plr.rec.x, emy->plr.rec.y+20, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = DOWN;
            }
            break;

        case RIGHT:
            if (!checkPont(emy->plr.rec.x+20, emy->plr.rec.y, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = RIGHT;
            }
            break;

        case LEFT:
            if (!checkPont(emy->plr.rec.x-1, emy->plr.rec.y, img)) {
                emy->plr.dir = NONE;
                emy->plr.lastDir = LEFT;
            }
            break;

        case NONE:
            break;
    }
}

//Szellemek mozgatasa
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

//Egyszeruen a jatekos fele probal haladni
void handleRed(Enemy* emy, Player* plr, Color* img, bool* init) {
    utvalaszt(emy, plr->rec.x, plr->rec.y, img);
    checkEnemyMove(emy, img);
    moveEnemy(emy);
}

//ELoszor kijut a szellemdobozbol, majd a jatekos ele probal haladni
void handlePink(Enemy* emy, Player* plr, Color* img, bool* init) {
    if (*init &&
        emy->plr.rec.y >= 220 &&
        emy->plr.rec.y <= 320) 
        {
        if (emy->plr.rec.y == 220) {
            *init = false;
            utvalaszt(emy, plr->rec.x, plr->rec.y, img);
        }
        else {
            emy->plr.rec.y--;
        }
    }
    else {
        switch (plr->dir) {
            case UP:
                utvalaszt(emy, plr->rec.x, plr->rec.y - 20, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;

            case DOWN:
                utvalaszt(emy, plr->rec.x, plr->rec.y + 20, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;

            case LEFT:
                utvalaszt(emy, plr->rec.x + 20, plr->rec.y, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;

            case RIGHT:
                utvalaszt(emy, plr->rec.x - 20, plr->rec.y, img);
                checkEnemyMove(emy, img);
                moveEnemy(emy);
                break;
            
            case NONE:
                break;
        }
    }
}

//ELoszor kijut a szellemdobozbol, majd huz egy egyenest a piros szellem poziciojatol
//a jatekos ele, azt megkettozi, es oda tart
//Ezaltal ahogy a piros kozelebb jut a jatekoshoz, a kek is egyre kozelebb lesz hozza
void handleBlue(Enemy* emy, Enemy* red, Player* plr, Color* img, bool* init) {
    if (*init) {
        if (emy->plr.rec.x == 290) {
            if (emy->plr.rec.y == 220) {
                *init = false;
                utvalaszt(emy, plr->rec.x, plr->rec.y, img);
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

        utvalaszt(emy, celX, celY, img);
        checkEnemyMove(emy, img);
        moveEnemy(emy);
    }
}

//Eloszor kijut a szellemdobozbol, majd attol fuggoen, hogy kozel vagy messze van a jatekostol:
// - ha kozel van: menekul vissza a palya kozepere
// - ha messze van: a jatekos fele tart
void handleOrange(Enemy* emy, Player* plr, Color* img, bool* init) {
    if (*init) {
        if (emy->plr.rec.x == 290) {
            if (emy->plr.rec.y == 220) {
                *init = false;
                utvalaszt(emy, plr->rec.x, plr->rec.y, img);
            } else emy->plr.rec.y--;
        } else emy->plr.rec.x--;
    }
    else {
        if (tavSzamit(emy->plr.rec.x, emy->plr.rec.y, plr->rec.x, plr->rec.y) > 80) {
            utvalaszt(emy, plr->rec.x, plr->rec.y, img);
            checkEnemyMove(emy, img);
            moveEnemy(emy);
        }
        else {
            utvalaszt(emy, 290, 220, img);
            checkEnemyMove(emy, img);
            moveEnemy(emy);
        }
    }
}

//Halal ellenorzese
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
#include "raylib.h"
#include "main.h"
#include "pont.h"
#include "render.h"
#include <stdlib.h>

#include "debugmalloc.h"

//Bemenet kezelese
void checkInput(Player* plr, Color* img) {
    if (IsKeyDown(KEY_LEFT)) {
        plr->nextDir = LEFT;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        plr->nextDir = RIGHT;
    }
    else if (IsKeyDown(KEY_UP)) {
        plr->nextDir = UP;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        plr->nextDir = DOWN;
    }
}

//Jatekos iranyanak frissitese
void updateDir(Player* plr, Color* img) {
    switch (plr->nextDir) {
        case DOWN:
            if (checkPont(plr->rec.x, plr->rec.y+20, img) && checkPont(plr->rec.x+19, plr->rec.y+20, img)) {
                plr->dir = DOWN;
                plr->nextDir = NONE;
            }
            break;

        case UP:
            if (checkPont(plr->rec.x, plr->rec.y-1, img) && checkPont(plr->rec.x+19, plr->rec.y-1, img)) {
                plr->dir = UP;
                plr->nextDir = NONE;
            }
            break;

        case LEFT:
            if (checkPont(plr->rec.x-1, plr->rec.y, img) && checkPont(plr->rec.x-1, plr->rec.y+19, img)) {
                plr->dir = LEFT;
                plr->nextDir = NONE;
            }
            break;

        case RIGHT:
            if (checkPont(plr->rec.x+20, plr->rec.y, img) && checkPont(plr->rec.x+20, plr->rec.y+19, img)) {
                plr->dir = RIGHT;
                plr->nextDir = NONE;
            }
            break;

        case NONE:
            break;
    }
}

//Jatekos mozgasanak kezelese
void checkMove(Player* plr, Color* img) {
    if (plr->rec.x < 5) {
        plr->rec.x = 595;
    }

    if (plr->rec.x > 595) {
        plr->rec.x = 5;
    }

    switch (plr->dir) {
        case UP:
            if (!checkPont(plr->rec.x, plr->rec.y-1, img)) {
                plr->dir = NONE;
                plr->lastDir = UP;
            }
            break;

        case DOWN:
            if (!checkPont(plr->rec.x, plr->rec.y+20, img)) {
                plr->dir = NONE;
                plr->lastDir = DOWN;
            }
            break;

        case RIGHT:
            if (!checkPont(plr->rec.x+20, plr->rec.y, img)) {
                plr->dir = NONE;
                plr->lastDir = RIGHT;
            }
            break;

        case LEFT:
            if (!checkPont(plr->rec.x-1, plr->rec.y, img)) {
                plr->dir = NONE;
                plr->lastDir = LEFT;
            }
            break;

        case NONE:
            break;
    }
}

//Jatekos mozgatasa
void move(Player* plr) {
    switch (plr->dir) {
        case UP:
            plr->rec.y--;
            break;

        case DOWN:
            plr->rec.y++;
            break;

        case RIGHT:
            plr->rec.x++;
            break;

        case LEFT:
            plr->rec.x--;
            break;

        case NONE:
            break;
    }
}

//Pac-man figura forgatasa - meg nem mukodik
float getRotation(Player* plr) {
    switch (plr->dir) {
        case DOWN:
            return 90.0f;
            break;

        case UP:
            return 270.0f;
            break;

        case LEFT:
            return 180.0f;
            break;

        case RIGHT:
            return 0.0f;
            break;

        case NONE:
            switch (plr->lastDir) {
                case DOWN:
                    return 90.0f;

                case UP:
                    return 270.0f;

                case LEFT:
                    return 180.0f;

                case RIGHT:
                    return 0.0f;

                case NONE:
                    return 0.0f;

                default:
                    return 0.0f;
            }
            break;

        default:
            return 0.0f;
            break;
    }
}

//Jatekos kezelese
void handlePlayer(Player* plr, Color* img, Texture2D* pacman) {
    checkInput(plr, img);
    updateDir(plr, img);
    checkMove(plr, img);
    move(plr);

    drawPacman(plr, pacman);
}
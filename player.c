#include "raylib.h"
#include "main.h"
#include "point.h"
#include "render.h"
#include <stdlib.h>

//Handle input
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

//Update player direction
void updateDir(Player* plr, Color* img) {
    switch (plr->nextDir) {
        case DOWN:
            if (checkPoint(plr->rec.x, plr->rec.y+20, img) && checkPoint(plr->rec.x+19, plr->rec.y+20, img)) {
                plr->dir = DOWN;
                plr->nextDir = NONE;
            }
            break;

        case UP:
            if (checkPoint(plr->rec.x, plr->rec.y-1, img) && checkPoint(plr->rec.x+19, plr->rec.y-1, img)) {
                plr->dir = UP;
                plr->nextDir = NONE;
            }
            break;

        case LEFT:
            if (checkPoint(plr->rec.x-1, plr->rec.y, img) && checkPoint(plr->rec.x-1, plr->rec.y+19, img)) {
                plr->dir = LEFT;
                plr->nextDir = NONE;
            }
            break;

        case RIGHT:
            if (checkPoint(plr->rec.x+20, plr->rec.y, img) && checkPoint(plr->rec.x+20, plr->rec.y+19, img)) {
                plr->dir = RIGHT;
                plr->nextDir = NONE;
            }
            break;

        case NONE:
            break;
    }
}

//Handle player movement
void checkMove(Player* plr, Color* img) {
    if (plr->rec.x < 5) {
        plr->rec.x = 595;
    }

    if (plr->rec.x > 595) {
        plr->rec.x = 5;
    }

    switch (plr->dir) {
        case UP:
            if (!checkPoint(plr->rec.x, plr->rec.y-1, img)) {
                plr->dir = NONE;
                plr->lastDir = UP;
            }
            break;

        case DOWN:
            if (!checkPoint(plr->rec.x, plr->rec.y+20, img)) {
                plr->dir = NONE;
                plr->lastDir = DOWN;
            }
            break;

        case RIGHT:
            if (!checkPoint(plr->rec.x+20, plr->rec.y, img)) {
                plr->dir = NONE;
                plr->lastDir = RIGHT;
            }
            break;

        case LEFT:
            if (!checkPoint(plr->rec.x-1, plr->rec.y, img)) {
                plr->dir = NONE;
                plr->lastDir = LEFT;
            }
            break;

        case NONE:
            break;
    }
}

//Move player
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

void handlePlayer(Player* plr, Color* img, Texture2D* pacman) {
    checkInput(plr, img);
    updateDir(plr, img);
    checkMove(plr, img);
    move(plr);

    drawPacman(plr, pacman);
}
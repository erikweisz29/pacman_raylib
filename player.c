#include "raylib.h"
#include "main.h"
#include "pont.h"
#include <stdlib.h>

bool animating = false;
bool inputActive = true;

void inputLock() {
    inputActive = false;
}

void inputUnlock(Player* plr) {
    inputActive = true;
    plr->movex = 0;
    plr->movey = 0;
}

bool checkInput(Player* plr) {
    if (IsKeyDown(KEY_LEFT)) {
        plr->angle = 180;
        plr->movex = -10;
        return true;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        plr->angle = 0;
        plr->movex = 10;
        return true;
    }
    else if (IsKeyDown(KEY_UP)) {
        plr->angle = 90;
        plr->movey = -10;
        return true;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        plr->angle = 270;
        plr->movey = 10;
        return true;
    }
    return false;
}

void checkMovePoint(Player* plr, Color* img) {
    if (plr->x+plr->movex < 0) plr->x += 600;
    if (plr->x+plr->movex > 600) plr->x -= 600;

    if (!checkPont(plr->x + plr->movex, plr->y + plr->movey, img)) {
        plr->movex = 0;
        plr->movey = 0;
    }
}

void handlePlayer(Player* plr, double* drawx, double* drawy, int* counter, Color* img) {
    if (!animating && checkInput(plr) && inputActive) {
        checkMovePoint(plr, img);
        *counter = 0;
        animating = true;
    }
    inputLock();
    DrawRectangle(*drawx-5, *drawy-5, 10, 10, YELLOW);
    if (plr->movex > 0) {
        *drawx = *drawx + 0.2;
    }
    else if (plr->movex < 0) {
        *drawx = *drawx - 0.2;
    }

    if (plr->movey > 0) {
        *drawy = *drawy + 0.2;
    }

    else if (plr->movey < 0) {
        *drawy = *drawy - 0.2;
    }

    *counter = *counter + 1;

    if (*counter == 20) {
        animating = false;
        inputUnlock(plr);
    }
}
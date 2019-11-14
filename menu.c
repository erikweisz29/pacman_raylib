#include "raylib.h"
#include "render.h"
#include "main.h"

static const int screenWidth = 600;
static const int screenHeight = 581;

bool HandleMenu(int menustate) {
    const Rectangle play = {screenWidth/2 - 225, screenHeight/2 - 175, 450, 60};
    drawMenu(menustate);

    if (CheckCollisionPointRec(GetMousePosition(), play)) {
        if (IsMouseButtonPressed(0)) {
            return true;
        }
    }

    return false;
}
#include "raylib.h"
#include "main.h"

static const int screenWidth = 600;
static const int screenHeight = 581;

void renderBackground(int gamestate) {
    Texture2D bg = LoadTexture("movemap.png");
    DrawTexture(bg, 0, 0, WHITE);

    if (gamestate == 0) {
        DrawRectangle(0, 0, screenWidth, screenHeight, CLITERAL{0, 0, 0, 150});
    }
}

void drawMenu(int menustate) {
    if (menustate == 0) {
        DrawRectangleGradientV(screenWidth/2 - 225, screenHeight/2 - 175, 450, 60, WHITE, BLANK);
        DrawText("PLAY", screenWidth/2 - MeasureText("PLAY", 36)/2, screenHeight/2 - 160, 36, WHITE);
    } 
}

void drawPont(Pont** pontok) {
    for (int i = 0; i < screenWidth/20; i++) {
        for (int j = 0; j < screenHeight/20; j++) {
            if (pontok[j][i].van) {
                DrawRectangle(pontok[j][i].x, pontok[j][i].y, 5, 5, YELLOW);
            }
        }
    }
}
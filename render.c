#include "raylib.h"
#include "main.h"
#include "player.h"
#include "pont.h"
#include "enemies.h"

#include "debugmalloc.h"

static const int screenWidth = 600;
static const int screenHeight = 581;

void renderBackground(int gamestate, Texture2D* bg) {
    DrawTexture(*bg, 0, 0, WHITE);

    if (gamestate == 0) {
        DrawRectangle(0, 0, screenWidth, screenHeight, (Color) {0, 0, 0, 150});
    }
}

void drawMenu(int menustate, bool debug) {
    if (menustate == 0) {
        DrawRectangleGradientV(screenWidth/2 - 225, screenHeight/2 - 175, 450, 60, WHITE, BLANK);
        DrawText("PLAY", screenWidth/2 - MeasureText("PLAY", 36)/2, screenHeight/2 - 160, 36, WHITE);
    }
    DrawRectangleLines(10, 10, 20, 20, WHITE);
    if (debug) DrawText("X", 15, 12, 18, WHITE);

    DrawText("Debug", 40, 10, 22, WHITE);
}

void drawPont(Pont** pontok) {
    for (int i = 0; i < screenWidth/20; i++) {
        for (int j = 0; j < screenHeight/20; j++) {
            if (pontok[j][i].van) {
                DrawRectangleRec(pontok[j][i].rect, (Color) {240, 240, 214, 200});
            }
        }
    }
}

void getPlusXY(Player* plr, bool* plusX, bool* plusY) {
    switch (plr->dir) {
        case DOWN:
            *plusX = true;
            *plusY = false;
            break;

        case UP:
            *plusX = false;
            *plusY = true;
            break;

        case LEFT:
            *plusX = true;
            *plusY = true;
            break;

        case RIGHT:
            *plusX = false;
            *plusY = false;
            break;

        case NONE:
            switch (plr->lastDir)
            {
            case DOWN:
                *plusX = true;
                *plusY = false;
                break;

            case UP:
                *plusX = false;
                *plusY = true;
                break;

            case LEFT:
                *plusX = true;
                *plusY = true;
                break;

            case RIGHT:
                *plusX = false;
                *plusY = false;
                break;

            case NONE:
                *plusX = false;
                *plusY = false;
                break;
            }
            break;
    }
}

void drawPacman(Player* plr, Texture2D* pacman) {
    bool plusX = false, plusY = false;
    getPlusXY(plr, &plusX, &plusY);
    DrawTextureEx(*pacman, (Vector2) {plr->rec.x + ((plusX) ? 20:0), plr->rec.y + ((plusY) ? 20:0)}, getRotation(plr), 1.0f, WHITE);
}

void drawEnemies(Enemies* emys, Texture2D textureArr[4][5]) {
    DrawTextureEx(textureArr[0][emys->red.plr.dir], (Vector2){emys->red.plr.rec.x, emys->red.plr.rec.y}, 0.0f, 0.125f, WHITE);
    DrawTextureEx(textureArr[1][emys->blue.plr.dir], (Vector2){emys->blue.plr.rec.x, emys->blue.plr.rec.y}, 0.0f, 0.125f, WHITE);
    DrawTextureEx(textureArr[2][emys->pink.plr.dir], (Vector2){emys->pink.plr.rec.x, emys->pink.plr.rec.y}, 0.0f, 0.125f, WHITE);
    DrawTextureEx(textureArr[3][emys->orange.plr.dir], (Vector2){emys->orange.plr.rec.x, emys->orange.plr.rec.y}, 0.0f, 0.125f, WHITE);
}
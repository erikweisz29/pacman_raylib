#include "raylib.h"
#include "pont.h"
#include "menu.h"
#include "render.h"
#include "main.h"
#include "player.h"
#include <stdio.h>

int main() {
    const int width = 600;
    const int height = 581;

    enum GameState gamestate = MENU;
    enum MenuState menustate = IDLE;

    //Pont** pontok;

    Image img = LoadImage("movemap.png");
    Color* pixels = GetImageData(img);

    Player plr = {300, 550, 0, 0, 0};
    double drawx = 300, drawy = 550;
    int counter = 0;

    InitWindow(width, height, "PacMan");

    SetTargetFPS(50);

    while (!WindowShouldClose()) {
        BeginDrawing();
        switch (gamestate) {
            case MENU:
                ClearBackground(WHITE);
                renderBackground(0);

                if (HandleMenu(menustate)) {
                    gamestate = GAME;
                    //pontok = initPont();
                    DrawText("Points drawn", 10, 10, 20, WHITE);
                }
                break;
            case GAME:
                ClearBackground(WHITE);
                renderBackground(1);
                //drawPont(pontok);
                handlePlayer(&plr, &drawx, &drawy, &counter, pixels);
                break;
            case SCOREBOARD:
                break;
        }
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}
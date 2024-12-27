#include "raylib.h"
#include "point.h"
#include "menu.h"
#include "render.h"
#include "main.h"
#include "player.h"
#include "enemies.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int screenWidth = 600;
int screenHeight = 581;

char* resultsPath = "results.pac";

int main() {
    //Window size
    const int width = 600;
    const int height = 700;

    //Initialize window, set target FPS
    InitWindow(width, height, "PacMan");
    SetTargetFPS(60);

    //To handle game state
    enum GameState gamestate = MENU;
    enum MenuState menustate = IDLE;
    enum GameEnd gameend;
    bool debug = false;

    Point** points;

    //Data for player movement
    Image playerMovementImage = LoadImage("img/maps/movemap.png");
    Color* playerMovementPixels = LoadImageColors(playerMovementImage);

    Rectangle playerHitbox = {300, 540, 20, 20};

    //Initial state for player
    Player plr = {playerHitbox, LEFT, NONE, NONE};
    int playerAnimationCounter = 0;

    //Data for enemy movement
    Image movemapEnemyImg = LoadImage("img/maps/movemap2.png");
    Color* movemapEnemy = LoadImageColors(movemapEnemyImg);

    Enemies emys;

    Rectangle recRed = {290, 220, 20, 20};
    emys.red = (Enemy) {(Player) {recRed, NONE, NONE}, (PossibleDir) {false, false, false, false}};
    bool initRed = true;

    Rectangle recPink = {290, 280, 20, 20};
    emys.pink = (Enemy){(Player){recPink, NONE, NONE}, (PossibleDir){false, false, false, false}};
    bool initPink = true;

    Rectangle recOrange = {340, 280, 20, 20};
    emys.orange = (Enemy){(Player){recOrange, NONE, NONE}, (PossibleDir){false, false, false, false}};
    bool initOrange = true;

    Rectangle recBlue = {240, 280, 20, 20};
    emys.blue = (Enemy){(Player){recBlue, NONE, NONE}, (PossibleDir){false, false, false, false}};
    bool initBlue = true;

    //Player score
    int score = 0;
    
    Result result[5];
    FILE* file = fopen(resultsPath, "r");

    //Read previous results from file
    for (int i = 0; i < 5; i++) {
        char szoveg[10];
        if (fgets(szoveg, 10, file) != NULL) {
            char* ptr;
            result[i].name = malloc(4 * sizeof(char));
            strncpy(result[i].name, szoveg, 3);
            result[i].name[3] = '\0';
            result[i].score = strtol(szoveg + 4, &ptr, 0);
        }
        else {
            result[i].name = NULL;
            result[i].score = -1;
        }
    }

    fclose(file);

    //Load background, player, enemies
    Texture2D bg = LoadTexture("img/maps/colourmap.png"),       //background
              bg_debug = LoadTexture("img/maps/movemap.png"),
              *bg_used = &bg;

    Texture2D pacman = LoadTexture("img/pacman/pacman.png"),    //1. frame
              pacman2 = LoadTexture("img/pacman/pacman2.png"),  //2.
              pacman3 = LoadTexture("img/pacman/pacman3.png"),  //3.
              *current = &pacman;                               //pointer to current frame

    //Load enemy textures into a single datastructure
    Texture2D textureArr[4][5];

    //red = 0
    textureArr[0][UP] = LoadTexture("img/enemies/red/redUp.png");
    textureArr[0][DOWN] = LoadTexture("img/enemies/red/redDown.png");
    textureArr[0][LEFT] = LoadTexture("img/enemies/red/redLeft.png");
    textureArr[0][RIGHT] = LoadTexture("img/enemies/red/redRight.png");
    textureArr[0][NONE] = LoadTexture("img/enemies/red/redUp.png");

    //blue = 1
    textureArr[1][UP] = LoadTexture("img/enemies/blue/blueUp.png");
    textureArr[1][DOWN] = LoadTexture("img/enemies/blue/blueDown.png");
    textureArr[1][LEFT] = LoadTexture("img/enemies/blue/blueLeft.png");
    textureArr[1][RIGHT] = LoadTexture("img/enemies/blue/blueRight.png");
    textureArr[1][NONE] = LoadTexture("img/enemies/blue/blueUp.png");

    //pink = 2
    textureArr[2][UP] = LoadTexture("img/enemies/pink/pinkUp.png");
    textureArr[2][DOWN] = LoadTexture("img/enemies/pink/pinkDown.png");
    textureArr[2][LEFT] = LoadTexture("img/enemies/pink/pinkLeft.png");
    textureArr[2][RIGHT] = LoadTexture("img/enemies/pink/pinkRight.png");
    textureArr[2][NONE] = LoadTexture("img/enemies/pink/pinkUp.png");

    //orange = 3
    textureArr[3][UP] = LoadTexture("img/enemies/orange/orangeUp.png");
    textureArr[3][DOWN] = LoadTexture("img/enemies/orange/orangeDown.png");
    textureArr[3][LEFT] = LoadTexture("img/enemies/orange/orangeLeft.png");
    textureArr[3][RIGHT] = LoadTexture("img/enemies/orange/orangeRight.png");
    textureArr[3][NONE] = LoadTexture("img/enemies/orange/orangeUp.png");

    bool plusX = false,
         plusY = false;

    //Game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        switch (gamestate) {
            case MENU:
                ClearBackground(BLACK);
                renderBackground(0, &bg);                       //render background, 0 = dark

                if (handleMenu(menustate, &debug)) {            //true if "play" was clicked
                    gamestate = GAME;
                    initPoint(&points);                         //initialize points

                    if (debug) bg_used = &bg_debug;
                }
                break;
            case GAME:
                ClearBackground(BLACK);
                renderBackground(1, bg_used);                   //render background, 1 = normal
                drawPont(points);
                if (plr.dir != NONE) {
                    playerAnimationCounter++;                   //increment counter for animation
                }
                switch (playerAnimationCounter) {               //next frame every 10 real frames
                    case 10:
                        current = &pacman;
                        break;
                    
                    case 20:
                        current = &pacman2;
                        break;

                    case 30:
                        current = &pacman3;
                        break;

                    case 40:
                        current = &pacman;
                        break;

                    case 50:
                        current = &pacman2;
                        break;

                    case 60:
                        current = &pacman3;
                        playerAnimationCounter = 0;
                        break;
                }

                //Handle player
                handlePlayer(&plr, playerMovementPixels, current);

                //Handle enemies
                if (playerAnimationCounter % 4 != 0) {                             //this makes enemy speed 75% of the player's speed
                    handleRed(&(emys.red), &plr, movemapEnemy, &initRed);
                    handlePink(&(emys.pink), &plr, movemapEnemy, &initPink);
                    handleBlue(&(emys.blue), &(emys.red), &plr, movemapEnemy, &initBlue);
                    handleOrange(&(emys.orange), &plr, movemapEnemy, &initOrange);
                }
                drawEnemies(&emys, textureArr);

                //Calculate svore
                handlePoints(&plr, points, &score);

                //Draw score
                char text[5];
                sprintf(text, "%d", score);
                DrawText("Score:", 20, 590, 36, WHITE);
                DrawText(text, 20, 640, 48, WHITE);
                getPlusXY(&plr, &plusX, &plusY);
                DrawTextureEx(*current, (Vector2) {475 + ((plusX) ? 100:0), 590 + ((plusY) ? 100:0)}, getRotation(&plr), 5.0f, WHITE);

                //Check death
                if (checkDeath(&emys, &plr)) {
                    gamestate = SCOREBOARD;
                    gameend = LOSE;
                }
                else if (score == 2380) {                           //2380 = maximum score,
                    gamestate = SCOREBOARD;                         //go to scoreboard
                    gameend = WIN;
                }
                break;
            case SCOREBOARD:
                handleScoreboard(gameend, score, bg_used, result);
                break;
        }
        EndDrawing();
    }
    CloseWindow();
    
    //Free points datastructure
    for (int y = 0; y < 29; ++y)
        free(points[y]);
    free(points);

    //Free scoreboard datastructure
    for (int i = 0; i < 5; i++) {
        free(result[i].name);
    }

    return 0;
}
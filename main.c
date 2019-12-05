#include "raylib.h"
#include "pont.h"
#include "menu.h"
#include "render.h"
#include "main.h"
#include "player.h"
#include "enemies.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debugmalloc.h"

int main() {
    //Ablak merete
    const int width = 600;                                      //kepernyo merete
    const int height = 700;                                     //

    //Ablak inicializalasa, cel FPS beallitasa
    InitWindow(width, height, "PacMan");
    SetTargetFPS(60);

    //Jatekallapot kezelesehez
    enum GameState gamestate = MENU;                            //alapallapotok
    enum MenuState menustate = IDLE;
    enum GameEnd gameend;
    bool debug = false;

    //Pontok
    Pont** pontok;

    //A jatekos mozgasahoz
    Image img = LoadImage("img/maps/movemap.png");                       //mozgas palyaja
    Color* pixels = GetImageData(img);                          //mozgas palyajanak pixelei

    Rectangle plrrect = {300, 540, 20, 20};                     //jatekos hitboxa
    Player plr = {plrrect, LEFT, NONE, NONE};                   //jatekos kezdeti helyzete
    int counter = 0;                                            //jatekos animaciojahoz

    //Az enemyk
    Image movemapEnemyImg = LoadImage("img/maps/movemap2.png");
    Color* movemapEnemy = GetImageData(movemapEnemyImg);

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

    //Jatekos eredmenye
    int score = 0;
    
    Eredmeny eredmeny[5];
    FILE* file = fopen("eredmeny.pac", "r");

    //Eddigi eredmenyek beolvasasa fajlbol
    for (int i = 0; i < 5; i++) {
        char szoveg[10];
        if (fgets(szoveg, 10, file) != NULL) {
            char* ptr;
            eredmeny[i].nev = malloc(4 * sizeof(char));
            strncpy(eredmeny[i].nev, szoveg, 3);
            eredmeny[i].nev[3] = '\0';
            eredmeny[i].pont = strtol(szoveg + 4, &ptr, 0);
        }
        else {
            eredmeny[i].nev = NULL;
            eredmeny[i].pont = -1;
        }
    }

    fclose(file);

    //Hatter, jatekosn, enemyk betoltese
    Texture2D bg = LoadTexture("img/maps/colourmap.png"),       //hatter
              bg_debug = LoadTexture("img/maps/movemap.png"),
              *bg_used = &bg;

    Texture2D pacman = LoadTexture("img/pacman/pacman.png"),    //elso frame
              pacman2 = LoadTexture("img/pacman/pacman2.png"),  //masodik frame
              pacman3 = LoadTexture("img/pacman/pacman3.png"),  //harmadik frame
              *current = &pacman;                               //jelenlegi frame-re mutato pointer

    //A szellemek kulonbozo texturainak betoltese, egy adatszerkezetbe
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

    //Jatek loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        switch (gamestate) {
            case MENU:
                ClearBackground(BLACK);
                renderBackground(0, &bg);                       //hatter render, 0 = sotetitett

                if (HandleMenu(menustate, &debug)) {            //akkor true, ha a play gomb meg van nyomva - lasd menu.c
                    gamestate = GAME;
                    initPont(&pontok);                          //pontok inicializalasa

                    if (debug) bg_used = &bg_debug;
                }
                break;
            case GAME:
                ClearBackground(BLACK);
                renderBackground(1, bg_used);                       //hatter render, 1 = normal
                drawPont(pontok);
                if (plr.dir != NONE) {
                    counter++;   
                }                                   //az animaciohoz szukseges szamlalo novelese
                switch (counter) {                              //10 framenkent kovetkezo frame
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
                        counter = 0;
                        break;
                }

                //Jatekos kezelese, rajzolasa a jelenlegi frammel
                handlePlayer(&plr, pixels, current);

                //Enemyk kezelese
                if (counter % 4 != 0) {                             //a szellemek sebessege emiatt 75%-a a jatekosenak
                    handleRed(&(emys.red), &plr, movemapEnemy, &initRed);
                    handlePink(&(emys.pink), &plr, movemapEnemy, &initPink);
                    handleBlue(&(emys.blue), &(emys.red), &plr, movemapEnemy, &initBlue);
                    handleOrange(&(emys.orange), &plr, movemapEnemy, &initOrange);
                }
                drawEnemies(&emys, textureArr);
                //Eredmeny szamolasa
                handlePoints(&plr, pontok, &score);

                //Eredmeny kiirasa
                char text[5];
                sprintf(text, "%d", score);
                DrawText("Score:", 20, 590, 36, WHITE);
                DrawText(text, 20, 640, 48, WHITE);
                getPlusXY(&plr, &plusX, &plusY);
                DrawTextureEx(*current, (Vector2) {475 + ((plusX) ? 100:0), 590 + ((plusY) ? 100:0)}, getRotation(&plr), 5.0f, WHITE);

                //Halal ellenorzese
                if (checkDeath(&emys, &plr)) {
                    gamestate = SCOREBOARD;
                    gameend = LOSE;
                }

                if (score == 2380) {                                //2380 = a maximum score,
                    gamestate = SCOREBOARD;                         //lepunk a scoreboardra
                    gameend = WIN;
                }
                break;
            case SCOREBOARD:
                handleScoreboard(gameend, score, bg_used, eredmeny);
                break;
        }
        EndDrawing();
    }
    CloseWindow();
    
    //Pontok szerkezetenek felszabaditasa
    for (int y = 0; y < 29; ++y)                                    //29 = a tomb magassaga
        free(pontok[y]);
    free(pontok);

    //Eredmenyek nevenek felszabaditasa
    for (int i = 0; i < 5; i++) {
        free(eredmeny[i].nev);
    }

    return 0;
}
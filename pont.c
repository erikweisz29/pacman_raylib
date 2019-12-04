#include "raylib.h"
#include "main.h"
#include <stdlib.h>

#include "debugmalloc.h"

//Kepernyo/hatter merete
static const int screenWidth = 600;

static const int szelesseg = 600/20;
static const int magassag = 581/20;

//Szinosszehasonlito fv
bool colorCmp(Color clr1, Color clr2) {
    if (clr1.b == clr2.b && clr1.g == clr2.g && clr1.r == clr2.r) {
        return true;
    }
    return false;
}

//Megnezi, hogy egy pont fekete-e egy adott kepen
bool checkPont(int x, int y, Color* img) {
    if (colorCmp(img[(y * screenWidth) + x], BLACK)) {
        return true;
    }
    return false;
}

//Pontok inicializalasa - egyelore nem mukodik
void initPont(Pont*** adatok) {
    Pont** pontok;

    Image pontmap = LoadImage("img/maps/pointmap.png");
    Color* pixels = GetImageData(pontmap);

    pontok = (Pont**) malloc(magassag * sizeof(Pont*));
    for (int i = 0; i < magassag; i++)
        pontok[i] = (Pont*) malloc(szelesseg * sizeof(Pont));

    int x = 0, y = 0;
    while (x < szelesseg) {
        y = 0;
        while (y < magassag) {
            if (checkPont((x*20)+10, (y*20)+10, pixels)) {
                pontok[y][x].rect = (Rectangle) {(x*20)+8, (y*20)+8, 5, 5};
                pontok[y][x].van = true;
            }
            y++;
        }
        x++;
    }
    *adatok = pontok;
}

void handlePoints(Player* plr, Pont** pontok, int* score) {
    //bool CheckCollisionRecs

    int x = 0, y = 0;
    while (x < szelesseg) {
        y = 0;
        while (y < magassag) {
            if (pontok[y][x].van && CheckCollisionRecs(plr->rec, pontok[y][x].rect)) {
                pontok[y][x].van = false;
                *score = *score + 10;
            }
            y++;
        }
        x++;
    }
}
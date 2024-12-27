#include "raylib.h"
#include "main.h"
#include "point.h"
#include <stdlib.h>

extern int screenWidth;

bool colorCmp(Color clr1, Color clr2) {
    if (clr1.b == clr2.b && clr1.g == clr2.g && clr1.r == clr2.r) {
        return true;
    }
    return false;
}

bool checkPoint(int x, int y, Color* img) {
    if (colorCmp(img[(y * screenWidth) + x], BLACK)) {
        return true;
    }
    return false;
}

void initPoint(Point*** data) {
    Point** points;

    Image pointmap = LoadImage("img/maps/pointmap.png");
    Color* pixels = LoadImageColors(pointmap);

    points = (Point**) malloc(height * sizeof(Point*));
    for (int i = 0; i < height; i++)
        points[i] = (Point*) malloc(width * sizeof(Point));

    int x = 0, y = 0;
    while (x < width) {
        y = 0;
        while (y < height) {
            if (checkPoint((x*20)+10, (y*20)+10, pixels)) {
                points[y][x].rect = (Rectangle) {(x*20)+8, (y*20)+8, 5, 5};
                points[y][x].has = true;
            }
            y++;
        }
        x++;
    }
    *data = points;
}

void handlePoints(Player* plr, Point** points, int* score) {
    int x = 0, y = 0;
    while (x < width) {
        y = 0;
        while (y < height) {
            if (points[y][x].has && CheckCollisionRecs(plr->rec, points[y][x].rect)) {
                points[y][x].has = false;
                *score = *score + 10;
            }
            y++;
        }
        x++;
    }
}
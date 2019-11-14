#include "raylib.h"
#include "main.h"
#include <stdlib.h>

static const int screenWidth = 600;
static const int screenHeight = 581;

bool colorCmp(Color clr1, Color clr2) {
    if (clr1.b == clr2.b && clr1.g == clr2.g && clr1.r == clr2.r && clr1.a == clr2.a) {
        return true;
    }
    return false;
}

bool checkPont(int x, int y, Color* img) {
    if (colorCmp(img[x*y], BLACK)) {
        return true;
    }
    return false;
}

Pont** initPont() {
    Image pontmap = LoadImage("pointmap.png");
    Color* pixels = GetImageData(pontmap);
    Pont** pontok = (Pont**) malloc((screenHeight/20)*sizeof(Pont*));
    pontok[0] = (Pont*) malloc((screenHeight/20)*(screenWidth/20)*sizeof(Pont));
    for (int i = 1; i < screenHeight/20; i++) {
        pontok[i] = pontok[0] + i*(screenWidth/20);
    }

    int x = 0, y = 0;
    while (x < screenWidth/20) {
        while (y < screenHeight/20) {
            if (checkPont((10+x)*20, (10+y)*20, pixels)) {
                Pont c = {(10+x)*20, (10+y)*20, true};
                pontok[y][x] = c;
            }
            y++;
        }
        x++;
    }
    return pontok;
}
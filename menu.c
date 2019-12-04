#include "raylib.h"
#include "render.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debugmalloc.h"

static const int screenWidth = 600;
static const int screenHeight = 581;

static int inputChars = 0;
static char inputChar;

static char input[4];

bool HandleMenu(int menustate, bool* pDebug) {
    const Rectangle play = {screenWidth / 2 - 225, screenHeight / 2 - 175, 450, 60};
    const Rectangle debug = {10, 10, 20, 20};

    drawMenu(menustate, *pDebug);

    //Debug jelolonegyzet kezelese
    if (CheckCollisionPointRec(GetMousePosition(), debug)) {
        if (IsMouseButtonPressed(0)) {
            *pDebug = !*pDebug;
        }
    }

    //Play gomb kezelese
    if (CheckCollisionPointRec(GetMousePosition(), play)) {
        if (IsMouseButtonPressed(0)) {
            return true;
        }
    }

    return false;
}

void listabaBeilleszt(Eredmeny eredmeny[], int score, char* nev) {
    if (score > eredmeny[4].pont) {
        int i = 4;
        while (i > 0 && score > eredmeny[i - 1].pont) {
            i--;
        }

        //Eddigi adatok shiftelese
        for (int j = 4; j > i; j--) {
            eredmeny[j].pont = eredmeny[j-1].pont;

            if (eredmeny[j-1].nev != NULL) {
                eredmeny[j].nev = (char*) malloc(10 * sizeof(char));
                strcpy(eredmeny[j].nev, eredmeny[j - 1].nev);
            }
        }

        //Uj eredmeny beillesztese
        eredmeny[i].nev = (char *) malloc(4 * sizeof(char));
        strcpy(eredmeny[i].nev, input);
        eredmeny[i].pont = score;
    }
}

void handleScoreboard(enum GameEnd gameend, int score, Texture2D* bg_used, Eredmeny eredmeny[]) {
    ClearBackground(BLACK);
    renderBackground(0, bg_used);

    char scoreText[15];
    sprintf(scoreText, "Your score: %d", score);
    DrawText(scoreText, screenWidth/2 - (MeasureText(scoreText, 36)/2), 175, 36, WHITE);

    //A 3 betu helyen levo vonalak, valamint a betuk kirajzolasa
    for (int i = 0; i < 5; i++) {
        if (eredmeny[i].nev != NULL) {
            char text[10];
            sprintf(text, "%s %d", eredmeny[i].nev, eredmeny[i].pont);
            DrawText(text, screenWidth/2 - (MeasureText(text, 20)/2), 360 + (i*30), 20, WHITE);
        }
    }

    //Szoveg beolvasasa
    if (inputChars < 3) {
        DrawText("Enter your name:", screenWidth/2 - (MeasureText("Enter your name", 48)/2), 215, 48, WHITE);
        for (int i = 0 + inputChars; i < 3; i++) {
            DrawLine(screenWidth/2 - 111 + (i*86), 300, screenWidth/2 - 111 + (i*86) + 66, 300, WHITE);
        }
        for (int i = 0; i < inputChars; i++) {
            char asd[3];
            sprintf(asd, "%c", input[i]);
            DrawText(asd, screenWidth / 2 - 111 + (i * 86) + 25, 270, 25, WHITE);
        }

        inputChar = GetKeyPressed();
        if ((inputChar >= 48 && inputChar <= 57) ||             //szam
            (inputChar >= 65 && inputChar <= 90) ||             //nagybetu
            (inputChar >= 97 && inputChar <= 122)) {            //kisbetu

            input[inputChars] = inputChar;
            inputChars++;
        }

        //Ha megvan mind a 3 karakter
        if (inputChars == 3) {
            input[3] = '\0';
            if (score > eredmeny[4].pont) {
                listabaBeilleszt(eredmeny, score, input);

                FILE* file = fopen("eredmeny.pac", "w");

                //Fajlba kiiras
                for (int i = 0; i < 5; i++) {
                    if (eredmeny[i].pont != -1) {
                        char write[10];
                        sprintf(write, "%s %d\n", eredmeny[i].nev, eredmeny[i].pont);
                        fputs(write, file);
                    }
                }
                fclose(file);
            }
        }
    }
    if (gameend == WIN) {
        DrawText("YOU WIN!", screenWidth / 2 - MeasureText("YOU WIN!", 72) / 2, 100, 72, GREEN);
    }
    else {
        DrawText("YOU LOSE!", screenWidth / 2 - MeasureText("YOU LOSE!", 72) / 2, 100, 72, RED);
    }
}
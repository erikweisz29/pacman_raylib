#include "raylib.h"
#include "render.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int screenWidth;
extern int screenHeight;
extern char* resultsPath;

static int inputChars = 0;
static char inputChar;

static char input[4];

bool handleMenu(int menustate, bool* pDebug) {
    const Rectangle play = {screenWidth / 2 - 225, screenHeight / 2 - 175, 450, 60};
    const Rectangle debug = {10, 10, 20, 20};

    drawMenu(menustate, *pDebug);

    //Handle debug checkbox
    if (CheckCollisionPointRec(GetMousePosition(), debug)) {
        if (IsMouseButtonPressed(0)) {
            *pDebug = !*pDebug;
        }
    }

    //Handle play button
    if (CheckCollisionPointRec(GetMousePosition(), play)) {
        if (IsMouseButtonPressed(0)) {
            return true;
        }
    }

    return false;
}

void addToResults(Result results[], int score, char* name) {
    if (score > results[4].score) {
        int i = 4;
        while (i > 0 && score > results[i - 1].score) {
            i--;
        }

        //Shift current scores
        for (int j = 4; j > i; j--) {
            results[j].score = results[j-1].score;

            if (results[j-1].name != NULL) {
                results[j].name = (char*) malloc(10 * sizeof(char));
                strcpy(results[j].name, results[j - 1].name);
            }
        }

        //Insert new result
        results[i].name = (char *) malloc(4 * sizeof(char));
        strcpy(results[i].name, input);
        results[i].score = score;
    }
}

void handleScoreboard(enum GameEnd gameend, int score, Texture2D* bg_used, Result results[]) {
    ClearBackground(BLACK);
    renderBackground(0, bg_used);

    char scoreText[15];
    sprintf(scoreText, "Your score: %d", score);
    DrawText(scoreText, screenWidth/2 - (MeasureText(scoreText, 36)/2), 175, 36, WHITE);

    //Draw the 3 placeholder lines, as well as the letters themselves
    for (int i = 0; i < 5; i++) {
        if (results[i].name != NULL) {
            char text[10];
            sprintf(text, "%s %d", results[i].name, results[i].score);
            DrawText(text, screenWidth/2 - (MeasureText(text, 20)/2), 360 + (i*30), 20, WHITE);
        }
    }

    //Read entered name
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
        if ((inputChar >= 48 && inputChar <= 57) ||             //number
            (inputChar >= 65 && inputChar <= 90) ||             //uppercase letter
            (inputChar >= 97 && inputChar <= 122)) {            //lowercase letter

            input[inputChars] = inputChar;
            inputChars++;
        }

        //If we have 3 characters
        if (inputChars == 3) {
            input[3] = '\0';
            if (score > results[4].score) {
                addToResults(results, score, input);

                FILE* file = fopen(resultsPath, "w");

                //Write to file
                for (int i = 0; i < 5; i++) {
                    if (results[i].score != -1) {
                        char write[10];
                        sprintf(write, "%s %d\n", results[i].name, results[i].score);
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
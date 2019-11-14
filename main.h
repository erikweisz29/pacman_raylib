#ifndef MAIN_H
#define MAIN_H

enum GameState
{
    MENU,
    GAME,
    SCOREBOARD
};

enum MenuState
{
    IDLE,
    PLAY,
    EXIT
};

extern enum GameState gamestate;
extern enum MenuState menustate;

typedef struct Pont {
    int x;
    int y;
    bool van;
} Pont;

typedef enum 
{
    UP,
    RIGHT,
    DOWN,
    LEFT
} Dir;

typedef struct Player {
    int x;
    int y;
    int angle;
    int movex;
    int movey;
} Player;

#endif
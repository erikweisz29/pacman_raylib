#ifndef MAIN_H
#define MAIN_H

//Game state enum
enum GameState
{
    MENU,
    GAME,
    SCOREBOARD
};

//Menu state enum
enum MenuState
{
    IDLE,
    PLAY,
    EXIT
};

extern enum GameState gamestate;
extern enum MenuState menustate;

enum GameEnd {
    WIN,
    LOSE
};

//Data structure for edible points
typedef struct Point {
    Rectangle rect;
    bool has;
} Point;

//Enum for directions
typedef enum 
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE
} Dir;

//Data structure for player
typedef struct Player {
    Rectangle rec;
    Dir dir;
    Dir nextDir;
    Dir lastDir;
} Player;

//Data structure for storing scoreboard data
typedef struct Result {
    char* name;
    int score;
} Result;

#endif
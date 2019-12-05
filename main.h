#ifndef MAIN_H
#define MAIN_H

//Jatekallapot kezelo
enum GameState
{
    MENU,
    GAME,
    SCOREBOARD
};

//Menuallapot kezelo
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

//Jovobeni megeheto pontok strukturaja
typedef struct Pont {
    Rectangle rect;
    bool van;
} Pont;

//Iranyok strukturaja
typedef enum 
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE
} Dir;

//Jatekos, valamint szellemek strukturaja
typedef struct Player {
    Rectangle rec;
    Dir dir;
    Dir nextDir;
    Dir lastDir;
} Player;

//Scoreboard eredmenyeinek tarolasahoz
typedef struct Eredmeny {
    char* nev;
    int pont;
} Eredmeny;

#endif
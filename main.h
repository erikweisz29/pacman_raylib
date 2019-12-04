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

//Szellemk kulonbozo texturainak tarolasahoz
typedef struct EnemiesPng {
    Texture2D redLeft;
    Texture2D redRight;
    Texture2D redUp;
    Texture2D redDown;

    Texture2D blueLeft;
    Texture2D blueRight;
    Texture2D blueUp;
    Texture2D blueDown;

    Texture2D orangeLeft;
    Texture2D orangeRight;
    Texture2D orangeUp;
    Texture2D orangeDown;

    Texture2D pinkLeft;
    Texture2D pinkRight;
    Texture2D pinkUp;
    Texture2D pinkDown;
} EnemiesPng;

//Scoreboard eredmenyeinek tarolasahoz
typedef struct Eredmeny {
    char* nev;
    int pont;
} Eredmeny;

#endif
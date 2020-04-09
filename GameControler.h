//
// Created by xieliangjing on 2020/3/5.
//

#ifndef GREEDYSNAKE_GAMECONTROLER_H
#define GREEDYSNAKE_GAMECONTROLER_H
#include "Snake.h"
#include "Food.h"
#include "Graph.h"

#define EASY 300
#define GENERAL 200
#define HARD 90

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


class GameControler{
public:
    GameControler();
    void mov_arrow(int x, int y);
    void start_interface(int &col, int &raw, int &speed);
    void game_over();
    void game();
    void pause();
    void show_info();
private:
    int state, score, mode;
    Snake snake;
    Food food;
    Graph map;
};
#endif //GREEDYSNAKE_GAMECONTROLER_H

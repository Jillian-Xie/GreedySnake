//
// Created by xieliangjing on 2020/3/5.
//

#ifndef GREEDYSNAKE_SNAKE_H
#define GREEDYSNAKE_SNAKE_H
#include <vector>
#include <windows.h>
#include <deque>
#include <iostream>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class Graph;

class Food;

using namespace std;

class Snake{
    friend class Food;
public:
    void mov_arrow(int x, int y);
    Snake():speed(200), direction(4){
        COORD my_snake = {1,1};
        snake.push_front(my_snake);
    };
    void grow_up(int length);
    void set_speed(int speed_input){ speed = speed_input;}
    void show_snake();
    int mov_forward(Graph &map, Food &food);//核心函数
private:
    int speed;
    int direction;
    deque<COORD> snake;//双端队列表示蛇体
};
#endif //GREEDYSNAKE_SNAKE_H

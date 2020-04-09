//
// Created by xieliangjing on 2020/3/5.
//
#include "Snake.h"
#include "Graph.h"
#include "Food.h"
#include <deque>
#include <conio.h>

void Snake::grow_up(int length) {
    for(int i = 0; i< length;++i){
        if(direction == UP){
            short y =(snake.begin()->Y)-1;
            COORD new_node = {snake.begin()->X, y};
            snake.push_front(new_node);
        }
        else if(direction == DOWN){
            short y =(snake.begin()->Y)+1;
            COORD new_node = {snake.begin()->X, y};
            snake.push_front(new_node);
        }
        else if(direction == LEFT){
            short x =(snake.begin()->X)-1;
            COORD new_node = {x, snake.begin()->Y};
            snake.push_front(new_node);
        }
        else if(direction == RIGHT){
            short x =(snake.begin()->X)+1;
            COORD new_node = {x, snake.begin()->Y};
            snake.push_front(new_node);
        }
        mov_arrow(snake.front().X, snake.front().Y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 'x';
    }
}

void Snake::mov_arrow(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Snake::show_snake() {
    for(int i = 0; i<snake.size(); ++i){
        mov_arrow(snake[i].X, snake[i].Y);
        cout << 'x';
    }
    return;
}

int Snake::mov_forward(Graph &map, Food &food) {
    mov_arrow(68,33);
    int key;
    while(1){
        if(food.timer != 0){
            food.timer--;
            mov_arrow(11, 33);
            for(int i = 0; i < food.timer; i++){
                cout << "=";
            }
            cout << "                   ";
            if(food.timer == 0){
                mov_arrow(10, 33);
                cout << "                                        ";//进度条
                mov_arrow(food.food_position.X, food.food_position.Y);
                cout << ' ';
                food.draw_food(map, *this);
            }
        }
        if(kbhit()) {
            key = getch();
            if (key == 'p') {
                return 1;
            } else if (key == 72 || key == 105) {//向上
                if (direction != DOWN) direction = UP;
            } else if (key == 80 || key == 107) {//向下
                if (direction != UP) direction = DOWN;
            } else if (key == 75 || key == 106) {//向左
                if (direction != RIGHT) direction = LEFT;
            } else if (key == 77 || key == 108) {//向右
                if (direction != LEFT) direction = RIGHT;
            } else if (key == 224) continue;
        }

        Sleep(speed);
        grow_up(1);
        mov_arrow(snake.back().X, snake.back().Y);
        cout << ' ';
        snake.pop_back();
        mov_arrow(68,33);//防止光标闪烁影响游戏体验
        if(snake.front().X <= 0 || snake.front().X >= map.col-1
        || snake.front().Y <= 0 || snake.front().Y >= map.raw-1
        ) return 0;//撞墙
        for(int i = 1; i < snake.size(); ++i){
            if(snake[i].X == snake.front().X && snake[i].Y == snake.front().Y)
                return 0;//撞自己
        }
        if(snake.front().X == food.food_position.X && snake.front().Y == food.food_position.Y){
            if(food.time_lim_food == false) {
                grow_up(1);
                food.draw_food(map, *this);
                return 2;
            }
            else{
                int score = 2+food.timer/6;
                food.timer = 0;
                mov_arrow(10, 33);
                cout << "                                   ";
                food.time_lim_food = 0;
                grow_up(1);
                food.draw_food(map, *this);
                return score;
            }
        }
    }
}

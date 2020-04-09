//
// Created by xieliangjing on 2020/3/6.
//

#include "Food.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

int Food::count = 0;

void mov_arrow(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Food::draw_food(Graph &map, Snake &snake) {
    srand(time(NULL));
    int flag = true, x, y;
    while (flag) {
        flag = false;
        x = rand() % (map.col - 1);
        y = rand() % (map.raw - 1);
        if (x == 0) x++;
        if (y == 0) y++;
        for (int i = 0; i < snake.snake.size(); ++i) {
            if (snake.snake[i].X == x && snake.snake[i].Y == y)
                flag = true;//如果food与蛇身重合，重新取随机数
        }
    }
    if (count == ROUND - 1) {//每5个果实产生一次限时果实
        mov_arrow(10, 33);
        cout << "|==============================|";//进度条
        timer = 30;
        time_lim_food = true;
        mov_arrow(x, y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << '0';
    } else {
        mov_arrow(x, y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << 'o';
    }
    food_position = {(short) x, (short) y};
    count = (count + 1) % ROUND;
    return;
}
//
// Created by xieliangjing on 2020/3/5.
//
#include "GameControler.h"
#include <windows.h>
#include <iostream>
#include <conio.h>


using namespace std;

GameControler::GameControler() {
    score = 0;//初始得分为0
    state = 0;//初始状态下游戏关闭
    mode = 1;//初始模式为简单
}

void GameControler::pause() {
    int temp;
    mov_arrow(0, 34);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "[Press 'c' to continue]" ;
    while(temp = getch()){
        if (temp == 'c') break;
    }
    mov_arrow(0, 34);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "[Press 'p' to pause]    " ;
    return;
}

void GameControler::show_info() {
    mov_arrow(0, 34);
    cout << "[Press 'p' to pause]" ;
    mov_arrow(45, 34);
    cout << "MODE:         SCORE:";
    mov_arrow(50,34);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    switch(mode){
        case 1: cout << "EASY";break;
        case 2: cout << "GENE";break;
        case 3: cout << "HARD";break;
    }
    mov_arrow(65,34);
    cout << score;
    return;
}

void GameControler::game_over() {
    system("CLS");
    mov_arrow(20,10);//模式选择初始界面
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "+--------------------------+" <<endl;
    mov_arrow(20,11);
    cout << "|         GAME OVER        |" << endl;//*表示该项被选中
    mov_arrow(20,12);
    cout << "|final score:              |" << endl;
    mov_arrow(20,13);
    cout << "| See you next time :)     |" << endl;
    mov_arrow(20,14);
    cout << "+--------------------------+" << endl;
    mov_arrow(34, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << score;
}

void GameControler::game() {
    int raw = 50,col = 50,speed = 200;
    start_interface(col, raw, speed);
    map.set_map(col, raw/2);
    snake.set_speed(speed);
    map.draw_map();
    show_info();
    snake.show_snake();
    food.draw_food(map,snake);
    while(state = snake.mov_forward(map, food)){
        if(state == 0) break;//游戏结束
        else if(state == 1){
            pause();
        }//游戏暂停
        else if(state >= 2){
            score += (state - 1);
            show_info();
        }//得分
    }
    game_over();
    Sleep(2700);
    return;
}

void GameControler::mov_arrow(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void GameControler::start_interface(int &col, int &raw, int &speed) {
    system("CLS");
    char a[100];
    system("color 0D");
    system("title 181860112's Little Greedy Snake");
    system("mode con cols=70 lines=35");
    mov_arrow(20,10);
    cout << "Welcome to xlj's greedy snake world!" << endl;
    mov_arrow(5, 12);
    cout << '|';
    for(int i = 0; i < 60; ++i){
        cout << ">";
        Sleep(25);
    }
    cout << '|';
    Sleep(600);
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    mov_arrow(28,10);
    cout << "INPUT MAP SIZE";//地图大小限制需要在调试后完善！
    mov_arrow(28, 12);
    cout << "RAW[10,70]:";
    cin >> raw;
    while(raw>70 || raw <10){
        cout<<"Wrong input, try again:";
        cin >> raw;
    }
    mov_arrow(28, 14);
    cout << "COL[10,64]:";
    cin >> col;
    while(col > 64 || col <10){
        cout<<"Wrong input, try again:";
        cin >> col;
    }
    system("CLS");
    mov_arrow(28,8);
    cout << "CHOOSE MODE";
    mov_arrow(20,10);//模式选择初始界面
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "+--------------------------+" <<endl;
    mov_arrow(19,11);
    cout << "*| 1.         ESAY          |" << endl;//*表示该项被选中
    mov_arrow(20,12);
    cout << "| 2.         GENERAL       |" << endl;
    mov_arrow(20,13);
    cout << "| 3.         HARD          |" << endl;
    mov_arrow(20,14);
    cout << "+--------------------------+" << endl;

    int key;//捕捉键盘输入
    while(1){
        key = getch();
        if(key == 13) break;
        else if(key == 75 || key == 72 || key == 105 || key == 106){
            switch (mode){
                case 1:
                    mov_arrow(19,11);
                    cout << " | 1.         ESAY          |" << endl;//*表示该项被选中
                    mov_arrow(19,12);
                    cout << " | 2.         GENERAL       |" << endl;
                    mov_arrow(19,13);
                    cout << "*| 3.         HARD          |" << endl;

                    mode = 3;
                    break;
                case 2:
                    mov_arrow(19,11);
                    cout << "*| 1.         ESAY          |" << endl;//*表示该项被选中
                    mov_arrow(19,12);
                    cout << " | 2.         GENERAL       |" << endl;
                    mov_arrow(19,13);
                    cout << " | 3.         HARD          |" << endl;

                    mode = 1;
                    break;
                case 3:
                    mov_arrow(19,11);
                    cout << " | 1.         ESAY          |" << endl;//*表示该项被选中
                    mov_arrow(19,12);
                    cout << "*| 2.         GENERAL       |" << endl;
                    mov_arrow(19,13);
                    cout << " | 3.         HARD          |" << endl;

                    mode = 2;
                    break;
                default:
                    break;
            }

        }//向上或向左键表示上移光标
        else if(key == 80 || key == 77 || key == 107 || key == 108){
            switch (mode){
                case 1:
                    mov_arrow(19,11);
                    cout << " | 1.         ESAY          |" << endl;//*表示该项被选中
                    mov_arrow(19,12);
                    cout << "*| 2.         GENERAL       |" << endl;
                    mov_arrow(19,13);
                    cout << " | 3.         HARD          |" << endl;

                    mode = 2;
                    break;
                case 2:
                    mov_arrow(19,11);
                    cout << " | 1.         ESAY          |" << endl;//*表示该项被选中
                    mov_arrow(19,12);
                    cout << " | 2.         GENERAL       |" << endl;
                    mov_arrow(19,13);
                    cout << "*| 3.         HARD          |" << endl;

                    mode = 3;
                    break;
                case 3:
                    mov_arrow(19,11);
                    cout << "*| 1.         ESAY          |" << endl;//*表示该项被选中
                    mov_arrow(19,12);
                    cout << " | 2.         GENERAL       |" << endl;
                    mov_arrow(19,13);
                    cout << " | 3.         HARD          |" << endl;

                    mode = 1;
                    break;
                default:
                    break;
            }
        }//向下或向右键表示下移光标
    }
    mov_arrow(col,raw);
    switch (mode){
        case 1: speed = EASY; break;
        case 2: speed = GENERAL; break;
        case 3: speed = HARD; break;
        default: break;
    }
}
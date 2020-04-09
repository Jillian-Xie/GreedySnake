//
// Created by xieliangjing on 2020/3/5.
//
#include <windows.h>
#include "Graph.h"
#include <cstdio>
#include <iostream>

using namespace std;

void Graph::mov_arrow(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Graph::set_map(int col_input, int raw_input) {
    col = col_input;
    raw = raw_input;
}
/*窗口大小是70（col)*35*/
void Graph::draw_map() {
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    mov_arrow(0,0);
    cout << '+';
    for(int i = 1; i<col-1; ++i){
        cout << '-';
    }
    cout << '+';
    for(int i = 1; i<raw-1; ++i){
        mov_arrow(0,i);
        cout << '|';
    }
    mov_arrow(0,raw-1);
    cout << '+';
    for(int i = 1;i<col-1;++i){
        cout << '-';
    }
    cout << '+';
    for(int i = 1; i<raw-1; ++i){
        mov_arrow(col-1,i);
        cout << '|';
    }
}


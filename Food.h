//
// Created by xieliangjing on 2020/3/6.
//

#ifndef GREEDYSNAKE_FOOD_H
#define GREEDYSNAKE_FOOD_H

#include "Graph.h"
#include "Snake.h"

#define ROUND 5

class Food {
friend Snake;
public:
    Food():timer(0), time_lim_food(0),food_position({0,0}){};
    void draw_food(Graph &map, Snake &snake);
    static int count;
private:
    int timer;
    bool time_lim_food;
    COORD food_position;
};


#endif //GREEDYSNAKE_FOOD_H

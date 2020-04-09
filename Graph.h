//
// Created by xieliangjing on 2020/3/5.
//
#ifndef GREEDYSNAKE_GRAPH_H
#define GREEDYSNAKE_GRAPH_H

class Graph{
    friend class Food;
    friend class Snake;
public:
    Graph():col(50), raw(25){};
    void set_map(int col_input, int raw_input);
    void draw_map();
    void mov_arrow(int x, int y);
private:
    int col, raw;
};



#endif //GREEDYSNAKE_GRAPH_H

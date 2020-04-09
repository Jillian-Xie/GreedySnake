# GreedySnake
Console version greedy snake.

### 一、使用手册

**简介: 运用面向对象的思维方法，编写的一个经典小游戏贪吃蛇的控制台版本。

**操作说明：使用方向键或 i（向上） k（向下） j（向左）l（向右）键控制蛇的移动。

​				   在游戏的任意时刻按p键暂停游戏，c键继续游戏。

​				   撞上墙体或蛇身将导致游戏失败。

​				   普通食物得分为1，特殊食物的得分为在一分的基础上加上剩余时间的五分之一。

**功能介绍 ：**

***地图界面：地图四面围墙。***

***操作要求：玩家用键盘方向键（或jkli键）控制蛇移动，每次吃掉一个食物，蛇的长度加一，并在地图上随机产生一个新食物，碰到蛇身及墙壁都会导致游戏失败。***
​                                                （其中‘x'表示蛇，紫色'o'表示普通食物）

***特殊食物：每吃掉5个普通食物后，附加多产生一个限时食物，在移动30格之后会自动消失 。***

​                                          （其中白色’0‘表示特殊食物，将在移动30步后消失）



***积分规则：普通食物每个1分，特殊食物将在一分的基础上加上剩余时间的五分之一作为分数，结束时显示得分***


***游戏开始显示动画***


***地图大小可调节***

​                           （其中方括号内为允许输入范围）



***游戏难度可选择，不同难度的贪吃蛇拥有不同的移动速度***




***边栏实时显示游戏信息***


***随时暂停和继续，并输出提示信息***


***特殊食物出现时用进度条显示倒计时***



### 二、设计思路

用一个双端队列存储蛇身，整数1 2 3 4 分别代表方向上下左右，每次依方向数据在蛇头部添加元素，在蛇尾消除元素。

在Food类中，用随机数产生横纵坐标决定食物出现位置。

整个程序是一个二重循环，move_forward是内层循环，遇到特殊事件时退出并返回相应的值给第一重循环，第一重循环依返回值做出相应的处理。



### 三、模块划分

代码共划分为四个模块，分别是

（1）Game Controller模块：控制游戏主逻辑，负责游戏的计分，启动和暂停。如果将游戏本身看作一个死循环，Game Controller是整个程序的第一层循环，接受其他模块发送的信息，并作出相应的响应和处理。

~~~C++
class GameControler{
public:
    GameControler();
    void mov_arrow(int x, int y);
    void start_interface(int &col, int &raw, int &speed);//开始界面
    void game_over();
    void game();
    void pause();
    void show_info();
private:
    int state, score, mode;//state表示游戏状态，score为得分，mode表示当前游戏的困难程度
    Snake snake;
    Food food;
    Graph map;
};
~~~



（2）Graph模块：接受控制台输入的参数，主要负责地图的绘制。

~~~C++
class Graph{
    friend class Food;
    friend class Snake;//将Snake和Food声明为友元，方便直接访问地图的行列信息
public:
    Graph():col(50), raw(25){};//默认值
    void set_map(int col_input, int raw_input);
    void draw_map();
    void mov_arrow(int x, int y);//移动光标
private:
    int col, raw;
};
~~~



（3）Food模块：控制地图上食物产生的逻辑和种类。

~~~C++
class Food {
friend Snake;
public:
    Food():timer(0), time_lim_food(0),food_position({0,0}){};
    void draw_food(Graph &map, Snake &snake);
    static int count;//用于计数是否应当有特殊食物出现
private:
    int timer;//用于倒计时
    bool time_lim_food;//是否存在特殊食物的标志
    COORD food_position;//当前食物位置
};
~~~



（4）Snake模块：游戏的二级循环，控制蛇的移动，成长，以及根据蛇的位置和状态向一级循环发送关键信息。

~~~C++
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
    deque<COORD> snake;//用双端队列表示蛇体
};
~~~



**模块间基本逻辑关系**

​                     Food   -------> Snake <-------------------------------------                    

​                         |               <------------------                                      |

​                     Graph        |                       |                                     |

起始界面 ------------------->  游戏过程------------------->  结束         |

​                                                                                                        |

​                                     Game Controller <----------------------------



### 四、核心代码分析

（1）主逻辑代码

分析内容见注释

~~~C++
void GameControler::game() {
    int raw = 50,col = 50,speed = 200;//默认地图大小和移动速度
    start_interface(col, raw, speed);//显示初始界面
    map.set_map(col, raw/2);//由于高是宽的两倍，为了达到视觉效果，采用raw/2作为参数
    snake.set_speed(speed);//设置移动速度
    map.draw_map();//绘出地图
    show_info();//显示边栏提示信息
    snake.show_snake();//画出蛇体
    food.draw_food(map,snake);//显示食物
    while(state = snake.mov_forward(map, food)){//通过mov_forward的返回值获取程序状态
        if(state == 0) break;//游戏结束
        else if(state == 1){
            pause();
        }//游戏暂停
        else if(state >= 2){
            score += (state - 1);
            show_info();
        }//得分
    }
    game_over();//显示结束页面，显示最终得分
    Sleep(2700);
    return;
}
~~~

（2)次逻辑代码

~~~C++
dint Snake::mov_forward(Graph &map, Food &food) {
    mov_arrow(68,33);
    int key;
    while(1){
        if(food.timer != 0){//记录步数，timer用于进行30步倒计时
            food.timer--;
            mov_arrow(11, 33);
            for(int i = 0; i < food.timer; i++){
                cout << "=";
            }
            cout << "                   ";//进度条减少
            if(food.timer == 0){
                  ...
                清空进度条
                  ...
                food.draw_food(map, *this);
            }
        }
        if(kbhit()) {//监听键盘操作
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
        grow_up(1);//头部增1
        mov_arrow(snake.back().X, snake.back().Y);
        cout << ' ';
        snake.pop_back();//尾部减一
        
        mov_arrow(68,33);//防止光标闪烁影响游戏体验
        
        if(snake.front().X <= 0 || snake.front().X >= map.col-1
        || snake.front().Y <= 0 || snake.front().Y >= map.raw-1
        ) return 0;//撞墙
        
        for(int i = 1; i < snake.size(); ++i){
            if(snake[i].X == snake.front().X && snake[i].Y == snake.front().Y)
                return 0;//撞自己
        }
        
        if(snake.front().X == food.food_position.X && snake.front().Y == food.food_position.Y){//吃到食物
            if(food.time_lim_food == false) {//判断食物种类
                grow_up(1);
                food.draw_food(map, *this);
                return 2;
            }
            else{
                int score = 2+food.timer/6;
                food.timer = 0;//倒计时清零
                mov_arrow(10, 33);
                cout << "                                   ";//清空进度条
                food.time_lim_food = 0;
                grow_up(1);
                food.draw_food(map, *this);
                return score;
            }
        }
    }
}
~~~


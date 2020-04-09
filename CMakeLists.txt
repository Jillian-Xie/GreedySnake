cmake_minimum_required(VERSION 3.15)
project(GreedySnake)

set(CMAKE_CXX_STANDARD 14)

add_executable(GreedySnake main.cpp Snake.h Graph.cpp Graph.h GameControler.cpp GameControler.h Snake.cpp Food.cpp Food.h)
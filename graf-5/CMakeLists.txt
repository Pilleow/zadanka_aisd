cmake_minimum_required(VERSION 3.28)
project(graf)

set(CMAKE_CXX_STANDARD 17)

add_executable(graf main.cpp
        GraphAsMatrix.h
        GraphAsMatrix.cpp
        visitor.h
        visitor.cpp)

cmake_minimum_required(VERSION 3.27)
project(runtest)

set(CMAKE_CXX_STANDARD 17)

add_executable(runtest
        setasarray.cpp
        setasarray.h
        visitor.cpp
        visitor.h
        test.cpp
)

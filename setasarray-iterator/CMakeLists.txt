cmake_minimum_required(VERSION 3.27)
project(setasarray_iterator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(setasarray_iterator
        setasarray.cpp
        setasarray.h
        test.cpp)

cmake_minimum_required(VERSION 3.31.6)
project(Project_Calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_Calculator
        src/main.cpp
        src/calculator.cpp
        src/calculator.h)

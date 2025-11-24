cmake_minimum_required(VERSION 4.0)
project(cpp_lab6_task4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_lab6_task4 main.cpp
        NumberGenerator.cpp
        NumberGenerator.h)

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(PROJECT_NAME File_RW_Test)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp FileHandle.cpp)

add_compile_options(-std=c++11 -lpthread )


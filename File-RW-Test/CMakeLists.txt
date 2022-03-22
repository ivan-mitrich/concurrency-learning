cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(PROJECT_NAME File_RW_Test)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp FileHandle.cpp)

add_compile_options(-std=c++11 -pthread -lpthread -Wl,--no-as-needed -Wall -Wextra -Wshadow)


set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -lpthread -Wl,--no-as-needed -Wall -Wextra -Wshadow")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.27)
project(pong)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(pong main.cpp
        Game.cpp
        Game.h
        Screen.cpp
        Screen.h
        Ball.cpp
        Ball.h
        src/headers/Helper.h
        Player.cpp
        Player.h
)

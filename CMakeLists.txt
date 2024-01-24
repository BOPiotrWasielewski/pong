cmake_minimum_required(VERSION 3.27)
project(pong)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(pong main.cpp
        src/classes/Game.cpp
        src/headers/Game.h
        src/classes/Screen.cpp
        src/headers/Screen.h
        src/classes/Ball.cpp
        src/headers/Ball.h
        src/headers/Helper.h
        src/classes/Player.cpp
        src/headers/Player.h
)

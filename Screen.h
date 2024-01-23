//
// Created by piotr on 22.01.2024.
//

#ifndef PONG_SCREEN_H
#define PONG_SCREEN_H

#include <thread>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <windows.h>

class Screen {
private:
    int width = 0;
    int height = 0;

    CONSOLE_SCREEN_BUFFER_INFO buffer{};
public:
    Screen();

    void calculate();
    void run();

    int getWidth();
    int getHeight();
};


#endif //PONG_SCREEN_H

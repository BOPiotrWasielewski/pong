//
// Created by piotr on 22.01.2024.
//

#include "Screen.h"

Screen::Screen() {
    this->calculate();
}

void Screen::calculate() {
    GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&this->buffer);
    this->width = this->buffer.dwSize.X;
    this->height = this->buffer.dwSize.Y;
}

int Screen::getWidth() {
    return this->width;
}

int Screen::getHeight() {
    return this->height;
}

void Screen::run() {
    std::thread resize([&]{
        for(;;){
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);
            this->calculate();
        }
    });
    resize.join();
}

//
// Created by piotr on 22.01.2024.
//

#include "../headers/Screen.h"

Screen::Screen() {
    this->calculate(); /** Run screen depths calculation method */
}

void Screen::calculate() {
    GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&this->buffer); /** Get terminal buffer information's and store in buffer value */
    this->width = this->buffer.dwSize.X; /** Set value of width based on terminal buffer */
    this->height = this->buffer.dwSize.Y; /** Set value of height based on terminal buffer */
}

int Screen::getWidth() {
    return this->width; /** Returns value of screen width */
}

int Screen::getHeight() {
    return this->height; /** Returns value of screen height */
}

void Screen::run(bool &force_restart) {
    std::thread resize([&]{ /** Create thread to catch terminal window resize */
        for(;;){ /** Infinite loop to keep thread alive */
            if(force_restart) break; /** End thread if game is restarting */
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s); /** stop thread for 0.05s */
            this->calculate(); /** Recalculate screen depths */
        }
    });
    resize.join(); /** Join and synchronize thread */
}

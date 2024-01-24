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
    int width = 0; /** Stores value of game screen width */
    int height = 0; /** Stores value of game screen height */

    CONSOLE_SCREEN_BUFFER_INFO buffer{}; /** Buffer for console window to read width and height of game screen */
public:
    /**
     * Constructor for initialize calculation of screen depths
     */
    Screen();

    /**
     * Method for calculate depths of game screen
     */
    void calculate();

    /**
     * Method to create and run thread for recalculating game screen depths
     * @param force_restart - flag to end thread on game restart
     */
    void run(bool &force_restart);

    /**
     * Getter method for game screen width
     * @return int value of screen width
     */
    int getWidth();

    /**
     * Getter method for game screen height
     * @return int value of screen height
     */
    int getHeight();
};


#endif //PONG_SCREEN_H

//
// Created by piotr on 22.01.2024.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <thread>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <windows.h>
#include "Screen.h"
#include "Ball.h"
#include "src/headers/Helper.h"
#include "Player.h"

class Game {
private:
    Screen screen;
    Helper::GameTime gameTime;
    Ball ball = Ball(1, 10, Helper::Axis::TopRight);
    Player player_1;
    Player player_2;
    Helper::Winner winner;
    bool hasWinner = false;
    bool started = false;
    bool is_running = true;

    int maxPoints = 3;

    void createPlayers();
    void horizontal_line(int length, int startPosX = 1, int offset = 1, int offsetY = 0);
    void vertical_line(int length, int startPos = 1, int offset = 1);
    void label(std::string text, int posX, int posY, Helper::Color color = Helper::Color::DEFAULT);
    void showTimer();
    void clear();

    // Play
    void checkPosition();
    void listenPlayer_1();
    void listenPlayer_2();
    void checkScore();
    void setWinner(Helper::Winner winner);
public:
    Game(int maxPoints = 3);
    int run();
};


#endif //PONG_GAME_H

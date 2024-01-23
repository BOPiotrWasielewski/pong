//
// Created by piotr on 22.01.2024.
//

#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

#include <thread>
#include <conio.h>
#include <windows.h>
#include "src/headers/Helper.h"

class Player {
private:
    int posX = 1;
    int posY = 1;
    int oldPosY = posY;
    int width = 2;
    int height = 10;
    int score = 0;
    Helper::Color color;
public:
    Player(Helper::Color color = Helper::Color::WHITE, int width = 2, int height = 10);
    void render();
    void savePosition();

    void SetPositionX(int posX);
    void SetPositionY(int posY);
    int GetPositionX();
    int GetPositionY();
    int GetHeight();
    int GetWidth();

    void IncreaseScore();
    void ResetScore();
    int GetScore();
};


#endif //PONG_PLAYER_H

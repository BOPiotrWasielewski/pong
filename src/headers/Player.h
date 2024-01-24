//
// Created by piotr on 22.01.2024.
//

#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

#include <thread>
#include <conio.h>
#include <windows.h>
#include "Helper.h"

class Player {
private:
    int posX = 1; /** Current Horizontal position of player */
    int posY = 1; /** Current Vertical position of player */
    int oldPosY = posY; /** Old Vertical position of player */
    int width = 2; /** Player object width for hitbox calculations */
    int height = 10; /** Player object height for hitbox calculations */
    int score = 0; /** Player score points */
    Helper::Color color; /** Player color based on Color enumeration */
public:
    /**
     * Constructor of Player class to create player object with specific startup params
     * @param color - Color enumeration for player color
     * @param width - width value of player object
     * @param height - height value of player object
     */
    Player(Helper::Color color = Helper::Color::WHITE, int width = 2, int height = 10);

    /**
     * Method for rendering and cleaning object on game screen
     */
    void render();

    /**
     * Method for saving current position of object to clear old data on render
     */
    void savePosition();

    /**
     * Setter method for changing Horizontal position
     */
    void SetPositionX(int posX);

    /**
     * Setter method for changing Vertical position
     */
    void SetPositionY(int posY);

    /**
     * Getter method for vertical position
     */
    int GetPositionY();

    /**
     * Getter method for player height
     */
    int GetHeight();

    /**
     * Getter method for player width
     */
    int GetWidth();

    /**
     * Method for increase player score points
     */
    void IncreaseScore();

    /**
     * Method for reset player points to default(0)
     */
    void ResetScore();

    /**
     * Getter method for player score points
     * @return int value of player score points
     */
    int GetScore();
};


#endif //PONG_PLAYER_H

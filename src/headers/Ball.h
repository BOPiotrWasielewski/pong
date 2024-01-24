//
// Created by piotr on 22.01.2024.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Helper.h"

class Ball {
private:
    int x = 1; /** Current Horizontal position of game ball */
    int y = 10; /** Current Vertical position of game ball */
    int oldX = x; /** Old Horizontal position of game ball */
    int oldY = y; /** Old Vertical position of game ball */
    int modifier = 0; /** Modification value for moving ball object */
    Helper::Axis axis = Helper::Axis::BottomRight; /** Current axis of rotation for moving ball object */
public:
    /**
     * Constructor of Ball class to create ball object with specific startup params
     * @param posX - Horizontal position of object
     * @param posY - Vertical position of object
     * @param axis - Axis of rotation of object
     */
    Ball(int posX, int posY, Helper::Axis axis);

    /**
     * Method for rendering and cleaning object on game screen
     */
    void render() const;

    /**
     * Setter method for changing position of object to specific horizontal and vertical coords
     * @param x - Horizontal position of object
     * @param y - Vertical position of object
     */
    void setPosition(int x, int y);

    /**
     * Method for saving current position of object to clear old data on render
     */
    void savePosition();

    /**
     * Setter method for changing object Axis of rotation
     * @param axis - Axis enumeration value
     */
    void setAxis(Helper::Axis axis);

    /**
     * Setter method for changing modification value of moving object
     * @param modifier - modification value
     */
    void setModifier(int modifier);

    /**
     * Getter method for Horizontal position of object
     * @return int value of current horizontal position
     */
    int GetPositionX() const;

    /**
     * Getter method for Vertical position of object
     * @return int value of current vertical position
     */
    int GetPositionY() const;

    /**
     * Method for randomize starting position and axis of object
     * @param minX - minimum horizontal position value of object
     * @param minY - minimum vertical position value of object
     * @param maxX - maximum horizontal position value of object
     * @param maxY - maximum vertical position value of object
     */
    void randomize(int minX, int minY, int maxX, int maxY);

    /**
     * Getter method for Axis of rotation of object
     * @return Axis value of rotation
     */
    Helper::Axis GetAxis();
};


#endif //PONG_BALL_H

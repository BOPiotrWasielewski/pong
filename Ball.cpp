//
// Created by piotr on 22.01.2024.
//

#include "Ball.h"

Ball::Ball(int posX, int posY, Helper::Axis axis) {
    this->oldX = this->x = posX; // Set startup values of horizontal position
    this->oldY = this->y = posY; // Set startup values of vertical position
    this->axis = axis; // Set startup value of axis of rotation
    srand(time(NULL)); // Prepare to generate random values for randomize() method
}

void Ball::render() const {
    Helper::gotoXY(oldX, oldY);
    Helper::changeColor();
    printf(" "); // Removes old ball object render

    Helper::gotoXY(x, y);
    Helper::changeColor(Helper::Color::WHITE);
    printf(" "); // Creates new ball object render
    Helper::changeColor();
}

void Ball::setPosition(int posX, int posY) {
    this->x = posX;
    this->y = posY;

    switch (this->axis) {
        case Helper::Axis::TopRight:
            this->y -= this->modifier;
            break;
        case Helper::Axis::BottomRight:
            this->y += this->modifier;
            break;
        case Helper::Axis::BottomLeft:
            this->y += this->modifier;
            break;
        case Helper::Axis::TopLeft:
            this->y -= this->modifier;
            break;
    }
}

void Ball::savePosition() {
    this->oldX = this->x;
    this->oldY = this->y;
}

void Ball::setAxis(Helper::Axis newAxis) {
    this->axis = newAxis;
}

void Ball::setModifier(int modifier) {
    this->modifier = modifier;
}

Helper::Axis Ball::GetAxis() {
    return this->axis;
}

int Ball::GetPositionX() const {
    return this->x;
}

int Ball::GetPositionY() const {
    return this->y;
}

void Ball::randomize(int minX, int minY, int maxX, int maxY) {
    this->setPosition(rand() % maxX + minX, rand() % maxY + minY);
    this->setAxis(static_cast<Helper::Axis>(rand() % Helper::Axis::TopLeft));
    this->savePosition();
}

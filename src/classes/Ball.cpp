//
// Created by piotr on 22.01.2024.
//

#include "../headers/Ball.h"

Ball::Ball(int posX, int posY, Helper::Axis axis) {
    this->oldX = this->x = posX; /** Set startup values of horizontal position */
    this->oldY = this->y = posY; /** Set startup values of vertical position */
    this->axis = axis; /** Set startup value of axis of rotation */
    srand(time(NULL)); /** Prepare to generate random values for randomize() method */
}

void Ball::render() const {
    Helper::gotoXY(oldX, oldY);
    Helper::changeColor();
    printf(" "); /** Removes old ball object render */

    Helper::gotoXY(x, y);
    Helper::changeColor(Helper::Color::WHITE);
    printf(" "); /** Creates new ball object render */
    Helper::changeColor();
}

void Ball::setPosition(int posX, int posY) {
    this->x = posX; /** Set new horizontal position */
    this->y = posY; /** Set new vertical position */

    /** Checking for axis rotation of object to modify moving positions */
    switch (this->axis) {
        case Helper::Axis::TopRight:
            this->y -= this->modifier; /** Modifies vertical position by modifier value */
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
    this->oldX = this->x; /** Save horizontal position of object as old value for rerender */
    this->oldY = this->y; /** Save vertical position of object as old value for rerender */
}

void Ball::setAxis(Helper::Axis newAxis) {
    this->axis = newAxis; /** Set new axis of rotation */
}

void Ball::setModifier(int modifier) {
    this->modifier = modifier; /** Sat new move modifier */
}

Helper::Axis Ball::GetAxis() {
    return this->axis; /** Returns axis of rotation */
}

int Ball::GetPositionX() const {
    return this->x; /** Returns horizontal position of object */
}

int Ball::GetPositionY() const {
    return this->y; /** Returns vertical position of object */
}

void Ball::randomize(int minX, int minY, int maxX, int maxY) {
    this->setPosition(rand() % maxX + minX, rand() % maxY + minY); /** Set new position by random values */
    this->setAxis(static_cast<Helper::Axis>(rand() % Helper::Axis::TopLeft)); /** Set new axis of rotation by random value cast into Axis enumeration */
    this->savePosition(); /** Save current positions for rerender */
}

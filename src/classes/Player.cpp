//
// Created by piotr on 22.01.2024.
//

#include "../headers/Player.h"

Player::Player(Helper::Color color, int width, int height) {
    this->width = width; /** Set startup value of player width */
    this->height = height; /** Set startup value of player height */
    this->color = color; /** Set startup value of player color based on Color enumeration */
}

void Player::render() {
    Helper::changeColor();
    for(int i = 0; i < this->height; i++){ /** Loop for cleaning last position of player object */
        Helper::gotoXY(this->posX - (this->width - 1), i + this->oldPosY);
        for(int j = 0; j < this->width; j++){
            printf(" ");
        }
    }

    Helper::changeColor(this->color);
    for(int i = 0; i < this->height; i++){ /** Loop for render player object */
        Helper::gotoXY(this->posX - (this->width - 1), i + this->posY);
        for(int j = 0; j < this->width; j++){
            printf(" ");
        }
    }
    Helper::changeColor();
}

void Player::SetPositionX(int posX) {
    this->posX = posX; /** Set new horizontal position */
}

void Player::SetPositionY(int posY) {
    this->posY = posY; /** Set new vertical position */
}

void Player::savePosition() {
    this->oldPosY = this->posY; /** Save vertical position of object as old value for rerender */
}

int Player::GetPositionY() {
    return this->posY; /** Returns vertical position of object */
}

int Player::GetHeight() {
    return this->height; /** Returns height value of object */
}

int Player::GetWidth() {
    return this->width; /** Returns width value of object */
}

void Player::IncreaseScore() {
    this->score++; /** Increase score value */
}

void Player::ResetScore() {
    this->score = 0; /** Reset score to default(0) */
}

int Player::GetScore() {
    return this->score; /** Returns score value of object */
}

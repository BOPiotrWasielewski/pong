//
// Created by piotr on 22.01.2024.
//

#include "Player.h"

Player::Player(Helper::Color color, int width, int height) {
    this->width = width;
    this->height = height;
    this->color = color;
}

void Player::render() {
    Helper::changeColor();
    for(int i = 0; i < this->height; i++){
        Helper::gotoXY(this->posX - (this->width - 1), i + this->oldPosY);
        for(int j = 0; j < this->width; j++){
            printf(" ");
        }
    }

    Helper::changeColor(this->color);
    for(int i = 0; i < this->height; i++){
        Helper::gotoXY(this->posX - (this->width - 1), i + this->posY);
        for(int j = 0; j < this->width; j++){
            printf(" ");
        }
    }
    Helper::changeColor();
}

void Player::SetPositionX(int posX) {
    this->posX = posX;
}

void Player::SetPositionY(int posY) {
    this->posY = posY;
}

void Player::savePosition() {
    this->oldPosY = this->posY;
}

int Player::GetPositionX() {
    return this->posX;
}

int Player::GetPositionY() {
    return this->posY;
}

int Player::GetHeight() {
    return this->height;
}

int Player::GetWidth() {
    return this->width;
}

void Player::IncreaseScore() {
    this->score++;
}

void Player::ResetScore() {
    this->score = 0;
}

int Player::GetScore() {
    return this->score;
}

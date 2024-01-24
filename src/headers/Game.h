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
#include "Helper.h"
#include "Player.h"

class Game {
private:
    Screen screen; /** Screen object to get values of screen depths */
    Helper::GameTime gameTime; /** GameTime structure for calculating play time */
    Ball ball = Ball(1, 10, Helper::Axis::TopRight); /** Ball object to pass ball between players */
    Player player_1; /** Player 1 object */
    Player player_2; /** Player 2 object */
    Helper::Winner winner; /** Winner enumeration to define who win the game */
    bool hasWinner = false; /** Flag to define if game was won by any player */
    bool started = false; /** Flag to define is game started */
    bool is_running = true; /** Flag to define is game running */

    bool force_restart = false; /** Flag to enforce game restart */

    int maxPoints = 3; /** Game maximum parameter to define when game is over */

    /**
     * Method to create and define players and ball objects
     */
    void createPlayers();

    /**
     * Method to draw straight horizontal line based on params
     * @param length - length value of line
     * @param startPosX - horizontal start position of line
     * @param offset - define spaces inside line to make it dashed
     * @param offsetY - define vertical offset from starting position
     */
    void vertical_line(int length, int startPosX = 1, int offset = 1, int offsetY = 0);

    /**
     * Method to draw straight vertical line based on params
     * @param length - length value of line
     * @param startPos - horizontal start position of line
     * @param offset - define spaces inside line to make it dashed
     */
    void horizontal_line(int length, int startPos = 1, int offset = 1);

    /**
     * Mathod to display text on screen
     * @param text - string to display on screen
     * @param posX - horizontal position of text on screen
     * @param posY - vertical position of text on screen
     * @param color - Color enumeration value
     */
    void label(std::string text, int posX, int posY, Helper::Color color = Helper::Color::DEFAULT);

    /**
     * Method to draw in-game timer
     */
    void showTimer();

    /**
     * Method to clear game screen
     */
    void clear();

    /**
     * Method to check position of ball object
     */
    void checkPosition();

    /**
     * Method to listen on players events
     */
    void listenPlayers();

    /**
     * Method to check players score
     */
    void checkScore();

    /**
     * Setter winner enumeration if any of players win
     * @param winner - Winner enumeration value
     */
    void setWinner(Helper::Winner winner);

    /**
     * Method to listen on restart game
     */
    void listenForRestart();
public:
    /**
     * Constructor of Game class to initialize game screen and basic game informations
     * @param maxPoints - maximum value of players score to win the game
     */
    Game(int maxPoints = 3);

    /**
     * Method to run whole game and all required threads
     * @return int value on error code when game is finished
     */
    int run();
};


#endif //PONG_GAME_H

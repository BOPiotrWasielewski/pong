//
// Created by piotr on 22.01.2024.
//

#ifndef PONG_HELPER_H
#define PONG_HELPER_H

#define KEY_UP 72       //Up arrow character
#define KEY_DOWN 80    //Down arrow character

#include <vector>
#include <string>
#include <windows.h>
#include <cstdio>

class Helper {
public:
    /**
     * Enumeration for ball Axis rotation in game loop
     */
    enum Axis{
        TopRight,
        BottomRight,
        BottomLeft,
        TopLeft
    };

    /**
     * Enumeration for simple color picking in rendering thread
     */
    enum Color{
        RED,
        GREEN,
        WHITE,
        BLACK,
        DEFAULT
    };

    /**
     * Enumeration for detecting which player won the game
     */
    enum Winner{
        Player_1,
        Player_2
    };

    /**
     * Structure for calculating and rendering in-game timer
     */
    struct GameTime{
        int minutes = 0;
        int seconds = 0;
        void calculate(){
            if(this->seconds % 60 == 0){
                if(this->minutes == 99) return;
                this->minutes = this->seconds / 60;
                this->seconds = 0;
            }
        }
    };

    /**
     * Simple static method for setting cursor position on screen where some elements will be rendered
     * @param x - Horizontal position of cursor
     * @param y - Vertical position of cursor
     */
    static void gotoXY(int x, int y) {
        printf("%c[%d;%df", 0x1B, y, x); // Change position of cursor
    }

    /**
     * Static method to get specific terminal color codes based on Color enumeration
     * @param color - Color enumeration value
     * @return
     */
    static WORD parseColor(Color color){
        switch (color) {
            case Color::WHITE:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; // Returns white text with white background
            case Color::RED:
                return FOREGROUND_RED | BACKGROUND_RED; // Returns red text with red background
            case Color::GREEN:
                return FOREGROUND_GREEN | BACKGROUND_GREEN; // Returns green text with green background
            case Color::BLACK:
                return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; // Return black text on white background
            default:
                return 7; // Reset terminal color value to default one
        }
    }

    /**
     * Static method to return vector array of players winner board
     * @param winner - Winner enumeration value
     * @return vector array of ascii generated art text
     */
    static std::vector<std::string> getWinner(Winner winner){
        std::vector<std::string> ascii;
        ascii.clear();
        switch (winner) {
            case Winner::Player_1:
                ascii.push_back("                                                                             ");
                ascii.push_back("88888888ba   88                                                          88  ");
                ascii.push_back("88      \"8b  88                                                        ,d88  ");
                ascii.push_back("88      ,8P  88                                                      888888  ");
                ascii.push_back("88aaaaaa8P'  88  ,adPPYYba,  8b       d8   ,adPPYba,  8b,dPPYba,         88  ");
                ascii.push_back("88\"\"\"\"\"\"'    88  \"\"     `Y8  `8b     d8'  a8P_____88  88P'   \"Y8         88  ");
                ascii.push_back("88           88  ,adPPPPP88   `8b   d8'   8PP\"\"\"\"\"\"\"  88                 88  ");
                ascii.push_back("88           88  88,    ,88    `8b,d8'    \"8b,   ,aa  88                 88  ");
                ascii.push_back("88           88  `\"8bbdP\"Y8      Y88'      `\"Ybbd8\"'  88                 88  ");
                ascii.push_back("                                 d8'                                         ");
                ascii.push_back("                                d8'                                          ");
                break;
            case Winner::Player_2:
                ascii.push_back("                                                                                  ");
                ascii.push_back("88888888ba   88                                                       ad888888b,  ");
                ascii.push_back("88      \"8b  88                                                      d8\"     \"88  ");
                ascii.push_back("88      ,8P  88                                                              a8P  ");
                ascii.push_back("88aaaaaa8P'  88  ,adPPYYba,  8b       d8   ,adPPYba,  8b,dPPYba,          ,d8P\"   ");
                ascii.push_back("88\"\"\"\"\"\"'    88  \"\"     `Y8  `8b     d8'  a8P_____88  88P'   \"Y8        a8P\"      ");
                ascii.push_back("88           88  ,adPPPPP88   `8b   d8'   8PP\"\"\"\"\"\"\"  88              a8P'        ");
                ascii.push_back("88           88  88,    ,88    `8b,d8'    \"8b,   ,aa  88             d8\"          ");
                ascii.push_back("88           88  `\"8bbdP\"Y8      Y88'      `\"Ybbd8\"'  88             88888888888  ");
                ascii.push_back("                                 d8'                                              ");
                ascii.push_back("                                d8'                                               ");
                break;
        }
        return ascii;
    }

    /**
     * Changes console cursor color by specific Color enumeration value
     * @param color - Color enumeration value
     */
    static void changeColor(Color color = Color::DEFAULT){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, parseColor(color));
    }
};


#endif //PONG_HELPER_H

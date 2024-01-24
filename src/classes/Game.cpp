//
// Created by piotr on 22.01.2024.
//

#include "../headers/Game.h"

Game::Game(int maxPoints) {
    this->maxPoints = maxPoints; /** Set maximum required score to win game */
    this->screen = Screen(); /** Initialize Screen object to get game depths */
    SetConsoleTitle("CDV Pong"); /** Define application name */
    Helper::hideCursor(); /** Hide cursor on terminal */
}

void Game::createPlayers() {
    this->player_1 = Player(Helper::Color::GREEN, 2, 5); /** Initialize player 1 object with params */
    this->player_1.ResetScore(); /** Reset player 1 score to prepare game */
    this->player_1.SetPositionY((this->screen.getHeight() / 2) + 3); /** Set startup vertical position of player */
    this->player_1.savePosition(); /** Saves player 1 coords */

    this->player_2 = Player(Helper::Color::RED, 2, 5); /** Initialize player 2 object with params */
    this->player_2.ResetScore(); /** Reset player 2 score to prepare game */
    this->player_2.SetPositionY((this->screen.getHeight() / 2) + 3); /** Set startup vertical position of player */
    this->player_2.savePosition(); /** Saves player 2 coords */

    /** Randomize ball location in game board */
    this->ball.randomize((this->screen.getWidth() / 2) - 4, 10, (this->screen.getWidth() / 2) + 4, this->screen.getHeight() - 8);
}

int Game::run() {
    this->force_restart = false; /** Disable force game restart to avoid rendering errors */
    this->gameTime.clearTime(); /** Clear in-game timer */
    this->createPlayers(); /** Run create players method to prepare entities for board */
    system("cls"); /** Clear whole screen */
    std::thread th_gameTime([&] { /** Thread for updating in-game timer */
        while(is_running) {
            using namespace std::chrono_literals;

            if(this->force_restart) break; /** End thread if game is restarting */

            if(this->started){ /** Checks if game already started */
                std::this_thread::sleep_for(1s); /** Sleep thread for 1s */
                this->gameTime.seconds+=1; /** Increase timer seconds by 1 */
                this->gameTime.calculate(); /** Calculate in-game time for seconds and minutes */
            }
        }
    });
    std::thread th_render([&] { /** Main thread responsible for drawing all objects on game screen */
        int delay = 1; /** Delay value to calculate refresh game screen rate */
        while(is_running) { /** Game main loop */
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);

            if (delay % 45 == 0) this->clear(); /** Clear whole game screen once every 45 ticks (about 0.5 FPS) */
            this->checkScore(); /** Check players score before refresh whole game objects */

            this->horizontal_line(this->screen.getWidth() - 7, 1); /** Draw vertical line to make board top border */
            this->horizontal_line(this->screen.getWidth(), this->screen.getHeight()); /** Draw horizontal line to make board bottom border */
            this->vertical_line(this->screen.getHeight(), (this->screen.getWidth() / 2) + 1, 2); /** Draw vertical line to split board */
            this->showTimer(); /** Draw timer on top of the game screen */
            this->label("CDV PONG", (this->screen.getWidth() / 2) - 3, 2, Helper::Color::BLACK); /** Show text with game title on game screen */

            this->label("Player 1", this->screen.getWidth() - 35, 4); /** Show player 1 name on game screen */
            this->label("Score: "+std::to_string(this->player_1.GetScore()), this->screen.getWidth() - 35, 5); /** Show player 1 score on game screen */
            this->player_1.SetPositionX(this->screen.getWidth()); /** Update player 1 horizontal position */
            this->player_1.render(); /** Render player 1 object */

            this->label("Player 2", 30, 4); /** Show player 2 name on game screen */
            this->label("Score: "+std::to_string(this->player_2.GetScore()), 30, 5); /** Show player 2 score on game screen */
            this->player_2.SetPositionX(1); /** Update player 2 horizontal position */
            this->player_2.render(); /** Render player 2 object */

            this->listenPlayers(); /** Run players actions listener */

            this->ball.render(); /** Render ball object on game screen */

            if(!this->started) { /** Create counter on game initialize */
                for(int i = 5; i > 0; i--){
                    this->label("Start in: "+std::to_string(i), (this->screen.getWidth() / 2) - 5, 16); /** Draw count down to start game */
                    std::this_thread::sleep_for(1s);
                }
                this->clear(); /** Clear game screen after count down */
                this->started = true;
            }

            this->checkPosition(); /** Checks ball object position on screen */
            delay++;
        }

        delay = 1;
        while(true) { /** Winner board loop */
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);

            if(this->force_restart) break; /** End thread if game is restarting */

            if(!is_running && hasWinner){ /** Checks if game is over and any of players won */
                if (delay % 40 == 0 || delay == 1) this->clear(); /** Clear whole game screen once every 45 ticks (about 0.5 FPS) or on winner board show up */

                this->label("! Winner !", (this->screen.getWidth() / 2) - 5, 8); /** Draw winner message */
                std::vector<std::string> ascii = Helper::getWinner(this->winner); /** Get winner ASCII art code */
                for(int i = 0; i < ascii.size(); i++){ /** Draw all lines of winner ASCII art code */
                    this->label(ascii[i], (this->screen.getWidth() / 2) - (ascii[i].length() / 2), 10 + i);
                }

                if(delay % 2) this->label("[ INSERT COIN TO CONTINUE ]", (this->screen.getWidth() / 2) - 13, 24); /** Draw text to restart the game */
                else this->label("                           ", (this->screen.getWidth() / 2) - 13, 24); /** Clear restart game text for cool animation */

                this->listenForRestart(); /** Listen for restart game action */

                delay++;
            }
        }
    });
    this->screen.run(this->force_restart); /** Run and synchronize screen depths calculation thread */
    th_gameTime.join(); /** Run and synchronize in-game time calculation */
    th_render.join(); /** Run and synchronize game main thread */

    return this->force_restart ? this->run() : 0;
}

void Game::vertical_line(int length, int startPosX, int offset, int offsetY) {
    for (int i = 1; i <= length; i += offset) { /** Loop to calculate position of line pixels */
        Helper::gotoXY(startPosX, i + offsetY);
        Helper::changeColor(Helper::Color::WHITE);
        printf(" ");
    }
    Helper::changeColor();
}

void Game::horizontal_line(int length, int startPos, int offset) {
    for (int i = 1; i <= length; i += offset) { /** Loop to calculate position of line pixels */
        Helper::gotoXY(i, startPos);
        Helper::changeColor(Helper::Color::WHITE);
        printf(" ");
    }
    Helper::changeColor();
}

void Game::checkPosition() {
    int r_pointer = rand() % 2; /** Create random value to be used as ball axis rotation and modifier */
    ball.savePosition(); /** Save ball position to recreate in new coords */
    switch (this->ball.GetAxis()) { /** Check current Axis to update it on border touch */
        case Helper::Axis::TopRight:
            if (ball.GetPositionY() <= 2) { /** Check if ball touched top border */
                ball.setAxis(Helper::Axis::BottomRight); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() >= (this->screen.getWidth() - this->player_1.GetWidth() - 3) &&
                       ball.GetPositionY() >= this->player_1.GetPositionY() &&
                       ball.GetPositionY() <= this->player_1.GetPositionY() + this->player_1.GetHeight()) { /** Check if ball touch player 1 hitbox */
                ball.setAxis(r_pointer ? Helper::Axis::TopLeft : Helper::Axis::BottomLeft); /** Change axis on player 1 touch */
                ball.setModifier(r_pointer); /** Add random modifier to ball movement on player touch */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() >= this->screen.getWidth()) { /** Check if ball touched right border */
                this->player_2.IncreaseScore(); /** Increase player 2 score points on border touch */
                ball.setAxis(Helper::Axis::TopLeft); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            }
            ball.setPosition(ball.GetPositionX() + 3, ball.GetPositionY() - 1); /** Update ball position on screen */
            break;
        case Helper::Axis::BottomRight:
            if (ball.GetPositionY() >= this->screen.getHeight() - 1) {
                ball.setAxis(Helper::Axis::TopRight); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() >= (this->screen.getWidth() - this->player_1.GetWidth() - 3) &&
                       ball.GetPositionY() >= this->player_1.GetPositionY() &&
                       ball.GetPositionY() <= this->player_1.GetPositionY() + this->player_1.GetHeight()) { /** Check if ball touch player 1 hitbox */
                ball.setAxis(r_pointer ? Helper::Axis::BottomLeft : Helper::Axis::TopLeft); /** Change axis on player 1 touch */
                ball.setModifier(r_pointer); /** Add random modifier to ball movement on player touch */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() >= this->screen.getWidth()) { /** Check if ball touched right border */
                this->player_2.IncreaseScore(); /** Increase player 2 score points on border touch */
                ball.setAxis(Helper::Axis::BottomLeft); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            }
            ball.setPosition(ball.GetPositionX() + 3, ball.GetPositionY() + 1); /** Update ball position on screen */
            break;
        case Helper::Axis::BottomLeft:
            if (ball.GetPositionY() >= this->screen.getHeight() - 1) {
                ball.setAxis(Helper::Axis::TopLeft); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() <= 5 &&
                       ball.GetPositionY() >= this->player_2.GetPositionY() &&
                       ball.GetPositionY() <= this->player_2.GetPositionY() + this->player_2.GetHeight()) { /** Check if ball touch player 2 hitbox */
                ball.setAxis(r_pointer ? Helper::Axis::BottomRight : Helper::Axis::TopRight); /** Change axis on player 2 touch */
                ball.setModifier(r_pointer); /** Add random modifier to ball movement on player touch */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() <= 1) { /** Check if ball touched left border */
                this->player_1.IncreaseScore(); /** Increase player 1 score points on border touch */
                ball.setAxis(Helper::Axis::BottomRight); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            }
            ball.setPosition(ball.GetPositionX() - 3, ball.GetPositionY() + 1); /** Update ball position on screen */
            break;
        case Helper::Axis::TopLeft:
            if (ball.GetPositionY() <= 2) { /** Check if ball touched top border */
                ball.setAxis(Helper::Axis::BottomLeft); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() <= 5 &&
                       ball.GetPositionY() >= this->player_2.GetPositionY() &&
                       ball.GetPositionY() <= this->player_2.GetPositionY() + this->player_2.GetHeight()) { /** Check if ball touch player 2 hitbox */
                ball.setAxis(r_pointer ? Helper::Axis::TopRight : Helper::Axis::BottomRight); /** Change axis on player 2 touch */
                ball.setModifier(r_pointer); /** Add random modifier to ball movement on player touch */
                return checkPosition(); /** Recalculate ball object position */
            } else if (ball.GetPositionX() <= 1) { /** Check if ball touched left border */
                this->player_1.IncreaseScore(); /** Increase player 1 score points on border touch */
                ball.setAxis(Helper::Axis::TopRight); /** Change axis on border touch */
                ball.setModifier(0); /** Reset ball movement modifier */
                return checkPosition(); /** Recalculate ball object position */
            }
            ball.setPosition(ball.GetPositionX() - 3, ball.GetPositionY() - 1); /** Update ball position on screen */
            break;
    }
}

void Game::listenPlayers() {
    this->player_1.savePosition(); /** Save current player 1 position */
    this->player_2.savePosition(); /** Save current player 2 position */

    if (GetAsyncKeyState(VK_DOWN)) { /** Check if user pressed DOWN key on keyboard */
        if (this->player_1.GetPositionY() + this->player_1.GetHeight() < this->screen.getHeight()) /** Check if player 1 position is not before border */
            this->player_1.SetPositionY(this->player_1.GetPositionY() + 1); /** Move player 1 position down */
    }
    if (GetAsyncKeyState(VK_UP)) {/** Check if user pressed UP key on keyboard */
        if (this->player_1.GetPositionY() > 2) /** Check if player 1 position is not before border */
            this->player_1.SetPositionY(this->player_1.GetPositionY() - 1); /** Move player 1 position up */
    }
    if (GetAsyncKeyState(0x53)) { /** Check if user pressed S key on keyboard */
        if (this->player_2.GetPositionY() + this->player_2.GetHeight() < this->screen.getHeight()) /** Check if player 2 position is not before border */
            this->player_2.SetPositionY(this->player_2.GetPositionY() + 1); /** Move player 2 position down */
    }
    if (GetAsyncKeyState(0x57)) { /** Check if user pressed W key on keyboard */
        if (this->player_2.GetPositionY() > 2) /** Check if player 2 position is not before border */
            this->player_2.SetPositionY(this->player_2.GetPositionY() - 1); /** Move player 2 position up */
    }
}

void Game::label(std::string text, int posX, int posY, Helper::Color color) {
    Helper::changeColor(color); /** Change text color on print */
    Helper::gotoXY(posX, posY); /** Move cursor to new text position */
    printf("%s", text.c_str()); /** Print text on screen */
    Helper::changeColor(); /** Reset terminal color to default */
}

void Game::showTimer() {
    Helper::changeColor(Helper::Color::BLACK); /** Change timer display color on print */
    Helper::gotoXY(this->screen.getWidth() - 6, 1); /** Move cursor to new timer position */
    printf(" %02d:%02d ", this->gameTime.minutes, this->gameTime.seconds); /** Print timer values on screen */
    Helper::changeColor(); /** Reset terminal color to default */
}

void Game::clear() {
    Helper::changeColor(); /** Reset terminal color to default */
    for (int i = 2; i < this->screen.getHeight() - 1; i++) { /** Loop through whole screen to clear it */
        Helper::gotoXY(1, i);
        for (int j = 1; j < this->screen.getWidth() + 1; j++) {
            printf(" ");
        }
    }
    Helper::changeColor();
}

void Game::checkScore() {
    if(this->player_1.GetScore() == this->maxPoints) return this->setWinner(Helper::Winner::Player_1); /** Check if player 1 won game */
    if(this->player_2.GetScore() == this->maxPoints) return this->setWinner(Helper::Winner::Player_2); /** Check if player 2 won game */
}

void Game::setWinner(Helper::Winner win) {
    this->hasWinner = true; /** Set main game loop parameter to define winner */
    this->winner = win; /** Set winner of game */
    this->is_running = false; /** Stop main game loop to show winner board */
}

void Game::listenForRestart() {
    if (GetAsyncKeyState(VK_RETURN)) { /** Check if user pressed ENTER key on keyboard */
        this->force_restart = true; /** Set restart flag */
        this->hasWinner = false; /** Reset winner game param */
        this->is_running = true; /** Reset game loop */
        this->started = false; /** Set game to first launch state */
    }
}

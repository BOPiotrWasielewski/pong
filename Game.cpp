//
// Created by piotr on 22.01.2024.
//

#include "Game.h"

Game::Game(int maxPoints) {
    this->maxPoints = maxPoints;
    this->screen = Screen();
    SetConsoleTitle("CDV Pong");
}

void Game::createPlayers() {
    this->player_1 = Player(Helper::Color::GREEN, 2, 5);
    this->player_1.ResetScore();
    this->player_1.SetPositionY(10);
    this->player_1.savePosition();

    this->player_2 = Player(Helper::Color::RED, 2, 5);
    this->player_2.ResetScore();
    this->player_2.SetPositionY(10);
    this->player_2.savePosition();

    this->ball.randomize((this->screen.getWidth() / 2) - 4, 10, (this->screen.getWidth() / 2) + 4, this->screen.getHeight() - 8);
}

int Game::run() {
    this->createPlayers();
    system("cls");
    std::thread th_gameTime([&] {
        while(is_running) {
            using namespace std::chrono_literals;
            if(this->started){
                std::this_thread::sleep_for(1s);
                this->gameTime.seconds+=1;
                this->gameTime.calculate();
            }
        }
    });
    std::thread th_render([&] {
        int delay = 1;
        while(is_running) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);

            if (delay % 45 == 0) this->clear();
            this->checkScore();

            this->vertical_line(this->screen.getWidth() - 7, 1);
            this->vertical_line(this->screen.getWidth(), this->screen.getHeight());
            this->horizontal_line(this->screen.getHeight(), (this->screen.getWidth() / 2) + 1, 2);
            this->showTimer();
            this->label("CDV PONG", (this->screen.getWidth() / 2) - 3, 2, Helper::Color::BLACK);

            this->label("Player 1", this->screen.getWidth() - 35, 4);
            this->label("Score: "+std::to_string(this->player_1.GetScore()), this->screen.getWidth() - 35, 5);
            this->player_1.SetPositionX(this->screen.getWidth());
            this->player_1.render();

            this->label("Player 2", 30, 4);
            this->label("Score: "+std::to_string(this->player_2.GetScore()), 30, 5);
            this->player_2.SetPositionX(1);
            this->player_2.render();

            this->listenPlayer_1();
            this->listenPlayer_2();

            this->ball.render();

            if(!this->started) {
                for(int i = 5; i > 0; i--){
                    this->label("Start in: "+std::to_string(i), (this->screen.getWidth() / 2) - 5, 16);
                    std::this_thread::sleep_for(1s);
                }
                this->clear();
                this->started = true;
            }

            this->checkPosition();
            delay++;
        }

        delay = 1;
        while(true) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);

            if(!is_running && hasWinner){
                if (delay % 40 == 0 || delay == 1) this->clear();

                this->label("! Winner !", (this->screen.getWidth() / 2) - 5, 8);
                std::vector<std::string> ascii = Helper::getWinner(this->winner);
                for(int i = 0; i < ascii.size(); i++){
                    this->label(ascii[i], (this->screen.getWidth() / 2) - (ascii[i].length() / 2), 10 + i);
                }

                delay++;
            }
        }
    });
    this->screen.run();
    th_gameTime.join();
    th_render.join();

    return 0;
}

void Game::horizontal_line(int length, int startPosX, int offsetX, int offsetY) {
    for (int i = 1; i <= length; i += offsetX) {
        Helper::gotoXY(startPosX, i + offsetY);
        Helper::changeColor(Helper::Color::WHITE);
        printf(" ");
    }
    Helper::changeColor();
}

void Game::vertical_line(int length, int startPos, int offset) {
    for (int i = 1; i <= length; i += offset) {
        Helper::gotoXY(i, startPos);
        Helper::changeColor(Helper::Color::WHITE);
        printf(" ");
    }
    Helper::changeColor();
}

void Game::checkPosition() {
    int r_pointer = rand() % 2;
    ball.savePosition();
    switch (this->ball.GetAxis()) {
        case Helper::Axis::TopRight:
            if (ball.GetPositionY() <= 2) {
                ball.setAxis(Helper::Axis::BottomRight);
                return checkPosition();
            } else if (ball.GetPositionX() >= (this->screen.getWidth() - this->player_1.GetWidth() - 5) &&
                       ball.GetPositionY() >= this->player_1.GetPositionY() &&
                       ball.GetPositionY() <= this->player_1.GetPositionY() + this->player_1.GetHeight()) {
                ball.setAxis(r_pointer ? Helper::Axis::TopLeft : Helper::Axis::BottomLeft);
                ball.setModifier(r_pointer);
            } else if (ball.GetPositionX() >= this->screen.getWidth()) {
                this->player_2.IncreaseScore();
                ball.setAxis(Helper::Axis::TopLeft);
                return checkPosition();
            }
            ball.setPosition(ball.GetPositionX() + 3, ball.GetPositionY() - 1);
            break;
        case Helper::Axis::BottomRight:
            if (ball.GetPositionY() >= this->screen.getHeight() - 1) {
                ball.setAxis(Helper::Axis::TopRight);
                return checkPosition();
            } else if (ball.GetPositionX() >= (this->screen.getWidth() - this->player_1.GetWidth() - 5) &&
                       ball.GetPositionY() >= this->player_1.GetPositionY() &&
                       ball.GetPositionY() <= this->player_1.GetPositionY() + this->player_1.GetHeight()) {
                ball.setAxis(r_pointer ? Helper::Axis::BottomLeft : Helper::Axis::TopLeft);
                ball.setModifier(r_pointer);
            } else if (ball.GetPositionX() >= this->screen.getWidth()) {
                this->player_2.IncreaseScore();
                ball.setAxis(Helper::Axis::BottomLeft);
                return checkPosition();
            }
            ball.setPosition(ball.GetPositionX() + 3, ball.GetPositionY() + 1);
            break;
        case Helper::Axis::BottomLeft:
            if (ball.GetPositionY() >= this->screen.getHeight() - 1) {
                ball.setAxis(Helper::Axis::TopLeft);
                return checkPosition();
            } else if (ball.GetPositionX() <= 8 &&
                       ball.GetPositionY() >= this->player_2.GetPositionY() &&
                       ball.GetPositionY() <= this->player_2.GetPositionY() + this->player_2.GetHeight()) {
                ball.setAxis(r_pointer ? Helper::Axis::BottomRight : Helper::Axis::TopRight);
                ball.setModifier(r_pointer);
            } else if (ball.GetPositionX() <= 1) {
                this->player_1.IncreaseScore();
                ball.setAxis(Helper::Axis::BottomRight);
                return checkPosition();
            }
            ball.setPosition(ball.GetPositionX() - 3, ball.GetPositionY() + 1);
            break;
        case Helper::Axis::TopLeft:
            if (ball.GetPositionY() <= 2) {
                ball.setAxis(Helper::Axis::BottomLeft);
                return checkPosition();
            } else if (ball.GetPositionX() <= 8 &&
                       ball.GetPositionY() >= this->player_2.GetPositionY() &&
                       ball.GetPositionY() <= this->player_2.GetPositionY() + this->player_2.GetHeight()) {
                ball.setAxis(r_pointer ? Helper::Axis::TopRight : Helper::Axis::BottomRight);
                ball.setModifier(r_pointer);
            } else if (ball.GetPositionX() <= 1) {
                this->player_1.IncreaseScore();
                ball.setAxis(Helper::Axis::TopRight);
                return checkPosition();
            }
            ball.setPosition(ball.GetPositionX() - 3, ball.GetPositionY() - 1);
            break;
    }
}

void Game::listenPlayer_1() {
    this->player_1.savePosition();

    if (GetAsyncKeyState(VK_DOWN)) {
        if (this->player_1.GetPositionY() + this->player_1.GetHeight() < this->screen.getHeight())
            this->player_1.SetPositionY(this->player_1.GetPositionY() + 1);
    }
    if (GetAsyncKeyState(VK_UP)) {
        if (this->player_1.GetPositionY() > 2) this->player_1.SetPositionY(this->player_1.GetPositionY() - 1);
    }
}

void Game::listenPlayer_2() {
    this->player_2.savePosition();

    if (GetAsyncKeyState(0x53)) { // S
        if (this->player_2.GetPositionY() + this->player_2.GetHeight() < this->screen.getHeight())
            this->player_2.SetPositionY(this->player_2.GetPositionY() + 1);
    }
    if (GetAsyncKeyState(0x57)) { // W
        if (this->player_2.GetPositionY() > 2) this->player_2.SetPositionY(this->player_2.GetPositionY() - 1);
    }
}

void Game::label(std::string text, int posX, int posY, Helper::Color color) {
    Helper::changeColor(color);
    Helper::gotoXY(posX, posY);
    printf("%s", text.c_str());
    Helper::changeColor();
}

void Game::showTimer() {
    Helper::changeColor(Helper::Color::BLACK);
    Helper::gotoXY(this->screen.getWidth() - 6, 1);
    printf(" %02d:%02d ", this->gameTime.minutes, this->gameTime.seconds);
    Helper::changeColor();
}

void Game::clear() {
    Helper::changeColor();
    for (int i = 2; i < this->screen.getHeight() - 1; i++) {
        Helper::gotoXY(1, i);
        for (int j = 1; j < this->screen.getWidth() + 1; j++) {
            printf(" ");
        }
    }
    Helper::changeColor();
}

void Game::checkScore() {
    if(this->player_1.GetScore() == this->maxPoints) return this->setWinner(Helper::Winner::Player_1);
    if(this->player_2.GetScore() == this->maxPoints) return this->setWinner(Helper::Winner::Player_2);
}

void Game::setWinner(Helper::Winner win) {
    this->hasWinner = true;
    this->winner = win;
    this->is_running = false;
}

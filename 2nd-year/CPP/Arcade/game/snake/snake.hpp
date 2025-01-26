/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "../APixels.hpp"
#include "../ATexts.hpp"
#include "../AGameModule.hpp"

class Segment {
    public:
        float rect_x;
        float rect_y;

        Segment(float x = 20.0, float y = 20.0) {
            rect_x = x * 20;
            rect_y = y * 20;
        }
};

class Apple {
    public:
        float rect_x;
        float rect_y;

        Apple(int x = 20, int y = 20) {
            rect_x = x;
            rect_y = y;
        }
};
class PowerUp {
    public:
        PowerUp(int x = 20, int y = 20, int t = 0) {
            rect_x = x;
            rect_y = y;
            type = t;
        }
        float rect_x;
        float rect_y;
        int type;

        int getType() {
            return type;
        }
};

class Snake : public arcade::AGameModule {
    public:
        Snake() : isCyclical(false) {init();};
        ~Snake() = default;

        void init();
        void stop();
        void applyEvents(arcade::IEvent *eventWrapper);
        void applyEvent(const arcade::Key &key);
        void reload();
        void update(float deltaTime);
        int getScore();
        void draw(arcade::IGraphicalModule *module);

        void updateScoreInFile();
        int applyPowerUp(int type);
        void handleCollision();
        void moveSystem();
        void displayBorders(int i, int j, Pixel &p);
        void displayPowerUp(int i, int j, Pixel &p);
        void displayApple(int i, int j, Pixel &p);
        void displaySnake(int i, int j, Pixel &p);
        void displayGameover(int j, Pixel &p);
        void create_snake_pixel_wrapper();
        void create_snake_text_wrapper();
        bool forceApplePosition(Apple currentApple, int attempts);
        void generateApple();
        bool isPositionOccupied(float x, float y);
        void eatApple();
        bool isSnakeEatingItself() const;
        void forcePowerUpPosition(int attempts);
        void generatePowerUp();
        void managePowerUp(float deltaTime);
        void manageRainbowMod();

    private:
        std::list<Segment> snake;
        float _direction_x;
        float _direction_y;
        std::vector<Apple> apple;
        std::vector<PowerUp> powerUp;
        int _score;
        bool isCyclical;
        float clock = 0;
        float clock2 = 0;
        float decale = 0;
        float decale2 = 0;
        float _speed = 0.1;
        float _poweruptime = 0;
        bool rainbowMod = false;
        std::tuple<int, int, int> _color = {51, 153, 255};
        int _rainbowAttemps = 0;
        bool isGameOver = false;
};

#endif /* !SNAKE_HPP_ */

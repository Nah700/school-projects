/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** solarfox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_

#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <cmath>
#include "../APixels.hpp"
#include "../ATexts.hpp"
#include "../AGameModule.hpp"

class Ship {
public:
    float rect_x;
    float rect_y;

    Ship(float x = 40.0, float y = 45.0) {
        rect_x = x * 20;
        rect_y = y * 20;
    }
};

class Projectile {
public:
    float rect_x;
    float rect_y;
    int direction;
    bool isAlive = false;
    bool isPlayer = false;
    int turnLeft = 2;

    Projectile(float x, float y, int dir, bool player) : rect_x(x), rect_y(y), direction(dir), isPlayer(player) {}
};

class Enemy {
public:
    float rect_x;
    float rect_y;
    int direction;

    Enemy(float x, float y, int dir) : rect_x(x), rect_y(y), direction(dir) {}
};
class target {
    public:
        float rect_x;
        float rect_y;

        target(float x, float y) : rect_x(x), rect_y(y) {}
};

class Solarfox : public arcade::AGameModule
{
    public:
        Solarfox() = default;
        ~Solarfox() = default;

        void init();
        void stop();
        void applyEvents(arcade::IEvent *eventWrapper);
        void applyEvent(const arcade::Key &key);
        void update(float deltaTime);
        void reload();
        void draw(arcade::IGraphicalModule *module);
        int getScore();

        void initMusic();
        void cleanMusic();
        void manageShoot();
        void moveSystemPlayerProjectil();
        void moveSystemPlayer();
        void generatemines();
        void generatetargets();
        void generateEnemies();
        void handleShipCollision();
        void displayBorders(Pixel &pixel, int i, int j);
        void displayMines(Pixel &pixel, int i, int j);
        void displayEnemies(Pixel &pixel, int i, int j);
        void displayPlayer(Pixel &pixel, int i, int j);
        void displayPlayerProjectils(Pixel &pixel, int i, int j);
        void displayTargets(Pixel &pixel, int i, int j);
        void createGamePixelWrapper();
        void createGameTextWrapper();
        void moveEnemies(int i);
        void moveEnemiesProjectiles(int i);
        void manageEnemiesShoots(int i);
        void updatePosition();

    private:
        Ship ship;
        std::vector<Enemy> enemies;
        std::vector<Projectile> projectiles;
        std::vector<target> targets;
        std::vector<target> mines;
        int _score;
        int direction_x;
        int direction_y;
        float _clock = 0;
        float _clock2 = 0;
        float _clock3 = 0;
        float _clock4 = 0;
        float _delay = 0;
        float _delay2 = 0;
        float _delay3 = 0;
        float _delay4 = 0;
        float speedboost = 0;
        libvlc_instance_t * inst;
        libvlc_media_t *theme;
        libvlc_media_t *shot;
        libvlc_media_player_t *shotPlayer;
        libvlc_media_player_t *themePlayer;
        bool _musicInit = false;
};

#endif /* !SOLARFOX_HPP_ */

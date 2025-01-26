/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** solarfox
*/

#include "solarfox.hpp"

int gameSize_x = 80;
int gameSize_y = 50;

void Solarfox::initMusic()
{
    if (this->_musicInit)
        return;
    this->inst = libvlc_new(0, NULL);
    this->theme = libvlc_media_new_path(inst, "Assets/Solarfox/solarfox.mp3");
    this->shot = libvlc_media_new_path(inst, "Assets/Solarfox/shot.mp3");
    this->themePlayer = libvlc_media_player_new_from_media(theme);
    this->shotPlayer = libvlc_media_player_new_from_media(shot);
    libvlc_media_release(this->theme);
    libvlc_media_release(this->shot);
    libvlc_audio_set_volume(this->themePlayer, 80);
    libvlc_audio_set_volume(this->shotPlayer, 100);
    libvlc_media_player_play(this->themePlayer);
    this->_musicInit = true;
}

void Solarfox::init()
{
    createPixelsObject();
    createTextsObject();

    this->_score = 0;
    ship = Ship(1.6, 1);
    this->direction_x = 0;
    this->direction_y = 0;
    generateEnemies();
    generatetargets();
    generatemines();
    initMusic();
}

void Solarfox::cleanMusic()
{
    if (this->_musicInit) {
        libvlc_media_player_stop(this->themePlayer);
        libvlc_media_player_stop(this->shotPlayer);
        libvlc_media_player_release(this->themePlayer);
        libvlc_media_player_release(this->shotPlayer);
        libvlc_release(this->inst);
        this->_musicInit = false;
    }
}

void Solarfox::stop()
{
    this->_pixels->getPixelMap().clear();
    this->_texts->getTextMap().clear();
    this->enemies.clear();
    this->projectiles.clear();
    this->targets.clear();
    this->mines.clear();

    this->_score = -1;
    cleanMusic();
}

void Solarfox::applyEvents(arcade::IEvent *eventWrapper)
{
    arcade::Key key = eventWrapper->getEvent()->getKey();
    if (key != arcade::Key::KEY_LIST_END)
        applyEvent(key);
}

void Solarfox::manageShoot()
{
    if (libvlc_media_player_get_position(this->shotPlayer) >= 0.9 || libvlc_media_player_get_position(this->shotPlayer) <= 0.1){
        libvlc_media_player_stop(this->shotPlayer);
        libvlc_media_player_set_position(this->shotPlayer, 0.0);
        libvlc_media_player_play(this->shotPlayer);
    }
    projectiles[4].rect_x = ship.rect_x + direction_x;
    projectiles[4].rect_y = ship.rect_y + direction_y;
    projectiles[4].direction = direction_x == 1 ? 0 : direction_y == 1 ? 1 : direction_x == -1 ? 2 : 3;
    projectiles[4].isAlive = true;
}

void Solarfox::applyEvent(const arcade::Key &key)
{
    this->speedboost = 0;
    if (key == arcade::Key::LEFT_ARROW && this->direction_x != 1) {
        this->direction_x = -1;
        this->direction_y = 0;
    } else if (key == arcade::Key::RIGHT_ARROW && this->direction_x != -1) {
        this->direction_x = 1;
        this->direction_y = 0;
    } else if (key == arcade::Key::UP_ARROW && this->direction_y != 1) {
        this->direction_x = 0;
        this->direction_y = -1;
    } else if (key == arcade::Key::DOWN_ARROW && this->direction_y != -1) {
        this->direction_x = 0;
        this->direction_y = 1;
    } else if (key == arcade::Key::E_KEY) {
        manageShoot();
    } else if (key == arcade::Key::SPACE) {
        speedboost = 0.1;
    }
}

void Solarfox::moveSystemPlayerProjectil()
{
    if (this->projectiles[4].turnLeft == 0)
        this->projectiles[4].isAlive = false;
    this->projectiles[4].rect_x += this->direction_x;
    this->projectiles[4].rect_y += this->direction_y;
    this->projectiles[4].turnLeft = this->projectiles[4].isAlive ? this->projectiles[4].turnLeft - 1 : 2;

}
void Solarfox::moveSystemPlayer()
{
    this->ship.rect_x += this->direction_x;
    this->ship.rect_y += this->direction_y;
    if (this->ship.rect_x == 2 || this->ship.rect_x == gameSize_x - 3 || this->ship.rect_y == 2 || this->ship.rect_y == gameSize_y - 5) {
        reload();
    }
}
void Solarfox::generatemines()
{
    mines.clear();
    while (mines.size() < 20) {
        float x = rand() % (gameSize_x - 6) + 3;
        float y = rand() % (gameSize_y - 6) + 3;
        float dx = x - ship.rect_x;
        float dy = y - ship.rect_y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance >= 3)
            mines.push_back(target(x, y));
    }
}

void Solarfox::generatetargets()
{
    while (targets.size() < 10) {
        float x = rand() % (gameSize_x - 6) + 3;
        float y = rand() % (gameSize_y - 6) + 5;
        targets.push_back(target(x, y));
    }
}

void Solarfox::update(float deltaTime)
{
    this->_clock += deltaTime;
    this->_clock2 += deltaTime;
    this->_clock3 += deltaTime;
    this->_clock4 += deltaTime;
    this->_pixels->getPixelMap().clear();
    this->_texts->getTextMap().clear();

    if (this->_clock2 - this->_delay2 > 0.02 - this->speedboost / 10) {
        this->_delay2 = this->_clock2;
        moveSystemPlayerProjectil();
    }
    if (this->_clock3 - this->_delay3 > 0.2 - this->speedboost) {
        this->_delay3 = this->_clock3;
        moveSystemPlayer();
    }
    if (this->_clock - this->_delay > 0.1) {
        this->_delay = this->_clock;
        updatePosition();
    }
    if (this->_clock4 - this->_delay4 > 5) {
        this->_delay4 = this->_clock4;
        generatemines();
    }
    handleShipCollision();
    createGamePixelWrapper();
    createGameTextWrapper();
}

void Solarfox::reload()
{
    stop();
    init();
}

void Solarfox::draw(arcade::IGraphicalModule *module)
{
    module->updatePixelsWrapper(this->_pixels.get());
    module->updateTextsWrapper(this->_texts.get());
    module->display();
}

int Solarfox::getScore()
{
    return _score;
}

void Solarfox::generateEnemies()
{
    enemies.push_back(Enemy(10, 1, 0));
    enemies.push_back(Enemy (1, 10, 1));
    enemies.push_back(Enemy (10, 48, 2));
    enemies.push_back(Enemy (78, 10, 3));
    projectiles.push_back(Projectile(10, 0, 1, false));
    projectiles.push_back(Projectile(0, 10, 2, false));
    projectiles.push_back(Projectile(10, 48, 3, false));
    projectiles.push_back(Projectile(79, 10, 0, false));
    projectiles.push_back(Projectile(10, 0, 1, true));
}

void Solarfox::handleShipCollision()
{
    for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
        if (ship.rect_x == it->rect_x && ship.rect_y == it->rect_y && !it->isPlayer)
            reload();
    }
    for (int i = 0; i < 4; i++) {
        if (projectiles[i].rect_x == projectiles[4].rect_x && projectiles[i].rect_y == projectiles[4].rect_y && projectiles[i].isAlive) {
            projectiles[i].isAlive = false;
            projectiles[4].isAlive = false;
        }
    }
    for (auto it = mines.begin(); it != mines.end(); ++it) {
        if (ship.rect_x == it->rect_x && ship.rect_y == it->rect_y)
            reload();
    }
    for (auto jt = targets.begin(); jt != targets.end(); ++jt) {
        if (projectiles[4].rect_x == jt->rect_x && projectiles[4].rect_y == jt->rect_y && projectiles[4].isAlive) {
            this->_score += 1;
            jt = targets.erase(jt);
            break;
        }
    }
}

void Solarfox::displayBorders(Pixel &pixel, int i, int j)
{
    if ((i < 3 && j < gameSize_y - 2) || (i >= gameSize_x - 3 && j < gameSize_y - 2) || j < 3 || j >= gameSize_y - 3) {
        pixel.setType(IPixel::PixelType::DEFAULT);
        pixel.setRed(192);
        pixel.setGreen(192);
        pixel.setBlue(192);
        pixel.setChar('#');
    }
}

void Solarfox::displayMines(Pixel &pixel, int i, int j)
{
    for (auto& s : mines) {
        if (s.rect_x == i && s.rect_y == j) {
            pixel.setType(IPixel::PixelType::TEXTURED);
            pixel.setRed(255);
            pixel.setGreen(255);
            pixel.setBlue(0);
            pixel.setChar('M');
            pixel.setTexturePath("Assets/Solarfox/bombs.jpg");
            pixel.setRectPosition({0, 0});
            pixel.setRectSize({256, 256});
        }
    }
}

void Solarfox::displayEnemies(Pixel &pixel, int i, int j)
{
    for (int k = 0; k < 4; ++k) {
        if (i == enemies[k].rect_x && j == enemies[k].rect_y) {
            pixel.setRed(255);
            pixel.setGreen(255);
            pixel.setBlue(255);
            pixel.setChar('E');
        }
        if (enemies[k].direction == 1 || enemies[k].direction == 3) {
            if ((i == enemies[k].rect_x && j == enemies[k].rect_y - 1) || (i == enemies[k].rect_x && j == enemies[k].rect_y + 1)) {
                pixel.setRed(255);
                pixel.setGreen(255);
                pixel.setBlue(255);
                pixel.setChar('E');
            }
        }
        if (enemies[k].direction == 0 || enemies[k].direction == 2) {
            if ((i == enemies[k].rect_x - 1 && j == enemies[k].rect_y) || (i == enemies[k].rect_x + 1 && j == enemies[k].rect_y)) {
                pixel.setRed(255);
                pixel.setGreen(255);
                pixel.setBlue(255);
                pixel.setChar('E');
            }
        }
        if (projectiles[k].isAlive && i == projectiles[k].rect_x && j == projectiles[k].rect_y) {
            pixel.setTexturePath("Assets/Solarfox/ballon.png");
            pixel.setRectPosition({0, 0});
            pixel.setRectSize({100, 150});
            pixel.setRed(255);
            pixel.setGreen(0);
            pixel.setBlue(0);
            pixel.setChar('o');
        }
    }
}

void Solarfox::displayPlayer(Pixel &pixel, int i, int j)
{
    if (i == ship.rect_x && j == ship.rect_y) {
        pixel.setType(IPixel::PixelType::TEXTURED);
        pixel.setRed(0);
        pixel.setGreen(0);
        pixel.setBlue(255);
        pixel.setChar('S');
        pixel.setTexturePath("Assets/Solarfox/player.png");
        pixel.setRectPosition({0, 0});
        pixel.setRectSize({222, 242});
        if (this->direction_x == 1 && this->direction_y == 0) {
            pixel.setRotation(IPixel::Rotation::R90);
        } else if (this->direction_x == -1 && this->direction_y == 0) {
            pixel.setRotation(IPixel::Rotation::R270);
        } else if (this->direction_y == 1 && this->direction_x == 0) {
            pixel.setRotation(IPixel::Rotation::R180);
        } else if (this->direction_y == -1 && this->direction_x == 0) {
            pixel.setRotation(IPixel::Rotation::R0);
        }
    }
}

void Solarfox::displayPlayerProjectils(Pixel &pixel, int i, int j)
{
    if (projectiles[4].isAlive && i == projectiles[4].rect_x && j == projectiles[4].rect_y) {
        pixel.setType(IPixel::PixelType::TEXTURED);
        pixel.setRed(0);
        pixel.setGreen(255);
        pixel.setBlue(0);
        pixel.setChar('o');
        if (this->direction_x == 1 && this->direction_y == 0)
            pixel.setTexturePath("Assets/Solarfox/right_shot.png");
        else if (this->direction_x == -1 && this->direction_y == 0)
            pixel.setTexturePath("Assets/Solarfox/left_shot.png");
        else if (this->direction_y == 1 && this->direction_x == 0)
            pixel.setTexturePath("Assets/Solarfox/down_shot.png");
        else if (this->direction_y == -1 && this->direction_x == 0)
            pixel.setTexturePath("Assets/Solarfox/up_shot.png");
        pixel.setRectPosition({0, 0});
        pixel.setRectSize({100, 77});
    }
}

void Solarfox::displayTargets(Pixel &pixel, int i, int j)
{
    for (auto& s : targets) {
        if (s.rect_x == i && s.rect_y == j) {
            pixel.setType(IPixel::PixelType::TEXTURED);
            pixel.setRed(255);
            pixel.setGreen(0);
            pixel.setBlue(255);
            pixel.setChar('P');
            pixel.setTexturePath("Assets/Solarfox/tv.png");
            pixel.setRectPosition({0, 0});
            pixel.setRectSize({100, 100});
        }
    }
}

void Solarfox::createGamePixelWrapper()
{
    for (int i = 0; i < gameSize_x; ++i) {
        for (int j = 0; j < gameSize_y; ++j) {
            Pixel pixel;
            pixel.setType(IPixel::PixelType::TEXTURED);
            pixel.setTexturePath("Assets/Solarfox/background.jpg");
            pixel.setRectPosition({i * (683 / gameSize_x), j * (360 / (gameSize_y - 4))});
            pixel.setRectSize({683 / gameSize_x, 360 / (gameSize_y - 4)});
            if (j > gameSize_y - 4)
                pixel.setType(IPixel::PixelType::DEFAULT);
            pixel.setAlpha(255);
            displayBorders(pixel, i, j);
            displayMines(pixel, i, j);
            displayEnemies(pixel, i, j);
            displayPlayer(pixel, i, j);
            displayTargets(pixel, i, j);
            displayPlayerProjectils(pixel, i, j);
            this->_pixels->getPixelMap()[{i, j}] = pixel;
        }
    }
}

void Solarfox::createGameTextWrapper()
{
    Text scoreText;
    scoreText.setStr("Score: " + std::to_string(_score));
    scoreText.setRed(255);
    scoreText.setGreen(255);
    scoreText.setBlue(255);
    scoreText.setAlpha(255);
    this->_texts->getTextMap()[{gameSize_x + 5, 0}] = scoreText;
}

void Solarfox::moveEnemies(int i)
{
    switch (enemies[i].direction) {
        case 0:
            enemies[i].rect_x++;
            if (enemies[i].rect_x >= gameSize_x) {
                enemies[i].rect_x = gameSize_x;
                enemies[i].direction = 2;
            }
            break;
        case 1:
            enemies[i].rect_y++;
            if (enemies[i].rect_y >= gameSize_y - 4) {
                enemies[i].rect_y = gameSize_y - 4;
                enemies[i].direction = 3;
            }
            break;
        case 2:
            enemies[i].rect_x--;
            if (enemies[i].rect_x <= 0) {
                enemies[i].rect_x = 0;
                enemies[i].direction = 0;
            }
            break;
        case 3:
            enemies[i].rect_y--;
            if (enemies[i].rect_y <= 0) {
                enemies[i].rect_y = 0;
                enemies[i].direction = 1;
            }
            break;
    }
}
void Solarfox::moveEnemiesProjectiles(int i)
{
    if (projectiles[i].isAlive) {
        switch (projectiles[i].direction) {
            case 0:
                projectiles[i].rect_x++;
                break;
            case 1:
                projectiles[i].rect_y++;
                break;
            case 2:
                projectiles[i].rect_x--;
                break;
            case 3:
                projectiles[i].rect_y--;
                break;
        }
    }
}

void Solarfox::manageEnemiesShoots(int i)
{
    int tmp_dir = 0;

    if (projectiles[i].rect_x < 0 || projectiles[i].rect_x >= gameSize_x
        || projectiles[i].rect_y < 0 || projectiles[i].rect_y >= gameSize_y - 2)
        projectiles[i].isAlive = false;
    if (projectiles[i].isAlive == false) {
        switch (i) {
            case 0:
                tmp_dir = 1;
                break;
            case 1:
                tmp_dir = 0;
                break;
            case 2:
                tmp_dir = 3;
                break;
            case 3:
                tmp_dir = 2;
                break;
        }
        projectiles[i].rect_x = enemies[i].rect_x + (tmp_dir == 0 ? 0 : tmp_dir == 1 ? 1 : tmp_dir == 2 ? 0 : -1);
        projectiles[i].rect_y = enemies[i].rect_y + (tmp_dir == 0 ? 1 : tmp_dir == 1 ? 0 : tmp_dir == 2 ? -1 : 0);
        projectiles[i].direction = tmp_dir;
        projectiles[i].isAlive = true;
    }
}

void Solarfox::updatePosition()
{
    for (int i = 0; i < 4; i++) {
        moveEnemies(i);
        moveEnemiesProjectiles(i);
        manageEnemiesShoots(i);
    }
}

extern "C" {
    std::string getType() {
        return "game";
    }
    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<Solarfox>();
    }
}

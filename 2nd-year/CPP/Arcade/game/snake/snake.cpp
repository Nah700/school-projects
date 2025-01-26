/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** snake
*/

#include "snake.hpp"

int gameSize_x = 80;
int gameSize_y = 50;

void Snake::init()
{
    if (!this->snake.empty()) {
        stop();
    }
    createPixelsObject();
    createTextsObject();

    if (!this->isGameOver)
        this->_score = 0;
    for(int i = 0; i < 4; i++) {
        snake.push_back(Segment(1.6 - i * 0.05, 1));
    }
    this->_direction_x = 0;
    this->_direction_y = 0;
    this->_speed = 0.1;
    generateApple();
}

void Snake::updateScoreInFile()
{
    std::ifstream inFile("leaderboard.txt");
    std::string line;
    std::regex pattern("^([a-zA-Z0-9_]+) = (\\d+):(E|A)$");
    std::vector<std::string> lines;

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        return;
    }

    while (std::getline(inFile, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, pattern)) {
            std::string username = matches[1].str();
            if (matches[3].str() == "A") {
                int score = std::stoi(matches[2].str());
                score += this->_score;
                line = username + " = " + std::to_string(score) + ":" + matches[3].str();
            }
            lines.push_back(line);
        }
    }
    inFile.close();

    std::ofstream outFile("leaderboard.txt");
    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();
}

void Snake::stop()
{
    this->_pixels->getPixelMap().clear();
    this->_texts->getTextMap().clear();
    this->snake.clear();
    this->apple.clear();
    this->powerUp.clear();
    this->_direction_x = 0;
    this->_direction_y = 0;
    updateScoreInFile();
}

void Snake::applyEvents(arcade::IEvent *eventWrapper)
{
    arcade::Key key = eventWrapper->getEvent()->getKey();
    if (key != arcade::Key::KEY_LIST_END)
        applyEvent(key);
}


void Snake::applyEvent(const arcade::Key &key)
{
    if (key == arcade::Key::LEFT_ARROW) {
        if (this->_direction_x == 1) {
            this->_direction_x = 0;
            this->_direction_y = -1;
        } else if (this->_direction_x == -1) {
            this->_direction_x = 0;
            this->_direction_y = 1;
        } else if (this->_direction_y == 1) {
            this->_direction_x = 1;
            this->_direction_y = 0;
        } else if (this->_direction_y == -1) {
            this->_direction_x = -1;
            this->_direction_y = 0;
        } else if (this->_direction_x == 0 && this->_direction_y == 0) {
            this->_direction_x = 0;
            this->_direction_y = -1;
        }
    } else if (key == arcade::Key::RIGHT_ARROW) {
        if (this->_direction_x == 1) {
            this->_direction_x = 0;
            this->_direction_y = 1;
        } else if (this->_direction_x == -1) {
            this->_direction_x = 0;
            this->_direction_y = -1;
        } else if (this->_direction_y == 1) {
            this->_direction_x = -1;
            this->_direction_y = 0;
        } else if (this->_direction_y == -1) {
            this->_direction_x = 1;
            this->_direction_y = 0;
        } else if (this->_direction_x == 0 && this->_direction_y == 0) {
            this->_direction_x = 0;
            this->_direction_y = 1;
        }
    } else if (key == arcade::Key::SPACE) {
        this->isCyclical = !this->isCyclical;
    } else if (key == arcade::Key::ENTER) {
        if (this->isGameOver) {
            this->isGameOver = false;
            this->_score = 0;
        }
    }
}

int Snake::applyPowerUp(int type)
{
    if (type == 0) {
        this->_speed = 0.005;
        this->_poweruptime = 0;
    } else if (type == 1) {
        this->_speed = 0.3;
        this->_poweruptime = 0;
    } else if (type == 2) {
        this->_score += 10;
        if (this->snake.size() > 1)
            this->snake.pop_back();
        if (this->snake.size() < 2) {
            reload();
            return 1;
        }
    } else if (type == 3) {
        this->_score += 2;
        this->rainbowMod = true;
        this->_rainbowAttemps = 0;
    }
    return 0;
}
void Snake::reload()
{
    stop();
    this->isGameOver = true;
    init();
}

void Snake::handleCollision()
{
    if (snake.front().rect_x < 1) {
        if (isCyclical)
            snake.front().rect_x = gameSize_x - 2;
        else {
            reload();
        }
    } else if (snake.front().rect_x > gameSize_x - 2) {
        if (isCyclical)
            snake.front().rect_x = 1;
        else {
            reload();
        }
    } else if (snake.front().rect_y < 1) {
        if (isCyclical)
            snake.front().rect_y = gameSize_y - 5;
        else {
            reload();
        }
    } else if (snake.front().rect_y > gameSize_y - 5) {
        if (isCyclical)
            snake.front().rect_y = 1;
        else {
            reload();
        }
    }
}

void Snake::moveSystem()
{
    float prevPos_x = snake.front().rect_x;
    float prevPos_y = snake.front().rect_y;

    for (auto& s : snake) {
        float tempPos_x = s.rect_x;
        float tempPos_y = s.rect_y;
        s.rect_x = prevPos_x;
        s.rect_y = prevPos_y;
        prevPos_x = tempPos_x;
        prevPos_y = tempPos_y;
    }
    snake.front().rect_x += _direction_x;
    snake.front().rect_y += _direction_y;

    handleCollision();
    if (isSnakeEatingItself() && (this->_direction_x != 0
        || this->_direction_y != 0)) {
        reload();
    }
}

void Snake::displayBorders(int i, int j, Pixel &p)
{
    if ((i == 0 && j < gameSize_y - 4) || (i == gameSize_x - 1
        && j < gameSize_y - 4) || j == 0 || j == gameSize_y - 4) {
        p.setType(IPixel::PixelType::DEFAULT);
        p.setRed(192);
        p.setGreen(192);
        p.setBlue(192);
        p.setChar('#');
    }
}

void Snake::displayPowerUp(int i, int j, Pixel &p)
{
    for (auto& pu : powerUp) {
        if (i == pu.rect_x && j == pu.rect_y) {
            if (pu.getType() == 0) {
                p.setType(IPixel::PixelType::DEFAULT);
                p.setRed(41);
                p.setGreen(255);
                p.setBlue(235);
                p.setChar('S');
            } else if (pu.getType() == 1) {
                p.setType(IPixel::PixelType::DEFAULT);
                p.setRed(122);
                p.setGreen(91);
                p.setBlue(6);
                p.setChar('F');
            } else if (pu.getType() == 2) {
                p.setType(IPixel::PixelType::DEFAULT);
                p.setRed(252);
                p.setGreen(56);
                p.setBlue(167);
                p.setChar('M');
            } else if (pu.getType() == 3) {
                p.setTexturePath("Assets/Snake/pommes.png");
                p.setRectPosition({0, 0});
                p.setRectSize({224, 224});
                p.setChar('X');
                p.setRotation(IPixel::Rotation::R90);
            }
        }
    }
}

void Snake::displayApple(int i, int j, Pixel &p)
{
    for (auto& a : apple) {
        if (i == a.rect_x && j == a.rect_y) {
            p.setTexturePath("Assets/Snake/apple.png");
            p.setRectPosition({0, 0});
            p.setRectSize({40, 40});
            p.setRed(255);
            p.setGreen(0);
            p.setBlue(0);
            p.setAlpha(255);
            p.setChar('A');
        }
    }
}

void Snake::displaySnake(int i, int j, Pixel &p)
{
    int k = 0;

    for (auto& s : snake) {
        if (s.rect_x == i && s.rect_y == j) {
            if (k == 0) {
                p.setType(IPixel::PixelType::TEXTURED);
                p.setRectPosition({0, 0});
                p.setRectSize({40, 40});
                if (this->_direction_x == 1 || (this->_direction_x == 0 && this->_direction_y == 0))
                    p.setTexturePath("Assets/Snake/head_right.png");
                else if (this->_direction_x == -1)
                    p.setTexturePath("Assets/Snake/head_left.png");
                else if (this->_direction_y == 1)
                    p.setTexturePath("Assets/Snake/head_down.png");
                else if (this->_direction_y == -1)
                    p.setTexturePath("Assets/Snake/head_up.png");
            } else
                p.setType(IPixel::PixelType::DEFAULT);
            p.setRed(std::get<0>(this->_color));
            p.setGreen(std::get<1>(this->_color));
            p.setBlue(std::get<2>(this->_color));
            p.setAlpha(255);
            p.setChar('o');
            break;
        }
        k++;
    }
}

void Snake::displayGameover(int j, Pixel &p)
{
    if (!this->isGameOver)
        return;
    if (j >= gameSize_y / 3 && j <= gameSize_y / 2 + 2) {
        p.setType(IPixel::PixelType::DEFAULT);
        p.setRed(0);
        p.setGreen(0);
        p.setBlue(0);
        p.setAlpha(255);
    }
}

void Snake::create_snake_pixel_wrapper()
{
    for (int i = 0; i < gameSize_x; i++) {
        for (int j = 0; j < gameSize_y; j++) {
            Pixel p;
            p.setType(IPixel::PixelType::TEXTURED);
            p.setTexturePath("Assets/Snake/background.png");
            p.setRectPosition({i * (1920 / gameSize_x), j * (1080 / (gameSize_y - 4))});
            p.setRectSize({1920 / gameSize_x, 1080 / (gameSize_y - 4)});
            if (j > gameSize_y - 4)
                p.setType(IPixel::PixelType::DEFAULT);
            p.setRed(0);
            p.setGreen(0);
            p.setBlue(0);
            p.setAlpha(255);
            displayBorders(i, j, p);
            displayPowerUp(i, j, p);
            displayApple(i, j, p);
            displaySnake(i, j, p);
            displayGameover(j, p);
            this->_pixels->getPixelMap()[{i, j}] = p;
        }
    }
}

void Snake::create_snake_text_wrapper()
{
    Text t;

    t.setStr("Score: " + std::to_string(this->_score));
    t.setRed(255);
    t.setGreen(255);
    t.setBlue(255);
    t.setAlpha(255);

    if (this->isGameOver) {
        this->_texts->getTextMap()[{gameSize_x / 2, gameSize_y / 2 - 1}] = t;
        t.setStr("Press Enter to restart");
        this->_texts->getTextMap()[{gameSize_x / 2 - 3, gameSize_y / 2}] = t;
    } else {
        this->_texts->getTextMap()[{gameSize_x + 5, 0}] = t;
    }

    t.setStr("Cyclical mod: " + std::string(this->isCyclical ? "ON" : "OFF"));

    this->_texts->getTextMap()[{gameSize_x + 5, 2}] = t;

    if (this->isGameOver) {
        t.setStr("Game Over");
        t.setRed(255);
        t.setGreen(0);
        t.setBlue(0);
        this->_texts->getTextMap()[{gameSize_x / 2, gameSize_y / 2 - 4}] = t;
    }
}

bool Snake::forceApplePosition(Apple currentApple, int attempts)
{
    if (attempts >= 100) {
        for (int x = 0; x < gameSize_x; x++) {
            for (int y = 0; y < gameSize_y; y++) {
                if (!isPositionOccupied(x, y)) {
                    currentApple.rect_x = x;
                    currentApple.rect_y = y;
                    this->apple.push_back(currentApple);
                    return false;
                }
            }
        }
    }
    return true;
}

void Snake::generateApple()
{
    int attempts = 0;

    if (this->apple.size() >= 5)
        return;
    Apple currentApple;
    while (true) {
        currentApple.rect_x = rand() % gameSize_x;
        currentApple.rect_y = rand() % gameSize_y;

        if (!isPositionOccupied(currentApple.rect_x, currentApple.rect_y) || attempts >= 100) {
            this->apple.push_back(currentApple);
            break;
        }
        attempts++;
        if (!forceApplePosition(currentApple, attempts))
            break;
    }
}

bool Snake::isPositionOccupied(float x, float y)
{
    for (const auto& segment : snake) {
        if (segment.rect_x == x && segment.rect_y == y)
            return true;
    }
    for (const auto& p : powerUp) {
        if (p.rect_x == x && p.rect_y == y)
            return true;
    }
    for (const auto& a : apple) {
        if (a.rect_x == x && a.rect_y == y)
            return true;
    }
    if (x < 1 || y < 1 || x >= gameSize_x - 2 || y >= gameSize_y - 4)
        return true;
    return false;
}

void Snake::eatApple()
{
    for (auto it = apple.begin(); it != apple.end();) {
        if (snake.front().rect_x == it->rect_x && snake.front().rect_y == it->rect_y) {
            Segment newSegment(snake.back().rect_x, snake.back().rect_y);
            snake.push_back(newSegment);
            this->_score++;
            it = apple.erase(it);
        } else {
            ++it;
        }
    }
}

bool Snake::isSnakeEatingItself() const
{
    auto head = snake.front();
    for (auto it = std::next(snake.begin()); it != snake.end(); ++it) {
        if (it->rect_x == head.rect_x && it->rect_y == head.rect_y) {
            return true;
        }
    }
    return false;
}

void Snake::forcePowerUpPosition(int attempts)
{
    if (attempts >= 100) {
        for (int x = 0; x < gameSize_x; x++) {
            for (int y = 0; y < gameSize_y; y++) {
                if (!isPositionOccupied(x, y)) {
                    PowerUp p(x, y, rand() % 4);
                    this->powerUp.push_back(p);
                    return;
                }
            }
        }
    }
}

void Snake::generatePowerUp()
{
if (this->clock2 - this->decale2 > 5.0) {
    this->decale2 = this->clock2;
    generateApple();
    if (this->powerUp.size() < 3) {
        int attempts = 0;
        while (true) {
            int x = rand() % gameSize_x;
            int y = rand() % gameSize_y;
            if (!isPositionOccupied(x, y)) {
                PowerUp p(x, y, rand() % 4);
                this->powerUp.push_back(p);
                break;
            }
            attempts++;
            forcePowerUpPosition(attempts);
        }
    }
}

}
void Snake::managePowerUp(float deltaTime)
{
    float waiter = 0.3f;
    if (this->_speed != 0.1f) {
        this->_poweruptime += deltaTime;
        waiter = this->_speed == 0.005f ? 1.0f : 0.3f;
        if (this->_poweruptime >= waiter) {
            this->_speed = 0.1f;
            this->_poweruptime = 0;
        }
    }
    for (auto it = this->powerUp.begin(); it != this->powerUp.end(); ++it) {
        if (it->rect_x == this->snake.front().rect_x
            && it->rect_y == this->snake.front().rect_y) {
            if (applyPowerUp(it->getType()) == 1)
                return;
            it = this->powerUp.erase(it);
            break;
        }
    }
    generatePowerUp();
}

void Snake::manageRainbowMod()
{
    if (this->rainbowMod) {
        this->_rainbowAttemps++;
        this->_color = {rand() % 255, rand() % 255, rand() % 255};
        if (this->_rainbowAttemps >= 100) {
            this->rainbowMod = false;
            this->_color = {51, 153, 255};
        }
    }
}

void Snake::update(float deltaTime)
{
    this->clock += deltaTime;
    this->clock2 += deltaTime;
    this->_pixels->getPixelMap().clear();
    this->_texts->getTextMap().clear();

    if (this->clock - this->decale > this->_speed
        && (this->_direction_x != 0 || this->_direction_y != 0) && !this->isGameOver) {
        this->decale = this->clock;
        moveSystem();
        eatApple();
        managePowerUp(deltaTime);
        manageRainbowMod();
    }
    create_snake_pixel_wrapper();
    create_snake_text_wrapper();
}

int Snake::getScore()
{
    return this->_score;
}

void Snake::draw(arcade::IGraphicalModule *module)
{
    module->updatePixelsWrapper(this->_pixels.get());
    module->updateTextsWrapper(this->_texts.get());
    module->display();
}

extern "C" {
    std::string getType() {
        return "game";
    }
    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<Snake>();
    }
}

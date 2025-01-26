/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** menu
*/

#include "menu.hpp"

int gameSize_x = 100;
int gameSize_y = 50;

void Menu::getUsernameFromFile()
{
    std::ifstream inFile("leaderboard.txt");
    std::string line;
    std::regex pattern("^([a-zA-Z0-9_]+) = (\\d+):(E|A)$");
    std::vector<std::string> lines;

    while (std::getline(inFile, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, pattern)) {
            std::string username = matches[1].str();
            if (matches[3].str() == "A") {
                this->_username = username;
                this->userNameFound = true;
                this->_leaderboard[username] = std::stoi(matches[2].str());
            }
        }
    }
    inFile.close();
}

void Menu::init()
{
    int hauteur = 0;
    int k = 0;
    createPixelsObject();
    createTextsObject();
    createLibArray();

    this->_score = 0;
    for (long unsigned int i = 0; i < 10 && i < this->_lib.size(); i++) {
        if (i > 4 && k > 4) {
            k = 0;
            hauteur = 10;
        }
        this->_buttons.push_back(Button((k + 2.5) * 10, 30 + hauteur, 7, 4, i));
        k++;
    }
    getInfosfromFile(0);
    getUsernameFromFile();
}

void Menu::stop()
{
    this->_pixels->getPixelMap().clear();
    this->_texts->getTextMap().clear();
    this->_lib.clear();
    this->_buttons.clear();
    this->_launchGame.clear();
    this->inUsername = false;
    this->usernametoolong = false;
    this->_leaderboard.clear();
    this->userNameFound = false;
    this->inLeaderBoard = false;
    this->_username.clear();

    this->_score = -1;
}

void Menu::create_menu_pixel_wrapper()
{
    for (int i = 0; i < gameSize_y; i++) {
        for (int j = 0; j < gameSize_x; j++) {
            Pixel p;
            p.setAlpha(255);
            p.setType(IPixel::PixelType::TEXTURED);
            p.setTexturePath("Assets/Menu/menu_background.png");
            p.setRectPosition({j * (1920 / gameSize_x), i * (1080 / gameSize_y)});
            p.setRectSize({1920 / gameSize_x, 1080 / gameSize_y});
            for (auto &button : this->_buttons) {
                if (button.isButton(j, i)) {
                    p.setType(IPixel::PixelType::DEFAULT);
                    if (this->_score == button.getId()) {
                        p.setRed(200);
                        p.setGreen(0);
                        p.setBlue(222);
                        p.setChar('X');
                    } else {
                        p.setRed(255);
                        p.setGreen(255);
                        p.setBlue(255);
                        p.setChar('O');
                    }
                }
            }
            this->_pixels->getPixelMap()[{j, i}] = p;
        }
    }
}

void Menu::applyEvents(arcade::IEvent *eventWrapper)
{
    arcade::Key key = eventWrapper->getEvent()->getKey();
    while (!this->_launchGame.empty()) {
        eventWrapper->pushChangeEvent(this->_launchGame.front());
        this->_launchGame.pop_front();
    }
    if (key != arcade::Key::KEY_LIST_END)
        applyEvent(key);
}

bool Menu::updateUsernameInFile(std::string &username, int flag)
{
    std::ifstream inFile("leaderboard.txt");
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();

    if (fileContent.find(username) == std::string::npos) {
        if (flag == 1) {
            std::ofstream outFile("leaderboard.txt", std::ios_base::app);
            outFile << username << " = 0:A\n";
            outFile.close();
        }
        inFile.close();
        return false;
    }
    inFile.close();
    return true;
}

bool Menu::manageLeaderBoard(const arcade::Key &key)
{
    if (this->inLeaderBoard) {
        if (key == arcade::Key::E_KEY) {
            this->inLeaderBoard = false;
            return true;
        }
    }
    return false;

}
bool Menu::manageUsername(const arcade::Key &key)
{
    if (this->inUsername) {
        this->_tryingToLaunch = false;
        if (key == arcade::Key::DELETE && this->_username.size() > 0) {
            if (this->_username.size() == 23) {
                this->_username.clear();
            } else {
                this->_username.pop_back();
            }
        } else if (key == arcade::Key::ENTER) {
            if (this->_username.size() < 1 || this->_username.size() > 10) {
                this->_username = "Enter a valid username!";
                this->usernametoolong = true;
                return false;
            }
            this->inUsername = false;
            getInfosfromFile(0);
            return true;
        } else if (key != arcade::Key::ENTER && key != arcade::Key::DELETE && (this->_username.size() < 12 || this->_username.size() == 23)) {
            if (this->_username.size() == 23)
                this->_username.clear();
            this->_username.push_back(getKeyChar(key));
        }
        if (this->_username.size() > 10 || this->_username.size() == 23) {
            this->usernametoolong = true;
        } else {
            this->usernametoolong = false;
        }
        return false;
    }
    return false;
}

void Menu::manageEnterButton()
{
    if (!this->_username.empty() && !this->usernametoolong) {
        if ((long unsigned int)this->_score > this->_lib.size() - 1)
            return;
        if (this->_score == 0) {
            this->_launchGame.push_back(arcade::ChangeKey::NEXT_GAME_LIB);
            this->_launchGame.push_back(arcade::ChangeKey::PREV_GAME_LIB);
        } else {
            for (int i = 0; i < this->_score; i++)
                this->_launchGame.push_back(arcade::ChangeKey::NEXT_GAME_LIB);
        }
        updateUsernameInFile(this->_username, 1);
    } else {
        this->_tryingToLaunch = true;
    }
}

void Menu::applyEvent(const arcade::Key &key)
{
    if (manageLeaderBoard(key) || manageUsername(key))
        return;
    if (key == arcade::Key::LEFT_ARROW && this->_score != 0) {
        this->_score--;
    }
    else if (key == arcade::Key::RIGHT_ARROW && static_cast<std::vector<std::string>::size_type>(this->_score + 1) < this->_lib.size()) {
        this->_score++;
    }
    else if (key == arcade::Key::UP_ARROW && this->_score > 4) {
        this->_score -= 5;
    }
    else if (key == arcade::Key::DOWN_ARROW && this->_score < 5 && static_cast<std::vector<std::string>::size_type>(this->_score + 5) < this->_lib.size()) {
        this->_score += 5;
    } else if (key == arcade::Key::E_KEY && !this->inUsername) {
        this->inLeaderBoard = true;
    }
    else if (key == arcade::Key::ENTER && !this->inUsername && !this->inLeaderBoard) {
        manageEnterButton();
    } else if (key == arcade::Key::T_KEY && !this->userNameFound) {
        this->inUsername = true;
    }
}

std::string Menu::getInfosfromFile(int flag)
{
    std::ifstream inFile("leaderboard.txt");
    std::string line;
    std::regex pattern("^([a-zA-Z0-9_]+) = (\\d+):(E|A)$");
    std::vector<std::string> lines;

    while (std::getline(inFile, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, pattern)) {
            if (flag == 1) {
                if (matches[3].str() == "A" && flag == 1) {
                    inFile.close();
                    return matches[1].str();
                }
            }
            if (flag == 0) {
                std::string username = matches[1].str();
                int score = std::stoi(matches[2].str());
                if (this->_username == username) {
                    this->userNameFound = true;
                    if (matches[3].str() == "E") {
                        line = username + " = " + std::to_string(score) + ":A";
                    }
                }
                lines.push_back(line);
                this->_leaderboard[username] = score;
            }
        }
    }
    inFile.close();

    std::ofstream outFile("leaderboard.txt");
    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();

    return "";
}

void Menu::displayLibsTextButton()
{
    int hauteur = 0;
    int k = 0;

    for (long unsigned int i = 0; i < this->_lib.size(); i++) {
        Text t2;
        t2.setRed(255);
        t2.setGreen(0);
        t2.setBlue(0);
        t2.setAlpha(255);
        if (i > 4 && k > 4) {
            k = 0;
            hauteur = 10;
        }
        t2.setStr(extractSubstring(this->_lib[i]));
        this->_texts->getTextMap()[{(k + 2.9) * 10, 33 + hauteur}] = t2;
        k++;
    }
}

void Menu::create_menu_text_wrapper()
{
    Text t;

    t.setStr("Arcade");
    t.setRed(255);
    t.setGreen(255);
    t.setBlue(255);
    t.setAlpha(255);

    this->_texts->getTextMap()[{gameSize_x / 2 - 2, gameSize_y / 3}] = t;
    t.setStr("Press ESC to quit the game");
    this->_texts->getTextMap()[{(gameSize_x / 10) * 8.5, 0}] = t;
    t.setStr("Press E to see leaderboard");
    this->_texts->getTextMap()[{(gameSize_x / 10) * 8.5, 1}] = t;

    displayLibsTextButton();
    enteringUsername();

    if (this->_tryingToLaunch) {
        tryToLaunch();
    }
}

void Menu::tryToLaunch()
{
    Text t;
    t.setStr("Enter a usernam before starting a game!");
    t.setRed(255);
    t.setGreen(255);
    t.setBlue(255);
    t.setAlpha(255);

    this->_texts->getTextMap()[{gameSize_x / 2 - 10, gameSize_y / 2}] = t;

}

void Menu::enteringUsername()
{
    Text t;

    if (this->inUsername) {
        t.setStr("Enter your username: " + this->_username);
    } else if (this->_username.empty()) {
        t.setStr("Press T to enter your username");
    } else {
        t.setStr("Welcome: " + this->_username + "! We are so happy to see you!");
    }
    t.setRed(255);
    t.setGreen(255);
    t.setBlue(255);
    if (this->usernametoolong) {
        t.setGreen(0);
        t.setBlue(0);
    }
    t.setAlpha(255);

    this->_texts->getTextMap()[{1, 0}] = t;
    if (this->userNameFound) {
        Text t2;
        t2.setStr("Your score: " + std::to_string(this->_leaderboard[this->_username]));
        t2.setRed(255);
        t2.setGreen(255);
        t2.setBlue(255);
        t2.setAlpha(255);

        this->_texts->getTextMap()[{1, 2}] = t2;
    }
}

void Menu::create_leaderboard_pixel_wrapper()
{
    for (int i = 0; i < gameSize_y; i++) {
        for (int j = 0; j < gameSize_x; j++) {
            Pixel p;
            p.setAlpha(255);
            p.setRed(1);
            p.setGreen(1);
            p.setBlue(1);
            if ((j == 10 || j == gameSize_x - 15)) {
                p.setRed(255);
                p.setGreen(255);
                p.setBlue(255);
                p.setChar('O');
                this->_pixels->getPixelMap()[{j, i}] = p;
            }
            this->_pixels->getPixelMap()[{j, i}] = p;
        }
    }
}

void Menu::createLeaderBoard()
{
    Text t;
    t.setStr("Leaderboard");
    t.setRed(255);
    t.setGreen(255);
    t.setBlue(255);
    t.setAlpha(255);

    this->_texts->getTextMap()[{gameSize_x / 2 - 3, gameSize_y / 8}] = t;

    t.setStr("Press E to go back to the menu");

    this->_texts->getTextMap()[{(gameSize_x / 10) * 7, 0}] = t;
    int i = 0;
    for (auto &elem : this->_leaderboard) {
        Text t2;
        t2.setStr(elem.first + " : " + std::to_string(elem.second));
        t2.setRed(255);
        t2.setGreen(255);
        t2.setBlue(255);
        t2.setAlpha(255);

        this->_texts->getTextMap()[{gameSize_x / 2 - 2, gameSize_y / 3 + i * 2 + 2}] = t2;
        i++;
    }
}

void Menu::update(float deltaTime)
{
    deltaTime = deltaTime;
    this->_pixels->getPixelMap().clear();
    this->_texts->getTextMap().clear();

    if (!this->inLeaderBoard) {
        create_menu_pixel_wrapper();
        create_menu_text_wrapper();
    } else {
        create_leaderboard_pixel_wrapper();
        createLeaderBoard();
    }
}

void Menu::reload()
{
    stop();
    init();
}

void Menu::draw(arcade::IGraphicalModule *module)
{
    module->updatePixelsWrapper(this->_pixels.get());
    module->updateTextsWrapper(this->_texts.get());
    module->display();
}

int Menu::getScore()
{
    return this->_score;
}

std::string Menu::extractSubstring(const std::string& input)
{
    size_t first = input.find_first_of('_') + 1;
    size_t last = input.find_last_of('.');
    if (first == std::string::npos || last == std::string::npos || first >= last) {
        return "";
    }
    return input.substr(first, last - first);
}

void Menu::createLibArray()
{
    arcade::LibHandler tmp = arcade::LibHandler();
    std::vector<std::string> fileNames;
    for (auto &entry : std::filesystem::directory_iterator("./lib")) {
        fileNames.push_back(entry.path().string());
        std::string entryName = std::string(entry.path().string());
        if (entryName.find("arcade_") != std::string::npos){
            tmp.ArcadeDlopen(entryName.c_str());
            auto type = reinterpret_cast<std::string(*)()>(tmp.ArcadeDlsym("getType"));
            if (type == NULL)
                continue;
            std::string result = type();
            if (result == "game")
                this->_lib.push_back(entryName);
            tmp.ArcadeDlclose();
        }
    }
}

char Menu::getKeyChar(arcade::Key key)
{
    switch(key) {
        case arcade::Key::A_KEY:
            return 'A';
        case arcade::Key::B_KEY:
            return 'B';
        case arcade::Key::C_KEY:
            return 'C';
        case arcade::Key::D_KEY:
            return 'D';
        case arcade::Key::E_KEY:
            return 'E';
        case arcade::Key::F_KEY:
            return 'F';
        case arcade::Key::G_KEY:
            return 'G';
        case arcade::Key::H_KEY:
            return 'H';
        case arcade::Key::I_KEY:
            return 'I';
        case arcade::Key::J_KEY:
            return 'J';
        case arcade::Key::K_KEY:
            return 'K';
        case arcade::Key::L_KEY:
            return 'L';
        case arcade::Key::M_KEY:
            return 'M';
        case arcade::Key::N_KEY:
            return 'N';
        case arcade::Key::O_KEY:
            return 'O';
        case arcade::Key::P_KEY:
            return 'P';
        case arcade::Key::Q_KEY:
            return 'Q';
        case arcade::Key::R_KEY:
            return 'R';
        case arcade::Key::S_KEY:
            return 'S';
        case arcade::Key::T_KEY:
            return 'T';
        case arcade::Key::U_KEY:
            return 'U';
        case arcade::Key::V_KEY:
            return 'V';
        case arcade::Key::W_KEY:
            return 'W';
        case arcade::Key::X_KEY:
            return 'X';
        case arcade::Key::Y_KEY:
            return 'Y';
        case arcade::Key::Z_KEY:
            return 'Z';
        case arcade::Key::SPACE:
            return ' ';
        default:
            return '\0';
    }
}

extern "C" {
    std::string getType() {
        return "mainMenu";
    }
    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<Menu>();
    }
}
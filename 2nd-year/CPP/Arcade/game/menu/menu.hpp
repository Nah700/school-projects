/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include <list>
#include <cstdlib>
#include <unistd.h>
#include <filesystem>
#include <map>
#include "../APixels.hpp"
#include "../Pixel.hpp"
#include "../ATexts.hpp"
#include "../AGameModule.hpp"
#include "../../LibHandler.hpp"

class Button {
    public:
        Button(int x = 0, int y = 0, int width = 0, int height = 0, int id = 0)
        {
            this->_x = x;
            this->_y = y;
            this->_width = width;
            this->_height = height;
            this->_id = id;
        }

        bool isButton(int x, int y)
        {
            if (x >= this->_x && x <= this->_x + this->_width && y >= this->_y && y <= this->_y + this->_height)
                return true;
            return false;
        }

        int getId()
        {
            return this->_id;
        }

    private:
        int _x;
        int _y;
        int _width;
        int _height;
        std::string _text;
        int _id;
};

class Menu : public arcade::AGameModule
{
    public:
        Menu() = default;
        ~Menu() = default;

        void init();
        void stop();
        void applyEvents(arcade::IEvent *eventWrapper);
        void applyEvent(const arcade::Key &key);
        void update(float deltaTime);
        void reload();
        void draw(arcade::IGraphicalModule *module);
        int getScore();

        void getUsernameFromFile();
        void create_menu_pixel_wrapper();
        char getKeyChar(arcade::Key key);
        bool updateUsernameInFile(std::string &username, int flag);
        bool manageLeaderBoard(const arcade::Key &key);
        bool manageUsername(const arcade::Key &key);
        void manageEnterButton();
        std::string getInfosfromFile(int flag);
        void displayLibsTextButton();
        void create_menu_text_wrapper();
        void tryToLaunch();
        void enteringUsername();
        void create_leaderboard_pixel_wrapper();
        void createLeaderBoard();
        std::string extractSubstring(const std::string& input);
        void createLibArray();

    private:
        int _score = 0;
        std::list<Button> _buttons;
        std::list<arcade::ChangeKey> _launchGame;
        std::vector<std::string> _lib;
        std::string _username;
        bool inUsername = false;
        bool usernametoolong = false;
        bool _tryingToLaunch = false;
        std::map<std::string, int> _leaderboard;
        bool userNameFound = false;
        bool inLeaderBoard = false;
};

#endif /* !MENU_HPP_ */

/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** Main
*/

#include <memory>
#include <dirent.h>
#include <filesystem>
#include <cstring>
#include <chrono>
#include "Core.hpp"

namespace arcade {

    LibHandler *Core::getGraphicLibHandler()
    {
        return this->_graphicLibHandler.get();
    }

    LibHandler *Core::getGameLibHandler()
    {
        return this->_gameLibHandler.get();
    }

    IGraphicalModule *Core::getGraphicInstance()
    {
        return this->_graphicLib.get();
    }

    void Core::setGraphicInstance(std::unique_ptr<IGraphicalModule> graphicLib)
    {
        this->_graphicLib = std::move(graphicLib);
    }

    void Core::retrieveLibs(std::string firstLib)
    {
        LibHandler tmp = LibHandler();
        this->_graphicLibsNames.push_back(firstLib);
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
                if (result == "graphical" && entryName != ("./" + firstLib))
                    this->_graphicLibsNames.push_back(entryName);
                if (result == "game")
                    this->_gameLibsNames.push_back(entryName);
                if (result == "mainMenu")
                    this->_menu = entryName;
                tmp.ArcadeDlclose();
            }
        }
    }

    std::vector<std::string> Core::getGraphicLibsNames()
    {
        return this->_graphicLibsNames;
    }

    std::vector<std::string> Core::getGameLibsNames()
    {
        return this->_gameLibsNames;
    }

    void Core::initGraphicLib()
    {
        this->_graphicLibHandler.release(); 
        this->_graphicLibHandler = std::make_unique<LibHandler>();
        this->_graphicLibHandler->ArcadeDlopen(this->_graphicLibsNames[this->_currentGraphicLibIndex].c_str());
        this->_graphicLib.release();
        std::unique_ptr<IGraphicalModule> tmp = this->_graphicLibHandler->loadInstance<std::unique_ptr<IGraphicalModule>>();
        this->_graphicLib = std::move(tmp);
        this->_graphicLib->init();
    }

    void Core::changeToNextGraphicLib()
    {
        this->_currentGraphicLibIndex++;
        if (this->_currentGraphicLibIndex >= this->_graphicLibsNames.size())
            this->_currentGraphicLibIndex = 0;
        this->_graphicLib->stop();
        this->_graphicLibHandler->ArcadeDlclose();
        this->initGraphicLib();
    }

    void Core::changeToPreviousGraphicLib()
    {
        if (int(this->_currentGraphicLibIndex) - 1 < 0)
            this->_currentGraphicLibIndex = this->_graphicLibsNames.size() - 1;
        else
            this->_currentGraphicLibIndex--;
        this->_graphicLib->stop();
        this->_gameLibHandler->ArcadeDlclose();
        this->initGraphicLib();
    }

    void Core::initMenu()
    {
        this->_currentGameLibIndex = 0;
        this->_gameLibHandler.release();
        this->_gameLibHandler = std::make_unique<LibHandler>();
        this->_gameLibHandler->ArcadeDlopen(this->_menu.c_str());
        this->_gameLib.release();
        std::unique_ptr<IGameModule> tmp = this->_gameLibHandler->loadInstance<std::unique_ptr<IGameModule>>();
        this->_gameLib = std::move(tmp);
        this->_gameLib->init();
    }

    void Core::initGameLib()
    {
        this->_gameLibHandler.release();
        this->_gameLibHandler = std::make_unique<LibHandler>();
        this->_gameLibHandler->ArcadeDlopen(this->_gameLibsNames[this->_currentGameLibIndex].c_str());
        this->_gameLib.release();
        std::unique_ptr<IGameModule> tmp = this->_gameLibHandler->loadInstance<std::unique_ptr<IGameModule>>();
        this->_gameLib = std::move(tmp);
        this->_gameLib->init();
    }

    void Core::changeToNextGameLib()
    {
        this->_currentGameLibIndex++;
        if (this->_currentGameLibIndex >= this->_gameLibsNames.size())
            this->_currentGameLibIndex = 0;
        this->_gameLib->stop();
        this->_gameLibHandler->ArcadeDlclose();
        this->initGameLib();
    }

    void Core::changeToPreviousGameLib()
    {
        if (int(this->_currentGameLibIndex) - 1 < 0)
            this->_currentGameLibIndex = this->_gameLibsNames.size() - 1;
        else
            this->_currentGameLibIndex--;
        this->_gameLib->stop();
        this->_gameLibHandler->ArcadeDlclose();
        this->initGameLib();
    }

    void Core::switchToMenu()
    {
        this->_isMenu = true;
        this->_gameLib->stop();
        this->_gameLibHandler->ArcadeDlclose();
        this->initMenu();
    }

    void Core::applyChangeEvent()
    {
        ChangeKey changeKey = this->_graphicLib->getEventWrapper()->getChangeEvent()->getChangeKey();
        while (changeKey != arcade::ChangeKey::CHANGE_LIST_END){
            if (changeKey == arcade::ChangeKey::ESCAPE && this->_isMenu == true){
                this->_gameLib->stop();
                this->_isRunning = false;
            }
            if (changeKey == arcade::ChangeKey::NEXT_GRAPHICAL_LIB){
                this->changeToNextGraphicLib();
            }
            if (changeKey == arcade::ChangeKey::PREV_GRAPHICAL_LIB){
                for (long unsigned i = 0; i < this->_graphicLibsNames.size() - 1; i++)
                    this->changeToNextGraphicLib();
            }
            if (changeKey == arcade::ChangeKey::NEXT_GAME_LIB){
                this->changeToNextGameLib();
            }
            if (changeKey == arcade::ChangeKey::PREV_GAME_LIB){
                this->changeToPreviousGameLib();
            }
            if (changeKey == arcade::ChangeKey::MAIN_MENU){
                switchToMenu();
            }
            changeKey = this->_graphicLib->getEventWrapper()->getChangeEvent()->getChangeKey();
        }
    }

    void Core::update()
    {
        this->_graphicLib->pollEvents();
        if (this->_graphicLib->getWindowWrapper()->isOpen() == false){
            this->_isRunning = false;
            return;
        }
        auto eventWrapper = this->_graphicLib->getEventWrapper();
        this->_gameLib->applyEvents(eventWrapper);
        this->_clock->update();
        this->_gameLib->update(this->_clock->getDeltaTime());
        this->applyChangeEvent();
    }

    void Core::initWrappers()
    {
        initGraphicLib();
        initMenu();
        initClock();
    }

    void Core::initClock()
    {
        this->_clock = std::make_unique<Time>();
    }

    void Core::stopModules()
    {
        this->_graphicLib->stop();
        this->_gameLib->stop();
    }

    void Core::run()
    {
        int frameTime = 1000 / 60;

        this->initWrappers();
        while (this->_isRunning) {
            auto startTime = std::chrono::steady_clock::now();

            this->update();

            if (this->_isRunning == false)
                break;
            auto p = this->_graphicLib.get();
            this->_gameLib->draw(p);
            auto endTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            if (elapsedTime < frameTime)
                std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - elapsedTime));
        }
        this->stopModules();
    }

}
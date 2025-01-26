/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <dlfcn.h>
#include <iostream>
#include <thread>
#include <memory>
#include <unordered_map>
#include "ITime.hpp"
#include "graphical/IGraphicalModule.hpp"
#include "game/IGameModule.hpp"
#include "Time.hpp"
#include "LibHandler.hpp"
#include "LibError.hpp"

namespace arcade {
    class Core {
        public:
            //Lib handling functions
            Core() = default;
            ~Core() = default;
            IGraphicalModule *getGraphicInstance();
            void setGraphicInstance(std::unique_ptr<IGraphicalModule> graphicLib);
            LibHandler *getGraphicLibHandler();
            LibHandler *getGameLibHandler();

            //Core functions
            void retrieveLibs(std::string firstLib);
            std::vector<std::string> getGraphicLibsNames();
            std::vector<std::string> getGameLibsNames();
            void initWrappers();
            void initGraphicLib();
            void initClock();
            void initMenu();
            void stopModules();
            void initGameLib();
            void changeToNextGraphicLib();
            void changeToPreviousGraphicLib();
            void changeToNextGameLib();
            void changeToPreviousGameLib();
            void applyChangeEvent();
            void update();
            void run();
            void switchToMenu();
        private:
            std::unique_ptr<LibHandler> _gameLibHandler;
            std::unique_ptr<LibHandler> _graphicLibHandler;
            long unsigned int _currentGraphicLibIndex = 0;
            long unsigned int _currentGameLibIndex = 0;
            std::unique_ptr<IGraphicalModule> _graphicLib;
            std::unique_ptr<IGameModule> _gameLib;
            std::unique_ptr<Time> _clock;
            std::vector<std::string> _graphicLibsNames;
            std::vector<std::string> _gameLibsNames;
            std::string _menu;
            bool _isRunning = true;
            bool _isMenu = true;
    };
};

#endif /* !CORE_HPP_ */

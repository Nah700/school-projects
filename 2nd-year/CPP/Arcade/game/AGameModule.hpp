/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

#include <string>
#include <unordered_map>
#include "Pixel.hpp"
#include "../graphical/Pair.hpp"
#include <array>
#include <algorithm>
#include <memory>
#include "IGameModule.hpp"
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

namespace arcade
{
    class AGameModule : public IGameModule {
        public:
            virtual void init() = 0;
            virtual void stop() = 0;
            std::string getName() const;
            IPixels *getPixelsWrapper();
            ITexts *getTextsWrapper();
            virtual void applyEvents(IEvent *eventWrapper) = 0;
            virtual void update(float deltaTime) = 0;
            virtual void reload() = 0;
            virtual int getScore() = 0;
            virtual void draw(IGraphicalModule *module) = 0;
        protected:
            IPixels *createPixelsObject();
            ITexts *createTextsObject();
            virtual void applyEvent(const Key &key) = 0;
            std::unique_ptr<IPixels> _pixels;
            std::unique_ptr<ITexts> _texts;
        private:
            std::string _name = "game";
    };
}

#endif /* !AGAMEMODULE_HPP_ */

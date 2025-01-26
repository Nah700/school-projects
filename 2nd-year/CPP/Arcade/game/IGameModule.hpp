/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <string>
#include <unordered_map>
#include "Pixel.hpp"
#include <array>
#include <algorithm>
#include "../graphical/IGraphicalModule.hpp"
#include "./APixels.hpp"
#include "./ATexts.hpp"


namespace arcade {
    class IGameModule {
        public:
            virtual ~IGameModule() = default;
            virtual void init() = 0;
            virtual void stop() = 0;
            virtual std::string getName() const = 0;
            virtual IPixels *getPixelsWrapper() = 0;
            virtual ITexts *getTextsWrapper() = 0;
            virtual void applyEvents(IEvent *eventWrapper) = 0;
            virtual void update(float deltaTime) = 0;
            virtual void reload() = 0;
            virtual int getScore() = 0;
            virtual void draw(IGraphicalModule *module) = 0;
        protected:
            virtual IPixels *createPixelsObject() = 0;
            virtual ITexts *createTextsObject() = 0;
            virtual void applyEvent(const Key &key) = 0;
    };
};

/* extern C :

extern "C" {
    std::string getType() {
        return "game";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::Snake>();
    }
}

*/
#endif /* !IGAMEMODULE_HPP_ */
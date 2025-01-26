/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IGraphicalModule
*/

#ifndef IGRAPHICALMODULE_HPP_
#define IGRAPHICALMODULE_HPP_

#include <iostream>
#include <memory>
#include "IEvent.hpp"
#include "IWindow.hpp"
#include "../game/IPixels.hpp"

namespace arcade {
    class IGraphicalModule {
        public:
            virtual ~IGraphicalModule() = default;
            virtual void init() = 0;
            virtual void stop() = 0;
            virtual std::string getName() const = 0;
            virtual IEvent *getEventWrapper() const = 0;
            virtual IWindow *getWindowWrapper() const = 0;
            virtual void updatePixelsWrapper(IPixels *pixels) = 0;
            virtual void updateTextsWrapper(ITexts *texts) = 0;
            virtual void pollEvents() = 0;
            virtual void display() const = 0;
        protected:
            virtual IEvent *createEventObject() = 0;
            virtual IWindow *createWindowObject() = 0;
    };
};

#endif /* !IGRAPHICALMODULE_HPP_ */

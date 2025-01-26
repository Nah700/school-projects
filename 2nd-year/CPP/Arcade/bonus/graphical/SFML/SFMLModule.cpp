/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SFMLModule
*/

#include "SFMLModule.hpp"
#include "SFMLWindow.hpp"
#include "SFMLEvent.hpp"

namespace arcade {
    void SFMLModule::init()
    {
        createWindowObject();
        createEventObject();

        this->_window->openWindow(1920, 1080);
    }

    void SFMLModule::stop()
    {
        this->_window->closeWindow();
    }

    std::string SFMLModule::getName() const
    {
        return _name;
    }

    IEvent *SFMLModule::getEventWrapper() const
    {
        return this->_event.get();
    }

    IWindow *SFMLModule::getWindowWrapper() const
    {
        return this->_window.get();
    }

    IPixels *SFMLModule::getPixelsWrapper() const
    {
        return this->_pixels;
    }

    ITexts *SFMLModule::getTextsWrapper() const
    {
        return this->_texts;
    }

    void SFMLModule::updatePixelsWrapper(IPixels *pixels)
    {
        this->_pixels = pixels;
    }

    void SFMLModule::updateTextsWrapper(ITexts *texts)
    {
        this->_texts = texts;
    }

    void SFMLModule::display() const
    {
        this->getWindowWrapper()->clearScreen();
        this->getWindowWrapper()->displayPixels(this->getPixelsWrapper());
        this->getWindowWrapper()->displayTexts(this->getTextsWrapper());
        this->getWindowWrapper()->display();
    }

    void SFMLModule::pollEvents()
    {
        if (!this->getWindowWrapper()->isOpen())
            return;
        sf::Event event;
        while (((SFMLWindow *)this->getWindowWrapper())->getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->_window->closeWindow();
            if (event.type == sf::Event::KeyReleased) {
                auto exist = this->_keyMap.count(event.key.code);
                if (exist == 1) {
                    this->getEventWrapper()->pushEvent(this->_keyMap[event.key.code]);
                }
                exist = this->_changeKeyMap.count(event.key.code);
                if (exist == 1) {
                    this->getEventWrapper()->pushChangeEvent(this->_changeKeyMap[event.key.code]);
                }
            }
        }
    }

    IWindow *SFMLModule::createWindowObject() {
        this->_window = std::make_unique<SFMLWindow>();
        return this->_window.get();
    }

    IEvent *SFMLModule::createEventObject() {
        this->_event = std::make_unique<SFMLEvent>();
        return this->_event.get();
    }
};
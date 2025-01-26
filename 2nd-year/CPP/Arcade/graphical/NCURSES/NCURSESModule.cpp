/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** NCURSESModule
*/

#include "NCURSESModule.hpp"
#include "NCURSESWindow.hpp"
#include "NCURSESEvent.hpp"

namespace arcade {
    void NCURSESModule::init()
    {
        createWindowObject();
        createEventObject();
        this->_window->openWindow(1920, 1080);
    }

    void NCURSESModule::stop()
    {
        this->_window->closeWindow();
    }

    std::string NCURSESModule::getName() const
    {
        return _name;
    }

    IEvent *NCURSESModule::getEventWrapper() const
    {
        return this->_event.get();
    }

    IWindow *NCURSESModule::getWindowWrapper() const
    {
        return this->_window.get();
    }

    IPixels *NCURSESModule::getPixelsWrapper() const
    {
        return this->_pixels;
    }

    ITexts *NCURSESModule::getTextsWrapper() const
    {
        return this->_texts;
    }

    void NCURSESModule::updatePixelsWrapper(IPixels *pixels)
    {
        this->_pixels = pixels;
    }

    void NCURSESModule::updateTextsWrapper(ITexts *texts)
    {
        this->_texts = texts;
    }

    void NCURSESModule::display() const
    {
        this->getWindowWrapper()->clearScreen();
        this->getWindowWrapper()->displayPixels(this->getPixelsWrapper());
        this->getWindowWrapper()->displayTexts(this->getTextsWrapper());
        this->getWindowWrapper()->display();
    }

    void NCURSESModule::pollEvents()
    {
        timeout(0);
        int ch;
        while ((ch = getch()) && ch != ERR) {
            if (_keymap.contains(ch)) {
                this->getEventWrapper()->pushEvent(_keymap[ch]);
                // _event->pushEvent(_keymap[ch]);
            }
            if (_changeKeyMap.contains(ch)) {
                this->getEventWrapper()->pushChangeEvent(_changeKeyMap[ch]);
                // _event->pushChangeEvent(_changeKeyMap[ch]);
            }
        }
    }

    IEvent *NCURSESModule::createEventObject()
    {
        this->_event = std::make_unique<NCURSESEvent>();
        return this->_event.get();
    }

    IWindow *NCURSESModule::createWindowObject()
    {
        this->_window = std::make_unique<NCURSESWindow>();
        return this->_window.get();
    }

}

extern "C" {
    std::string getType() {
        return "graphical";
    }
    std::unique_ptr<arcade::IGraphicalModule> entryPoint() {
        return std::make_unique<arcade::NCURSESModule>();
    }
}
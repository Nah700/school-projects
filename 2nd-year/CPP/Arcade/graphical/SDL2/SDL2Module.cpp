/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SDL2Module
*/

#include "SDL2Module.hpp"
#include "SDLWindow.hpp"
#include "SDLEvent.hpp"

namespace arcade {
    IWindow *SDLModule::getWindowWrapper() const
    {
        return this->_window.get();
    }

    IEvent *SDLModule::getEventWrapper() const
    {
        return this->_event.get();
    }

    IPixels *SDLModule::getPixelsWrapper() const
    {
        return this->_pixels;
    }

    ITexts *SDLModule::getTextsWrapper() const
    {
        return this->_texts;
    }

    void SDLModule::updatePixelsWrapper(IPixels *pixels)
    {
        this->_pixels = pixels;
    }

    void SDLModule::updateTextsWrapper(ITexts *texts)
    {
        this->_texts = texts;
    }

    void SDLModule::init()
    {
        createWindowObject();
        createEventObject();
        this->_window->openWindow(1920, 950);
    }

    void SDLModule::stop()
    {
        this->_window->closeWindow();
        SDL_Quit();
    }

    std::string SDLModule::getName() const
    {
        return this->_name;
    }

    void SDLModule::pollEvents()
    {
        if (this->_window->isOpen() == false)
            return;
        while (SDL_PollEvent(&_sdlEvent)) {
            if (_sdlEvent.type == SDL_QUIT)
                this->_window->closeWindow();
            if (_sdlEvent.type == SDL_KEYDOWN){
                SDL_Keycode keyCode = _sdlEvent.key.keysym.sym;
                auto exist = this->_keyMap.count(SDL_KeyCode(keyCode));
                if (exist == 1) {
                    this->getEventWrapper()->pushEvent(this->_keyMap[SDL_KeyCode(keyCode)]);
                }
                exist = this->_changeKeyMap.count(SDL_KeyCode(keyCode));
                if (exist == 1) {
                    this->getEventWrapper()->pushChangeEvent(this->_changeKeyMap[SDL_KeyCode(keyCode)]);
                }
            }
        }
    }

    void SDLModule::display() const
    {
        this->getWindowWrapper()->clearScreen();
        this->getWindowWrapper()->displayPixels(this->getPixelsWrapper());
        this->getWindowWrapper()->displayTexts(this->getTextsWrapper());
        this->getWindowWrapper()->display();
    }
    
    IEvent *SDLModule::createEventObject()
    {
        this->_event = std::make_unique<SDLEvent>();
        return this->_event.get();
    }

    IWindow *SDLModule::createWindowObject()
    {
        this->_window = std::make_unique<SDLWindow>();
        return this->_window.get();
    }
};

extern "C" {
    std::string getType() {
        return "graphical";
    }
    std::unique_ptr<arcade::IGraphicalModule> entryPoint() {
        return std::make_unique<arcade::SDLModule>();
    }
}

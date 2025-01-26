/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SDLWindow
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../IWindow.hpp"
#include <map>


namespace arcade {
    class SDLWindow : public IWindow {
        public:
            SDLWindow() = default;
            ~SDLWindow() = default;
            void openWindow(int width, int height) override;
            void closeWindow() override;
            void resizeWindow(int width, int height) override;
            bool isOpen() const override;
            void clearScreen() override;
            void displayPixels(IPixels *pixels) override;
            void displayTexts(ITexts *texts) override;
            void display() override;
            SDL_Window *getWindow() const;
        protected:
        private:
            SDL_Window *_window = NULL;
            SDL_Renderer *_renderer = NULL;
            double _pixel_size;
            std::map<std::string, SDL_Texture *> _textures;
    };
};

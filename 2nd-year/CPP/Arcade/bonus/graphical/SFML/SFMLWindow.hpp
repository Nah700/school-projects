/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SFMLWindow
*/

#ifndef SFMLWINDOW_HPP_
#define SFMLWINDOW_HPP_

#include "SFMLModule.hpp"
#include "../Pair.hpp"

namespace arcade {
    class SFMLWindow : public IWindow {
        public:
            ~SFMLWindow() = default;
            void openWindow(int width, int height) override;
            void resizeWindow(int width, int height) override;
            bool isOpen() const override;
            void clearScreen() override;
            void closeWindow() override;
            void display() override;
            void displayPixels(IPixels *pixels) override;
            void displayTexts(ITexts *texts) override;
            sf::RenderWindow *getWindow() const;
        private:
            double _pixel_size;
            std::map<std::string, sf::Texture> _textures;
            sf::RenderWindow *_window;
    };
};

#endif /* !SFMLWINDOW_HPP_ */

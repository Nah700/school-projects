/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** NCURSESWindow
*/


#include "../IWindow.hpp"
#include <ncurses.h>
#include <vector>
#include <iostream>
#include <algorithm>

namespace arcade {
    class NCURSESWindow : public IWindow {
        public:
            NCURSESWindow() = default;
            ~NCURSESWindow() = default;
            void openWindow(int width, int height) override;
            void closeWindow() override;
            void resizeWindow(int width, int height) override;
            bool isOpen() const override;
            void clearScreen() override;
            void displayPixels(IPixels *pixels) override;
            void displayTexts(ITexts *texts) override;
            void display() override;
            void getColors() const;
            void checkColorSimilitude(Pixel &pixel);
        protected:
        private:
            WINDOW *_win;
            std::vector<Pixel> _color = {
                Pixel(0, 0, 0), // black
                Pixel(256, 0, 0), // red
                Pixel(0, 256, 0), // green
                Pixel(0, 0, 256), // blue
                Pixel(256, 256, 0), // yellow
                Pixel(256, 0, 256), // magenta
                Pixel(0, 256, 256), // cyan
                Pixel(256, 256, 256), // white
            };
    };
};

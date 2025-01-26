/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IWindow
*/

#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

#include <iostream>
#include <memory>
#include <vector>
#include "../game/IPixels.hpp"
#include "../game/ITexts.hpp"

class IWindow {
    public:
        virtual ~IWindow() = default;
        virtual void openWindow(int width, int height) = 0;
        virtual void closeWindow() = 0;
        virtual void resizeWindow(int width, int height) = 0;
        virtual bool isOpen() const = 0;
        virtual void clearScreen() = 0;
        virtual void displayPixels(arcade::IPixels *pixels) = 0;
        virtual void displayTexts(arcade::ITexts *texts) = 0;
        virtual void display() = 0;
};

#endif /* !IWINDOW_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** NCURSESWindow
*/

#include "NCURSESWindow.hpp"


namespace arcade {
    void NCURSESWindow::getColors() const
    {
        std::vector<std::pair<int, int>> colors = {
            {COLOR_BLACK, COLOR_BLACK},
            {COLOR_RED, COLOR_BLACK},
            {COLOR_GREEN, COLOR_BLACK},
            {COLOR_BLUE, COLOR_BLACK},
            {COLOR_YELLOW, COLOR_BLACK},
            {COLOR_MAGENTA, COLOR_BLACK},
            {COLOR_CYAN, COLOR_BLACK},
            {COLOR_WHITE, COLOR_BLACK}
        };

        for (size_t i = 0; i < colors.size(); ++i) {
            init_pair(i, colors[i].first, colors[i].second);
        }
    }

    void NCURSESWindow::openWindow(int width, int height)
    {
        width = width;
        height = height;
        initscr();
        start_color();
        getColors();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
    }

    void NCURSESWindow::closeWindow()
    {
        endwin();
    }

    void NCURSESWindow::resizeWindow(int width, int height)
    {
        resize_term(height, width);
    }

    bool NCURSESWindow::isOpen() const
    {
        if (!isendwin())
            return (true);
        return (false);
    }

    void NCURSESWindow::checkColorSimilitude(Pixel &pixel)
    {
        std::vector<int> similitude;
        int min = 0;

        for (auto &color : this->_color) {
            similitude.push_back(abs(color.getRed() - pixel.getRed()) + abs(color.getGreen() - pixel.getGreen()) + abs(color.getBlue() - pixel.getBlue()));
        }
        for (size_t i = 0; i < similitude.size(); i++) {
            if (similitude[i] < similitude[min])
                min = i;
        }
        attron(COLOR_PAIR(min));
    }

    void NCURSESWindow::displayPixels(IPixels *pixels)
    {
        double maxX = 0;
        double maxY = 0;
        auto &pixelMap = pixels->getPixelMap();
        for (auto &pixel : pixelMap) {
            if (pixel.first.first > maxX)
                maxX = pixel.first.first;
            if (pixel.first.second > maxY)
                maxY = pixel.first.second;
        }
        for (auto &pixel : pixelMap) {
            checkColorSimilitude(pixel.second);
            mvaddch(pixel.first.second, pixel.first.first, pixel.second.getChar());
        }
 
    }

    void NCURSESWindow::displayTexts(ITexts *texts)
    {
        double maxX = 0;
        double maxY = 0;
        auto &TextMap = texts->getTextMap();
        for (auto &text : TextMap) {
            if (text.first.first > maxX)
                maxX = text.first.first;
            if (text.first.second > maxY)
                maxY = text.first.second;
        }
    for (auto &pixel : TextMap) {
            mvprintw(pixel.first.second, pixel.first.first, "%s", pixel.second.getStr().c_str());
        }
    }

    void NCURSESWindow::clearScreen()
    {
        refresh();
        clear();
    }

    void NCURSESWindow::display()
    {
        return;
    }
};

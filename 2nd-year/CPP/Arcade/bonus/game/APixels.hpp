/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** APixels
*/

#ifndef APIXELS_HPP_
#define APIXELS_HPP_

#include <tuple>
#include <iostream>
#include "IPixels.hpp"
#include "../graphical/Pair.hpp"

typedef std::unordered_map<std::pair<int, int>, Pixel> PixelsMap;

class APixels : public arcade::IPixels {
    public:
        PixelsMap &getPixelMap();
        void updatePixelMap(const PixelsMap &pixels);
    private:
        PixelsMap _pixels;
};

#endif /* !APIXELS_HPP_ */
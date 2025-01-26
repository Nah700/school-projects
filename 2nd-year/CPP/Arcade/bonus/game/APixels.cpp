/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** APixels
*/

#include "APixels.hpp"

PixelsMap &APixels::getPixelMap()
{
    return _pixels;
}

void APixels::updatePixelMap(const PixelsMap &pixels)
{
    for (auto &value : pixels) {
        _pixels.insert(value);
    }
}

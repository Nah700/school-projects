/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IPixels
*/

#ifndef IPIXELS_HPP_
#define IPIXELS_HPP_

#include <unordered_map>
#include "./Pixel.hpp"

typedef std::unordered_map<std::pair<int, int>, Pixel> PixelsMap;

namespace arcade {
    class IPixels {
        public:
            virtual ~IPixels() = default;
            virtual PixelsMap &getPixelMap() = 0;
            virtual void updatePixelMap(const PixelsMap &pixels) = 0;
    };
};

#endif /* !IPIXELS_HPP_ */

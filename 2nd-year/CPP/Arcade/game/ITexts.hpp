/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** ITexts
*/

#ifndef ITEXTS_HPP_
#define ITEXTS_HPP_

#include <unordered_map>
#include "./Text.hpp"

typedef std::unordered_map<std::pair<int, int>, Text> TextMap;

namespace arcade {
    class ITexts {
        public:
            virtual ~ITexts() = default;
            virtual TextMap &getTextMap() = 0;
            virtual void updateTextMap(const TextMap &texts) = 0;
    };
};

#endif /* !ITEXTS_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** ATexts
*/

#ifndef ATEXTS_HPP_
#define ATEXTS_HPP_

#include <unordered_map>
#include "ITexts.hpp"
#include "../graphical/Pair.hpp"

typedef std::unordered_map<std::pair<int, int>, Text> TextMap;

namespace arcade {
    class ATexts : public ITexts {
        public:
            TextMap &getTextMap() override;
            void updateTextMap(const TextMap &texts) override;
        private:
            TextMap _texts;
    };
};

#endif /* !ATEXTS_HPP_ */

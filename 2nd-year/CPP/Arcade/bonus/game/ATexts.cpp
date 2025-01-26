/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** ATexts
*/

#include "ATexts.hpp"

namespace arcade {
    TextMap &ATexts::getTextMap() {
        return this->_texts;
    };

    void ATexts::updateTextMap(const TextMap &texts) {
        for (auto &value : texts) {
            this->_texts.insert(value);
        }
    };
};

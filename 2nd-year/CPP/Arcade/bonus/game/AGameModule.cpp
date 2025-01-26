/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

namespace arcade {
    std::string AGameModule::getName() const
    {
        return _name;
    }

    IPixels *AGameModule::getPixelsWrapper()
    {
        return this->_pixels.get();
    }

    ITexts *AGameModule::getTextsWrapper()
    {
        return this->_texts.get();
    }

    IPixels *AGameModule::createPixelsObject()
    {
        this->_pixels = std::make_unique<APixels>();
        return dynamic_cast<IPixels*>(this->_pixels.get());
    }

    ITexts *AGameModule::createTextsObject()
    {
        this->_texts = std::make_unique<ATexts>();
        return dynamic_cast<ITexts*>(this->_texts.get());
    }
};

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace nts {

    void AComponent::setLinkInOther(std::size_t pin, nts::IComponent *other, std::size_t otherPin)
    {
        std::pair<int, nts::IComponent *> tuple = {otherPin, other};
        this->_links[pin] = tuple;
    }

    void AComponent::setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin)
    {
        std::pair<int, nts::IComponent *> tuple = {otherPin, other};
        this->_links[pin] = tuple;
        other->setLinkInOther(otherPin, this, pin);
    }

    std::map<std::size_t, std::pair<size_t, IComponent *>> AComponent::getLinks()
    {
        return this->_links;
    }

    IComponent *AComponent::getLink(std::size_t pin)
    {
        if (this->_links.find(pin) == this->_links.end())
            return nullptr;
        return this->_links[pin].second;
    }

    size_t AComponent::getPin(std::size_t pin)
    {
        if (this->_links.find(pin) == this->_links.end())
            return 0;
        return this->_links[pin].first;
    }
}

std::ostream &operator<<(std ::ostream &s, nts::Tristate v)
{
    if (v == nts::UNDEFINED)
        s << "U";
    else if (v == nts::TRUE)
        s << "1";
    else
        s << "0";
    return s;
}

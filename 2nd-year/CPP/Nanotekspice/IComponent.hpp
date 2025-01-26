/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <iostream>
#include <map>
#include <vector>

namespace nts {
    enum Tristate {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void simulate(std::size_t tick) = 0;
            virtual void setLinkInOther(std::size_t pin, nts::IComponent *other, std::size_t otherPin) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin) = 0;
            virtual Tristate compute(std::size_t pin) = 0;
            virtual IComponent *getLink(std::size_t pin) = 0;
            virtual size_t getPin(std::size_t pin) = 0;
            virtual Tristate getStatusSpecial() = 0;
            virtual void setStatusSpecial(Tristate status) = 0;
            virtual int getMaxPin() const = 0;
            virtual std::vector<int> getBannedPin() const = 0;
            virtual void setActualTick(std::size_t tick) = 0;
        protected:
        private:
    };
};

    std::ostream &operator<<(std ::ostream &s, nts::Tristate v);

#endif /* !ICOMPONENT_HPP_ */

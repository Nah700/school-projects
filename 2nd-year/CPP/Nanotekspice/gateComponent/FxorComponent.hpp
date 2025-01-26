/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** FxorComponent
*/

#ifndef FXORCOMPONENT_HPP_
#define FXORCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class FxorComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 7 || pin == 14)
                    return UNDEFINED;
                if (pin == 3 || pin == 10 || pin == 4 || pin == 11) {
                    size_t pin1 = pin == 3 || pin == 10 ? pin - 1 : pin + 1;
                    size_t pin2 = pin == 3 || pin == 10 ? pin - 2 : pin + 2;
                    IComponent *link1 = this->getLink(pin1);
                    IComponent *link2 = this->getLink(pin2);

                    if (!link1 || !link2 || link1->compute(this->getPin(pin1)) == UNDEFINED || link2->compute(this->getPin(pin2)) == UNDEFINED)
                        return UNDEFINED;
                    if ((link1->compute(this->getPin(pin1)) == FALSE && link2->compute(this->getPin(pin2)) == FALSE)
                    || (link1->compute(this->getPin(pin1)) == TRUE && link2->compute(this->getPin(pin2)) == TRUE))
                        return FALSE;
                    return TRUE;
                }
                if (getLink(pin) != nullptr)
                    return getLink(pin)->compute(this->getPin(pin));
                return UNDEFINED;
            }
            void setStatusSpecial(Tristate status) override {};
            std::vector<int> getBannedPin() const override {
                return this->_banned_pin;
            }
            Tristate getStatusSpecial() override { return UNDEFINED; };
            int getMaxPin() const override {
                return max_pin;
            }
        protected:
        private:
            int max_pin = 14;
            std::vector<int> _banned_pin = {7, 14};
    };
};
#endif /* !FXORCOMPONENT_HPP_ */

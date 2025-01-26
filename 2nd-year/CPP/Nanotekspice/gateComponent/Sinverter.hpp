/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** Sinverter
*/

#ifndef SINVERTER_HPP_
#define SINVERTER_HPP_

#include "../AComponent.hpp"

namespace nts {
    class Sinverter : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 14 && pin == 7) {
                    return UNDEFINED;
                }
                if (pin % 2 == 0){
                    size_t pin1 = pin < 7 ? pin - 1 : pin + 1;
                    IComponent *link1 = this->getLink(pin1);
                    if (!link1 || link1->compute(this->getPin(pin1)) == UNDEFINED)
                        return UNDEFINED;
                    if (link1->compute(this->getPin(pin1)) == TRUE)
                        return FALSE;
                    return TRUE;
                } else {
                    if (getLink(pin) != nullptr)
                        return getLink(pin)->compute(this->getPin(pin));
                    return UNDEFINED;
                }
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

#endif /* !SINVERTER_HPP_ */

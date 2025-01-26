/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** InverterComponent
*/

#ifndef INVERTERCOMPONENT_HPP_
#define INVERTERCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class InverterComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 2) {
                    if (!getLink(1) || getLink(1)->compute(this->getPin(1)) == UNDEFINED)
                        return UNDEFINED;
                    if (getLink(1)->compute(this->getPin(1)) == TRUE)
                        return FALSE;
                    return TRUE;
                }
                if (getLink(pin) != nullptr)
                    return getLink(pin)->compute(this->getPin(pin));
                return UNDEFINED;
            }
            int getMaxPin() const override {
                return max_pin;
            }
            void setStatusSpecial(Tristate status) override {};
            std::vector<int> getBannedPin() const override {
                return std::vector<int>{-1};
            }
            Tristate getStatusSpecial() override { return UNDEFINED; };
        protected:
        private:
            int max_pin = 2;
    };
};

#endif /* !INVERTERCOMPONENT_HPP_ */

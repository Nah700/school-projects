/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** OrComponent
*/

#ifndef ORCOMPONENT_HPP_
#define ORCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class OrComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 3) {
                    IComponent *link1 = this->getLink(1);
                    IComponent *link2 = this->getLink(2);

                    if (!link1 || !link2 || (link1->compute(this->getPin(1)) == UNDEFINED && link2->compute(this->getPin(2)) == FALSE)
                    || (link2->compute(this->getPin(2)) == UNDEFINED && link1->compute(this->getPin(1)) == FALSE)
                    || (link1->compute(this->getPin(1)) == UNDEFINED && link2->compute(this->getPin(2)) == UNDEFINED))
                        return UNDEFINED;
                    if (link1->compute(this->getPin(1)) == FALSE && link2->compute(this->getPin(2)) == FALSE)
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
            int max_pin = 3;
    };
};
#endif /* !ORCOMPONENT_HPP_ */

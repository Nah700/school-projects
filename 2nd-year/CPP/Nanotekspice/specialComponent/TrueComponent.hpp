/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** TrueComponent
*/

#ifndef TRUECOMPONENT_HPP_
#define TRUECOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 1)
                    return TRUE;
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
            int max_pin = 1;
    };
};

#endif /* !TRUECOMPONENT_HPP_ */

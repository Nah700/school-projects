/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** FalseComponent
*/

#ifndef FALSECOMPONENT_HPP_
#define FALSECOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class FalseComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 1)
                    return FALSE;
                return UNDEFINED;
            }
            int getMaxPin() const override {
                return max_pin;
            }
            void setStatusSpecial(Tristate status) override {};
            Tristate getStatusSpecial() override { return UNDEFINED; };
            std::vector<int> getBannedPin() const override {
                return std::vector<int>{-1};
            }
        protected:
        private:
            int max_pin = 1;
    };
};
#endif /* !FALSECOMPONENT_HPP_ */

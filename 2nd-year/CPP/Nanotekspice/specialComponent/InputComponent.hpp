/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class InputComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 1 && _status != UNDEFINED)
                    return _status;
                return UNDEFINED;
            }
            void setStatusSpecial(Tristate status) override {
                this->_status = status;
            }
            Tristate getStatusSpecial() override {
                return this->_status;
            }
            int getMaxPin() const override {
                return max_pin;
            }
            std::vector<int> getBannedPin() const override {
                return std::vector<int>{-1};
            }
        protected:
        private:
            Tristate _status = UNDEFINED;
            int max_pin = 1;
    };
};

#endif /* !INPUTCOMPONENT_HPP_ */

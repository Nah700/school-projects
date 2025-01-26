/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** LoggerComponent
*/

#ifndef LOGGERCOMPONENT_HPP_
#define LOGGERCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class LoggerComponent : public AComponent {
        public:
            Tristate compute(std::size_t pin) override {
                if (getLink(pin) != nullptr)
                    return getLink(pin)->compute(this->getPin(pin));
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
            int max_pin = 10;
    };
};

#endif /* !LOGGERCOMPONENT_HPP_ */

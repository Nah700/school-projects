/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** NorComponent
*/

#ifndef NORCOMPONENT_HPP_
#define NORCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class FNorComponent : public AComponent{
        public:
            Tristate compute(std::size_t pin) override {
                if (pin == 14 || pin == 7)
                    return UNDEFINED;
                if (pin == 3 || pin == 4 || pin == 10 || pin == 11) {
                    size_t pin1 = pin == 3 || pin == 10 ? pin - 1 : pin + 1;
                    size_t pin2 = pin == 3 || pin == 10 ? pin - 2 : pin + 2;
                    IComponent *link1 = this->getLink(pin1);
                    IComponent *link2 = this->getLink(pin2);

                    if (pin == 3 && (this->_last_State[3].second == this->getActualTick()))
                        return this->_last_State[3].first;
                    if (pin == 4 && (this->_last_State[4].second == this->getActualTick()))
                        return this->_last_State[4].first;
                    if ((pin == 3 || pin == 4) && !(this->_last_State[4].second == this->getActualTick()))
                        this->_last_State[pin == 3 ? 3 : 4].second = this->getActualTick();

                    if (!link1 || !link2 || (link1->compute(this->getPin(pin1)) == UNDEFINED && link2->compute(this->getPin(pin2)) != TRUE)
                    || (link2->compute(this->getPin(pin2)) == UNDEFINED && link1->compute(this->getPin(pin1)) != TRUE)){
                        if (pin == 3 || pin == 4)
                            this->_last_State[pin == 3 ? 3 : 4].first = UNDEFINED;
                        return UNDEFINED;
                    }
                    if (link1->compute(this->getPin(pin1)) == FALSE && link2->compute(this->getPin(pin2)) == FALSE){
                        if (pin == 3 || pin == 4)
                            this->_last_State[pin == 3 ? 3 : 4].first = TRUE;
                        return TRUE;
                    }
                    if (pin == 3 || pin == 4)
                        this->_last_State[pin == 3 ? 3 : 4].first = FALSE;
                    return FALSE;
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
            std::map<int, std::pair<Tristate, int>> _last_State = {{3, {UNDEFINED, 0}}, {4, {UNDEFINED, 0}}};
    };
};

#endif /* !NORCOMPONENT_HPP_ */

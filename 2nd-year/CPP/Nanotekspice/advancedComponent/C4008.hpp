/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** C4008
*/

#ifndef C4008_HPP_
#define C4008_HPP_

#include <vector>
#include "../AComponent.hpp"

namespace nts
{
    class C4008 : public AComponent {
        public:
            Tristate computeSomme(Tristate a, Tristate b, Tristate c){
                if (a == UNDEFINED || b == UNDEFINED || c == UNDEFINED)
                    return UNDEFINED;
                if ((a == TRUE && b == FALSE && c == FALSE)
                || (a == FALSE && b == TRUE && c == FALSE)
                || (a == FALSE && b == FALSE && c == TRUE)
                || (a == TRUE && b == TRUE && c == TRUE))
                    return TRUE;
                return FALSE;
            }
    
            Tristate computeCarry(Tristate a, Tristate b, Tristate c){
                if (a == UNDEFINED || b == UNDEFINED || c == UNDEFINED)
                    return UNDEFINED;
                if ((a == TRUE && b == TRUE && c == FALSE)
                || (a == TRUE && b == FALSE && c == TRUE)
                || (a == FALSE && b == TRUE && c == TRUE)
                || (a == TRUE && b == TRUE && c == TRUE))
                    return TRUE;
                return FALSE;
            }
    
            Tristate computeEveryCarry(int nb){
                Tristate carry = computeCarry(this->getLink(6)->compute(this->getPin(6)), this->getLink(7)->compute(this->getPin(7)), this->getLink(9)->compute(this->getPin(9)));
                if (nb >= 2)
                    carry = computeCarry(this->getLink(4)->compute(this->getPin(4)), this->getLink(5)->compute(this->getPin(5)), carry);
                if (nb >= 3)
                    carry = computeCarry(this->getLink(2)->compute(this->getPin(2)), this->getLink(3)->compute(this->getPin(3)), carry);
                if (nb >= 4)
                    carry = computeCarry(this->getLink(1)->compute(this->getPin(1)), this->getLink(15)->compute(this->getPin(15)), carry);
                return carry;
            }
    
            Tristate compute(std::size_t pin) override{
                if (pin == 10){
                    return computeSomme(this->getLink(6)->compute(this->getPin(6)), this->getLink(7)->compute(this->getPin(7)), this->getLink(9)->compute(this->getPin(9)));
                }
                if (pin == 11){
                    Tristate carry = this->computeEveryCarry(1);
                    return computeSomme(this->getLink(4)->compute(this->getPin(4)), this->getLink(5)->compute(this->getPin(5)), carry);
                }
                if (pin == 12){
                    Tristate carry = this->computeEveryCarry(2);
                    return computeSomme(this->getLink(2)->compute(this->getPin(2)), this->getLink(3)->compute(this->getPin(3)), carry);
                }
                if (pin == 13){
                    Tristate carry = this->computeEveryCarry(3);
                    return computeSomme(this->getLink(1)->compute(this->getPin(1)), this->getLink(15)->compute(this->getPin(15)), carry);
                }
                if (pin == 14){
                    Tristate carry1 = computeCarry(this->getLink(6)->compute(this->getPin(6)), this->getLink(7)->compute(this->getPin(7)), this->getLink(9)->compute(this->getPin(9)));
                    Tristate carry2 = computeCarry(this->getLink(4)->compute(this->getPin(4)), this->getLink(5)->compute(this->getPin(5)), carry1);
                    Tristate carry3 = computeCarry(this->getLink(2)->compute(this->getPin(2)), this->getLink(3)->compute(this->getPin(3)), carry2);
                    Tristate carry4 = computeCarry(this->getLink(1)->compute(this->getPin(1)), this->getLink(15)->compute(this->getPin(15)), carry3);
                    if (carry1 == UNDEFINED || carry2 == UNDEFINED || carry3 == UNDEFINED || carry4 == UNDEFINED)
                        return UNDEFINED;
                    return carry4;
                }
                return this->getLink(pin)->compute(this->getPin(pin));
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
            int max_pin = 16;
            std::vector<int> _banned_pin = {8, 16};
    };
};

#endif /* !C4008_HPP_ */

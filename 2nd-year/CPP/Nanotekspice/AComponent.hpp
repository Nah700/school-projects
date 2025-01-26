/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"

namespace nts {
        class AComponent : public IComponent{
            public:
                AComponent() = default;
                ~AComponent() = default;
                void setLinkInOther(std::size_t pin, nts::IComponent *other, std::size_t otherPin) override;
                void setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin) override;
                std::map<std::size_t, std::pair<size_t, IComponent *>> getLinks();
                IComponent *getLink(std::size_t pin) override;
                size_t getPin(std::size_t pin) override;
                void simulate(std::size_t tick) override {};
                virtual Tristate compute(std::size_t pin) = 0;
                virtual Tristate getStatusSpecial() = 0;
                virtual void setStatusSpecial(Tristate status) = 0;
                virtual int getMaxPin() const = 0;
                virtual std::vector<int> getBannedPin() const = 0;
                void setActualTick(std::size_t tick) {
                    _actual_tick = tick;
                }
                size_t getActualTick() {
                    return _actual_tick;
                }
            protected:
            private:
                std::map<std::size_t, std::pair<size_t, IComponent *>> _links;   // pair of pin and component
                size_t _actual_tick = 0;
        };
};

std::ostream &operator<<(std ::ostream &s, nts::Tristate v);

#endif /* !ACOMPONENT_HPP_ */

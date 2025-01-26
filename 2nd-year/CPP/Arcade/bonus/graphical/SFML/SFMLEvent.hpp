/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SFMLEvent
*/

#ifndef SFMLEVENT_HPP_
#define SFMLEVENT_HPP_

#include "SFMLModule.hpp"

namespace arcade {
    class SFMLEvent : public IEvent {
        public:
            SFMLEvent() = default;
            ~SFMLEvent() = default;
            std::unique_ptr<IEventInfo> getEvent() override;
            std::unique_ptr<IEventInfo> getChangeEvent() override;
            void pushEvent(const Key &key);
            void pushEvent(const Key &key, std::pair<int, int> mouseCoords);
            void pushChangeEvent(const ChangeKey &key);
            void clearEventQueue();
            void clearChangeEventQueue();
        private:
            std::vector<std::unique_ptr<IEventInfo>> _events;
            std::vector<std::unique_ptr<IEventInfo>> _changeEvents;
    };
};
#endif /* !SFMLEVENT_HPP_ */

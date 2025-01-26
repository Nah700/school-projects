/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** NCURSESEvent
*/

#ifndef NCURSESEVENT_HPP_
#define NCURSESEVENT_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include "../IEvent.hpp"


namespace arcade {
    class NCURSESEvent : public IEvent {
        public:
            NCURSESEvent() = default;
            ~NCURSESEvent() = default;
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

#endif /* !NCURSESEVENT_HPP_ */

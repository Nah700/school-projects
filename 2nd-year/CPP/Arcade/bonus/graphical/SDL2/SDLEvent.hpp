/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SDLEvent
*/

#ifndef SDLEVENT_HPP_
#define SDLEVENT_HPP_

#include <vector>
#include <SDL2/SDL.h>
#include "../IEvent.hpp"

namespace arcade {

    class SDLEvent : public IEvent {
        public:
            SDLEvent() = default;
            ~SDLEvent() = default;
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

#endif /* !SDLEVENT_HPP_ */

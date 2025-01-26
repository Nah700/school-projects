/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SDLEvent
*/

#include "SDLEvent.hpp"

namespace arcade {

    std::unique_ptr<IEventInfo> SDLEvent::getChangeEvent()
    {
        if (this->_changeEvents.empty())
            return std::move(std::make_unique<EventInfo>(ChangeKey::CHANGE_LIST_END));
        std::unique_ptr<IEventInfo> event = std::move(this->_changeEvents[0]);
        this->_changeEvents.erase(this->_changeEvents.begin());
        return event;
    }

    std::unique_ptr<IEventInfo> SDLEvent::getEvent()
    {
        if (this->_events.empty())
            return std::move(std::make_unique<EventInfo>(Key::KEY_LIST_END));
        std::unique_ptr<IEventInfo> event = std::move(this->_events[0]);
        this->_events.erase(this->_events.begin());
        return event;
    }

    void SDLEvent::pushChangeEvent(const ChangeKey &key)
    {
        this->_changeEvents.push_back(std::make_unique<EventInfo>(key));
    }

    void SDLEvent::pushEvent(const Key &key)
    {
        this->_events.push_back(std::make_unique<EventInfo>(key));
    }

    void SDLEvent::pushEvent(const Key &key, std::pair<int, int> mouseCoords)
    {
        this->_changeEvents.push_back(std::make_unique<EventInfo>(key, mouseCoords));
    }

    void SDLEvent::clearEventQueue()
    {
        this->_events.clear();
    }

    void SDLEvent::clearChangeEventQueue()
    {
        this->_changeEvents.clear();
    }
}

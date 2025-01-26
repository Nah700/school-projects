/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
    #define IEVENT_HPP_
    #include <memory>
    #include "Keys.hpp"
    #include "EventInfo.hpp"

namespace arcade
{
    class IEvent {
        public:
            virtual ~IEvent() = default;
            virtual std::unique_ptr<IEventInfo> getEvent() = 0;
            virtual std::unique_ptr<IEventInfo> getChangeEvent() = 0;
            virtual void pushEvent(const Key &key) = 0;
            virtual void pushEvent(const Key &key, std::pair<int, int> mouseCoords) = 0;
            virtual void pushChangeEvent(const ChangeKey &changeKey) = 0;
            virtual void clearEventQueue() = 0;
            virtual void clearChangeEventQueue() = 0;
    };
};
#endif /* !IEVENT_HPP_ */
/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** EventInfo
*/

#ifndef EVENTINFO_HPP_
#define EVENTINFO_HPP_

#include "IEventInfo.hpp"

namespace arcade
{
    class EventInfo : public IEventInfo {
        public:
            EventInfo();
            EventInfo(const Key &key);
            EventInfo(const Key &key, const std::pair<int, int> &mouseCoords);
            EventInfo(const ChangeKey &key);
            ~EventInfo() override = default;
            std::pair<int, int> getMouseCoords() const override;
            Key getKey() const override;
            ChangeKey getChangeKey() const override;
            void setMouseCoords(const std::pair<int, int> &coords) override;
            void setKey(const Key &key) override;
            void setChangeKey(const ChangeKey &key) override;
        private:
            std::pair<int, int> _mouseCoords;
            Key _key;
            ChangeKey _changeKey;
    };
}

#endif /* !EVENTINFO_HPP_ */

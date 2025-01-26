/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IEventInfo
*/

#ifndef IEVENTINFO_HPP_
    #define IEVENTINFO_HPP_
    #include <iostream>
    #include "Keys.hpp"

namespace arcade
{
    class IEventInfo {
        public:
            virtual ~IEventInfo() = default;
            virtual std::pair<int, int> getMouseCoords() const = 0;
            virtual Key getKey() const = 0;
            virtual ChangeKey getChangeKey() const = 0;
            virtual void setMouseCoords(const std::pair<int, int> &coords) = 0;
            virtual void setKey(const Key &key) = 0;
            virtual void setChangeKey(const ChangeKey &key) = 0;
    };
};

#endif /* !IEVENTINFO_HPP_ */
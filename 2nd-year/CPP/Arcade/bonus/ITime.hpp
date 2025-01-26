/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** ITime
*/

#ifndef ITIME_HPP_
#define ITIME_HPP_

#include <chrono>

class ITime {
    public:
        virtual ~ITime() = default;
        virtual void update() = 0;
        virtual float getTime() const = 0;
        virtual float getDeltaTime() const = 0;
};

#endif /* !ITIME_HPP_ */

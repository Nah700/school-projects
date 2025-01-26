/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** Time
*/

#include "Time.hpp"

Time::Time() : startTime(std::chrono::steady_clock::now()), previousTime(startTime)
{
    update();
}

void Time::update()
{
    currentTime = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - previousTime).count();
    previousTime = currentTime;
}

float Time::getTime() const
{
    return std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - startTime).count();
}

float Time::getDeltaTime() const
{
    return deltaTime;
}

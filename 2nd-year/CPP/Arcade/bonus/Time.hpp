/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** Time
*/

#ifndef TIME_HPP_
#define TIME_HPP_

#include "./ITime.hpp"

class Time : public ITime {
    public:
        Time();
        void update() override;
        float getTime() const override;
        float getDeltaTime() const override;
    private:
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point previousTime;
        std::chrono::steady_clock::time_point currentTime;
        float deltaTime;
};

#endif /* !TIME_HPP_ */

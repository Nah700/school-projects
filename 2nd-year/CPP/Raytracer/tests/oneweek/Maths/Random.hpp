/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>

namespace Math {
    class Random {
        public:
            static double random_double() {
                return _distribution(_generator);
            }

            static double random_double(double min, double max) {
                return min + random_double() * (max - min);
            }
        private:
            inline static std::uniform_real_distribution<double> _distribution{0.0, 1.0};
            inline static std::mt19937 _generator;
    };
};

#endif /* !RANDOM_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** Pair
*/

#ifndef PAIR_HPP_
#define PAIR_HPP_

#include <iostream>

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
}

#endif /* !PAIR_HPP_ */

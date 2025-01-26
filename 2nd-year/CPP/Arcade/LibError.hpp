/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** LibError
*/

#ifndef LIBERROR_HPP_
#define LIBERROR_HPP_

#include <iostream>
#include <exception>

class LibError : public std::exception{
    public:
        LibError(const std::string &message) : _message(message) {};
        const char *what() const noexcept override {
            return _message.c_str();
        };
    private:
        std::string _message;
};

#endif /* !LIBERROR_HPP_ */

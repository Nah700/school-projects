/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>
#include <exception>

class Error : public std::exception{
    public:
        Error(const std::string &message) : _message(message) {};

        const char *what() const noexcept override {
            return _message.c_str();
        };

    private:
        std::string _message;
};

#endif /* !ERROR_HPP_ */

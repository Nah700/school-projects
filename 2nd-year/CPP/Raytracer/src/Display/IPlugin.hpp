/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** IPlugin
*/

#ifndef IPLUGIN_HPP_
#define IPLUGIN_HPP_

#include <iostream>

class IPlugin {
    public:
        virtual ~IPlugin() = default;
        virtual void init(std::string &colors) = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual bool isWindowOpen() = 0;
};

#endif /* !IPLUGIN_HPP_ */

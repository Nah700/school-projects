/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** DisplayPlugin
*/

#ifndef DISPLAYPLUGIN_HPP_
#define DISPLAYPLUGIN_HPP_

#include "IPlugin.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>

class DisplayPlugin : public IPlugin {
    public:
        DisplayPlugin() = default;
        ~DisplayPlugin() = default;
        void init(std::string &colors) override;
        void update() override;
        void render() override;
        bool isWindowOpen() override;
    protected:
    private:
        int _width;
        int _height;
        std::vector<sf::Color> _colors;
        sf::RenderWindow _window;
};

#endif /* !DISPLAYPLUGIN_HPP_ */

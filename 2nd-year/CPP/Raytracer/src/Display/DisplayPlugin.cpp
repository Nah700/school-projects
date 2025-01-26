/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** DisplayPlugin
*/

#include "DisplayPlugin.hpp"

void DisplayPlugin::init(std::string &colors) {
    std::istringstream stream(colors);
    std::string line;
    int width, height, maxval;

    std::getline(stream, line);
    stream >> width >> height >> maxval;
    std::cout << "Width: " << width << ", Height: " << height << ", MaxVal: " << maxval << std::endl;
    this->_width = width;
    this->_height = height;
    _colors.clear();
    int r, g, b;
    while (stream >> r >> g >> b)
        _colors.push_back(sf::Color(r, g, b));
    _window.create(sf::VideoMode(width, height), "Raytracer Display");
    _window.clear(sf::Color::Black);
    _window.display();
}

void DisplayPlugin::update() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void DisplayPlugin::render() {
    _window.clear();
    float tileWidth = static_cast<float>(_window.getSize().x) / _width;
    float tileHeight = static_cast<float>(_window.getSize().y) / _height;

    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
            long unsigned int index = row * _width + col;
            if (index < _colors.size()) {
                sf::RectangleShape rectangle(sf::Vector2f(tileWidth, tileHeight));
                rectangle.setPosition(col * tileWidth, row * tileHeight);
                rectangle.setFillColor(_colors[index]);
                _window.draw(rectangle);
            }
        }
    }
    _window.display();
}

bool DisplayPlugin::isWindowOpen() {
    return _window.isOpen();
}

extern "C" {
    std::unique_ptr<IPlugin> entryPoint() {
        return std::make_unique<DisplayPlugin>();
    }
}

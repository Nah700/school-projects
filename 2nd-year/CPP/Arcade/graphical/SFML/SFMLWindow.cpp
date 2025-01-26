/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SFMLWindow
*/

#include "SFMLWindow.hpp"

namespace arcade {
    void SFMLWindow::openWindow(int width, int height) {
        this->_window = new sf::RenderWindow(sf::VideoMode(width, height), "Arcade");
    }

    void SFMLWindow::resizeWindow(int width, int height) {
        this->_window->setSize(sf::Vector2u(width, height));
    }

    bool SFMLWindow::isOpen() const {
        return this->_window->isOpen();
    }

    void SFMLWindow::clearScreen() {
        if (this->_window->isOpen())
            this->_window->clear();
    }

    void SFMLWindow::closeWindow() {
        this->_window->close();
    }
    void SFMLWindow::display() {
        this->_window->display();
    }

    void SFMLWindow::displayPixels(IPixels *pixels) {
        double maxX = 0;
        double maxY = 0;
        auto &pixelMap = pixels->getPixelMap();
        for (auto &pixel : pixelMap) {
            if (pixel.first.first > maxX)
                maxX = pixel.first.first;
            if (pixel.first.second > maxY)
                maxY = pixel.first.second;
        }
        double ratioX = _window->getSize().x / (maxX + 1);
        double ratioY = _window->getSize().y / (maxY + 1);
        this->_pixel_size = std::min(ratioX, ratioY);

        sf::VertexArray vertices(sf::Quads, 4);
        for (auto &pixel : pixelMap) {
            double x = pixel.first.first * this->_pixel_size;
            double y = pixel.first.second * this->_pixel_size;
            if (pixel.second.getType() == IPixel::PixelType::TEXTURED) {
                std::string texturePath = pixel.second.getTexturePath();
                if (this->_textures.find(texturePath) == this->_textures.end()) {
                    sf::Texture texture;
                    if (!texture.loadFromFile(texturePath)) {
                        std::cerr << "Failed to load texture from " << texturePath << std::endl;
                        continue;
                    }
                    this->_textures[texturePath] = texture;
                }

                sf::Sprite sprite(this->_textures[texturePath]);
                std::pair<int, int> rectSize = pixel.second.getRectSize();
                std::pair<int, int> rectPosition = pixel.second.getRectPosition();
                if (rectSize.first != 0 && rectSize.second != 0) {
                    sprite.setTextureRect(sf::IntRect(rectPosition.first, rectPosition.second, rectSize.first, rectSize.second));
                }
                sprite.setPosition(x, y);
                sprite.setScale(this->_pixel_size / (float)rectSize.first, this->_pixel_size / (float)rectSize.second);
                this->_window->draw(sprite);
            } else {
                sf::Color color = sf::Color(pixel.second.getRed(), pixel.second.getGreen(), pixel.second.getBlue(), pixel.second.getAlpha());
                vertices.append(sf::Vertex(sf::Vector2f(x, y), color));
                vertices.append(sf::Vertex(sf::Vector2f(x + this->_pixel_size, y), color));
                vertices.append(sf::Vertex(sf::Vector2f(x + this->_pixel_size, y + this->_pixel_size), color));
                vertices.append(sf::Vertex(sf::Vector2f(x, y + this->_pixel_size), color));
            }
        }
        this->_window->draw(vertices);
    }

    void SFMLWindow::displayTexts(ITexts *texts) {
        auto &textsMap = texts->getTextMap();
        sf::Text sfText;
        sf::Font font;
        font.loadFromFile("Fonts/arial.ttf");
        for (auto &text : textsMap) {
            sfText.setString(text.second.getStr());
            sfText.setFillColor(sf::Color(text.second.getRed(), text.second.getGreen(), text.second.getBlue(), text.second.getAlpha()));
            sfText.setPosition(text.first.first * this->_pixel_size, text.first.second * this->_pixel_size);
            sfText.setCharacterSize(this->_pixel_size);
            sfText.setFont(font);
            this->_window->draw(sfText);
        }
    }

    sf::RenderWindow *SFMLWindow::getWindow() const {
        return this->_window;
    }
};

extern "C" {
    std::string getType() {
        return "graphical";
    }
    std::unique_ptr<arcade::IGraphicalModule> entryPoint() {
        return std::make_unique<arcade::SFMLModule>();
    }
}

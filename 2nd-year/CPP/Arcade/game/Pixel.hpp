/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include "./IPixel.hpp"

class Pixel : public IPixel {
    public:
        Pixel();
        Pixel(
            Color red,
            Color green,
            Color blue,
            Color alpha = 255,
            PixelType pixelType = PixelType::DEFAULT,
            char charValue = ' ',
            const std::string &texturePath = "",
            Rotation rotation = Rotation::R0,
            std::pair<int, int> rectSize = std::make_pair(0, 0),
            std::pair<int, int> rectPosition = std::make_pair(0, 0)
        );

        Color getRed() const override;
        Color getGreen() const override;
        Color getBlue() const override;
        Color getAlpha() const override;
        char getChar() const override;
        std::string getTexturePath() const override;
        Rotation getRotation() const override;
        PixelType getType() const override;
        std::pair<int, int> getRectSize() const override;
        std::pair<int, int> getRectPosition() const override;

        void setRed(Color red) override;
        void setGreen(Color green) override;
        void setBlue(Color blue) override;
        void setAlpha(Color alpha) override;
        void setChar(char charValue) override;
        void setTexturePath(const std::string &path) override;
        void setRotation(Rotation rotation) override;
        void setType(PixelType type) override;
        void setRectSize(std::pair<int, int> rectSize) override;
        void setRectPosition(std::pair<int, int> rectPosition) override;

    private:
        Color _red;
        Color _green;
        Color _blue;
        Color _alpha;
        PixelType _type;
        char _char;
        std::string _texturePath;
        Rotation _rotation;
        std::pair<int, int> _rectSize;
        std::pair<int, int> _rectPosition;
};

#endif /* !PIXEL_HPP_ */

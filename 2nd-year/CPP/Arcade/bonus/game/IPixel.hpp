/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IPixel
*/

#ifndef IPIXEL_HPP_
#define IPIXEL_HPP_

#include <string>

class IPixel {
    public:
        using Color = unsigned int;

        enum class PixelType {
            DEFAULT,
            TEXTURED,
            // ...
            NONE,
        };

        enum class Rotation {
            R0,
            R90,
            R180,
            R270
        };
        virtual ~IPixel() = default;
        virtual Color getRed() const = 0;
        virtual Color getGreen() const = 0;
        virtual Color getBlue() const = 0;
        virtual Color getAlpha() const = 0;
        virtual char getChar() const = 0;
        virtual std::string getTexturePath() const = 0;
        virtual Rotation getRotation() const = 0;
        virtual PixelType getType() const = 0;
        virtual std::pair<int, int> getRectSize() const = 0;
        virtual std::pair<int, int> getRectPosition() const = 0;

        virtual void setRed(Color red) = 0;
        virtual void setGreen(Color green) = 0;
        virtual void setBlue(Color blue) = 0;
        virtual void setAlpha(Color alpha) = 0;
        virtual void setChar(char charValue) = 0;
        virtual void setTexturePath(const std::string &path) = 0;
        virtual void setRotation(Rotation rotation) = 0;
        virtual void setType(PixelType type) = 0;
        virtual void setRectSize(std::pair<int, int> rectSize) = 0;
        virtual void setRectPosition(std::pair<int, int> rectPosition) = 0;
};

#endif /* !IPIXEL_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** IText
*/

#ifndef ITEXT_HPP_
#define ITEXT_HPP_

#include <string>

class IText {
    public:
        using Color = unsigned int;

        virtual ~IText() = default;
        virtual Color getRed() const = 0;
        virtual Color getGreen() const = 0;
        virtual Color getBlue() const = 0;
        virtual Color getAlpha() const = 0;
        virtual std::string getStr() const = 0;

        virtual void setRed(Color red) = 0;
        virtual void setGreen(Color green) = 0;
        virtual void setBlue(Color blue) = 0;
        virtual void setAlpha(Color alpha) = 0;
        virtual void setStr(const std::string &str) = 0;
};

#endif /* !ITEXT_HPP_ */

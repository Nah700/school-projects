/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "./IText.hpp"

class Text : public IText {
    public:
        Text();
        Text(const std::string &str);
        Text(
            const std::string &str,
            Color red,
            Color green,
            Color blue,
            Color alpha = 255
        );

        Color getRed() const override;
        Color getGreen() const override;
        Color getBlue() const override;
        Color getAlpha() const override;
        std::string getStr() const override;

        void setRed(Color red) override;
        void setGreen(Color green) override;
        void setBlue(Color blue) override;
        void setAlpha(Color alpha) override;
        void setStr(const std::string &str) override;

    private:
        std::string _str;
        Color _red;
        Color _green;
        Color _blue;
        Color _alpha;
};

#endif /* !TEXT_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SFMLModule
*/

#ifndef SFMLMODULE_HPP_
#define SFMLMODULE_HPP_

#include <SFML/Graphics.hpp>
#include "../IGraphicalModule.hpp"
#include <map>

namespace arcade {
    class SFMLModule  : public IGraphicalModule {
        public:
            SFMLModule() = default;
            ~SFMLModule() = default;

            void init();
            void stop();
            IEvent *getEventWrapper() const override;
            IWindow *getWindowWrapper() const override;
            IPixels *getPixelsWrapper() const;
            ITexts *getTextsWrapper() const;
            void updatePixelsWrapper(IPixels *pixels) override;
            void updateTextsWrapper(ITexts *texts) override;
            std::string getName() const override;
            void pollEvents() override;
            void display() const override;
        protected:
            IEvent *createEventObject();
            IWindow *createWindowObject();
        private:
            std::string _name = "SFML";
            std::unique_ptr<IEvent> _event;
            std::unique_ptr<IWindow> _window;
            IPixels *_pixels;
            ITexts *_texts;
            std::unordered_map<sf::Keyboard::Key, Key> _keyMap {
                {sf::Keyboard::A, Key::A_KEY},
                {sf::Keyboard::B, Key::B_KEY},
                {sf::Keyboard::C, Key::C_KEY},
                {sf::Keyboard::D, Key::D_KEY},
                {sf::Keyboard::E, Key::E_KEY},
                {sf::Keyboard::F, Key::F_KEY},
                {sf::Keyboard::G, Key::G_KEY},
                {sf::Keyboard::H, Key::H_KEY},
                {sf::Keyboard::I, Key::I_KEY},
                {sf::Keyboard::J, Key::J_KEY},
                {sf::Keyboard::K, Key::K_KEY},
                {sf::Keyboard::L, Key::L_KEY},
                {sf::Keyboard::M, Key::M_KEY},
                {sf::Keyboard::N, Key::N_KEY},
                {sf::Keyboard::O, Key::O_KEY},
                {sf::Keyboard::P, Key::P_KEY},
                {sf::Keyboard::Q, Key::Q_KEY},
                {sf::Keyboard::R, Key::R_KEY},
                {sf::Keyboard::S, Key::S_KEY},
                {sf::Keyboard::T, Key::T_KEY},
                {sf::Keyboard::U, Key::U_KEY},
                {sf::Keyboard::V, Key::V_KEY},
                {sf::Keyboard::W, Key::W_KEY},
                {sf::Keyboard::X, Key::X_KEY},
                {sf::Keyboard::Y, Key::Y_KEY},
                {sf::Keyboard::Z, Key::Z_KEY},
                {sf::Keyboard::Up, Key::UP_ARROW},
                {sf::Keyboard::Left, Key::LEFT_ARROW},
                {sf::Keyboard::Down, Key::DOWN_ARROW},
                {sf::Keyboard::Right, Key::RIGHT_ARROW},
                {sf::Keyboard::Space, Key::SPACE},
                {sf::Keyboard::Enter, Key::ENTER},
                {sf::Keyboard::Backspace, Key::DELETE},
            };
            std::unordered_map<sf::Keyboard::Key, ChangeKey> _changeKeyMap {
                {sf::Keyboard::F1, ChangeKey::MAIN_MENU},
                {sf::Keyboard::F2, ChangeKey::PREV_GAME_LIB},
                {sf::Keyboard::F3, ChangeKey::NEXT_GAME_LIB},
                {sf::Keyboard::F4, ChangeKey::PREV_GRAPHICAL_LIB},
                {sf::Keyboard::F5, ChangeKey::NEXT_GRAPHICAL_LIB},
                {sf::Keyboard::Escape, ChangeKey::ESCAPE},
            };
    };
};
#endif /* !SFMLMODULE_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** NCURSESModule
*/

#ifndef NCURSESMODULE_HPP_
#define NCURSESMODULE_HPP_

#include "../IGraphicalModule.hpp"
#include <ncurses.h>
#include <unordered_map>

namespace arcade {
    class NCURSESModule : public IGraphicalModule {
        public:
            NCURSESModule() = default;
            ~NCURSESModule() = default;

            void init() override;
            void stop() override;
            void display() const override;
            void pollEvents() override;
            IEvent *getEventWrapper() const override;
            IWindow *getWindowWrapper() const override;
            IPixels *getPixelsWrapper() const;
            ITexts *getTextsWrapper() const;
            void updatePixelsWrapper(IPixels *pixels) override;
            void updateTextsWrapper(ITexts *texts) override;
            std::string getName() const override;
        protected:
            IEvent *createEventObject();
            IWindow *createWindowObject();
        private:
            std::string _name = "NCURSES";
            std::unique_ptr<IEvent> _event;
            std::unique_ptr<IWindow> _window;
            IPixels *_pixels;
            ITexts *_texts;
            std::unordered_map<int, Key> _keymap = {
                {'a', Key::A_KEY},
                {'b', Key::B_KEY},
                {'c', Key::C_KEY},
                {'d', Key::D_KEY},
                {'e', Key::E_KEY},
                {'f', Key::F_KEY},
                {'g', Key::G_KEY},
                {'h', Key::H_KEY},
                {'i', Key::I_KEY},
                {'j', Key::J_KEY},
                {'k', Key::K_KEY},
                {'l', Key::L_KEY},
                {'m', Key::M_KEY},
                {'n', Key::N_KEY},
                {'o', Key::O_KEY},
                {'p', Key::P_KEY},
                {'q', Key::Q_KEY},
                {'r', Key::R_KEY},
                {'s', Key::S_KEY},
                {'t', Key::T_KEY},
                {'u', Key::U_KEY},
                {'v', Key::V_KEY},
                {'w', Key::W_KEY},
                {'x', Key::X_KEY},
                {'y', Key::Y_KEY},
                {'z', Key::Z_KEY},
                {KEY_UP, Key::UP_ARROW},
                {KEY_DOWN, Key::DOWN_ARROW},
                {KEY_LEFT, Key::LEFT_ARROW},
                {KEY_RIGHT, Key::RIGHT_ARROW},
                {32, Key::SPACE},
                {'\n', Key::ENTER},
                {KEY_BACKSPACE, Key::DELETE},
                // {KEY_END, Key::KEY_LIST_END},
            };
            std::unordered_map<int, ChangeKey> _changeKeyMap {
                {KEY_F(1), ChangeKey::MAIN_MENU},
                {KEY_F(2), ChangeKey::PREV_GAME_LIB},
                {KEY_F(3), ChangeKey::NEXT_GAME_LIB},
                {KEY_F(4), ChangeKey::PREV_GRAPHICAL_LIB},
                {KEY_F(5), ChangeKey::NEXT_GRAPHICAL_LIB},
                {27, ChangeKey::ESCAPE},
            };
    };
}

#endif /* !NCURSESMODULE_HPP_ */

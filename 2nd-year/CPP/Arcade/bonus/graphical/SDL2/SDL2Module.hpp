/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SDL2Module
*/

#ifndef SDL2MODULE_HPP_
#define SDL2MODULE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include "../IGraphicalModule.hpp"

namespace arcade {
    class SDLModule  : public IGraphicalModule {
        public:
            SDLModule() = default;
            ~SDLModule() = default;
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
            std::string _name = "SDL2";
            std::unique_ptr<IEvent> _event;
            std::unique_ptr<IWindow> _window;
            SDL_Event _sdlEvent;
            IPixels *_pixels;
            ITexts *_texts;
            std::unordered_map<SDL_KeyCode, Key> _keyMap {
                {SDLK_a, Key::A_KEY},
                {SDLK_b, Key::B_KEY},
                {SDLK_c, Key::C_KEY},
                {SDLK_d, Key::D_KEY},
                {SDLK_e, Key::E_KEY},
                {SDLK_f, Key::F_KEY},
                {SDLK_g, Key::G_KEY},
                {SDLK_h, Key::H_KEY},
                {SDLK_i, Key::I_KEY},
                {SDLK_j, Key::J_KEY},
                {SDLK_k, Key::K_KEY},
                {SDLK_l, Key::L_KEY},
                {SDLK_m, Key::M_KEY},
                {SDLK_n, Key::N_KEY},
                {SDLK_o, Key::O_KEY},
                {SDLK_p, Key::P_KEY},
                {SDLK_q, Key::Q_KEY},
                {SDLK_r, Key::R_KEY},
                {SDLK_s, Key::S_KEY},
                {SDLK_t, Key::T_KEY},
                {SDLK_u, Key::U_KEY},
                {SDLK_v, Key::V_KEY},
                {SDLK_w, Key::W_KEY},
                {SDLK_x, Key::X_KEY},
                {SDLK_y, Key::Y_KEY},
                {SDLK_z, Key::Z_KEY},
                {SDLK_UP, Key::UP_ARROW},
                {SDLK_LEFT, Key::LEFT_ARROW},
                {SDLK_DOWN, Key::DOWN_ARROW},
                {SDLK_RIGHT, Key::RIGHT_ARROW},
                {SDLK_SPACE, Key::SPACE},
                {SDLK_RETURN, Key::ENTER},
                {SDLK_BACKSPACE, Key::DELETE},
            };
            std::unordered_map<SDL_KeyCode, ChangeKey> _changeKeyMap {
                {SDLK_F1, ChangeKey::MAIN_MENU},
                {SDLK_F2, ChangeKey::PREV_GAME_LIB},
                {SDLK_F3, ChangeKey::NEXT_GAME_LIB},
                {SDLK_F4, ChangeKey::PREV_GRAPHICAL_LIB},
                {SDLK_F5, ChangeKey::NEXT_GRAPHICAL_LIB},
                {SDLK_ESCAPE, ChangeKey::ESCAPE},
            };
    };
};
#endif /* !SDL2MODULE_HPP_ */

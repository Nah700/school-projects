/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** SDLWindow
*/

#include "SDLWindow.hpp"
#include <SDL2/SDL_image.h>

namespace arcade {
    void SDLWindow::openWindow(int width, int height)
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        TTF_Init();
        this->_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    }

    void SDLWindow::resizeWindow(int width, int height)
    {
        SDL_SetWindowSize(this->_window, width, height);
    }

    bool SDLWindow::isOpen() const
    {
        return SDL_GetWindowFlags(this->_window) & SDL_WINDOW_SHOWN;
    }

    void SDLWindow::clearScreen()
    {
        if (this->isOpen()) {
            SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
            SDL_RenderClear(this->_renderer);
        }
    }

    void SDLWindow::display()
    {
        SDL_RenderPresent(this->_renderer);
    }

    void SDLWindow::displayPixels(IPixels *pixels) {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(_window, &windowWidth, &windowHeight);

        double maxX = 0;
        double maxY = 0;
        auto &pixelMap = pixels->getPixelMap();
        for (auto &pixel : pixelMap) {
            if (pixel.first.first > maxX)
                maxX = pixel.first.first;
            if (pixel.first.second > maxY)
                maxY = pixel.first.second;
        }
        double ratioX = windowWidth / (maxX + 1);
        double ratioY = windowHeight / (maxY + 1);
        this->_pixel_size = std::min(ratioX, ratioY);

        SDL_Rect rect;
        for (auto &pixel : pixelMap) {
            double x = pixel.first.first * this->_pixel_size;
            double y = pixel.first.second * this->_pixel_size;
            rect.x = x;
            rect.y = y;
            rect.w = this->_pixel_size;
            rect.h = this->_pixel_size;

            if (pixel.second.getType() == IPixel::PixelType::TEXTURED) {
                std::string texturePath = pixel.second.getTexturePath();
                if (this->_textures.find(texturePath) == this->_textures.end()) {
                    SDL_Texture* texture = IMG_LoadTexture(_renderer, texturePath.c_str());
                    if (!texture) {
                        std::cerr << "Failed to load texture from " << texturePath << std::endl;
                        continue;
                    }
                    this->_textures[texturePath] = texture;
                }

                SDL_Texture* texture = this->_textures[texturePath];
                std::pair<int, int> rectSize = pixel.second.getRectSize();
                std::pair<int, int> rectPosition = pixel.second.getRectPosition();
                if (rectSize.first != 0 && rectSize.second != 0) {
                    rect.w = this->_pixel_size;
                    rect.h = this->_pixel_size;
                    SDL_Rect srcRect = {rectPosition.first, rectPosition.second, rectSize.first, rectSize.second};
                    SDL_RenderCopy(_renderer, texture, &srcRect, &rect);
                }
            } else {
                SDL_SetRenderDrawColor(_renderer, pixel.second.getRed(), pixel.second.getGreen(), pixel.second.getBlue(), pixel.second.getAlpha());
                SDL_RenderFillRect(_renderer, &rect);
            }
        }
    }

    void SDLWindow::displayTexts(ITexts *texts) {
        auto &textsMap = texts->getTextMap();
        SDL_Surface* surfaceMessage;
        SDL_Texture* Message;
        SDL_Rect Message_rect;
        SDL_Color color;
        TTF_Font* font = TTF_OpenFont("Fonts/arial.ttf", this->_pixel_size);

        for (auto &text : textsMap) {
            color.r = text.second.getRed();
            color.g = text.second.getGreen();
            color.b = text.second.getBlue();
            color.a = text.second.getAlpha();
            surfaceMessage = TTF_RenderText_Solid(font, text.second.getStr().c_str(), color);
            Message = SDL_CreateTextureFromSurface(this->_renderer, surfaceMessage);
        
            Message_rect.x = text.first.first * this->_pixel_size;  
            Message_rect.y = text.first.second * this->_pixel_size;
            Message_rect.w = surfaceMessage->w; 
            Message_rect.h = surfaceMessage->h; 

            SDL_RenderCopy(this->_renderer, Message, NULL, &Message_rect);

            SDL_FreeSurface(surfaceMessage);
            SDL_DestroyTexture(Message);
        }

        TTF_CloseFont(font);
    }

    void SDLWindow::closeWindow()
    {
        // if (this->_window != NULL)
        //     SDL_DestroyWindow(this->_window);
        // if (this->_renderer != NULL)
        //     SDL_DestroyRenderer(this->_renderer);
        SDL_Quit();
        TTF_Quit();
    }

    SDL_Window *SDLWindow::getWindow() const
    {
        return this->_window;
    }
};

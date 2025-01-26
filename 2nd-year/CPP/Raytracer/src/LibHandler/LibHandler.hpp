/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** LibHandler
*/

#ifndef LIBHANDLER_HPP_
    #define LIBHANDLER_HPP_

    #include <iostream>
    #include "ILibHandler.hpp"

class LibHandler : public ILibHandler{
    public:
        LibHandler() = default;
        void ArcadeDlopen(const char *lib) override;
        void *ArcadeDlsym(const char *name) override;
        void ArcadeDlclose() override;
        void ArcadeDlerror() override;
        void **getHandler() override;

        template<typename T>
        T loadInstance()
        {
            void *symbol = this->ArcadeDlsym("entryPoint");
            using type = T (*)();
            return reinterpret_cast<type>(symbol)();
        };
    private:
        void *_handler;
};

#endif /* !LIBHANDLER_HPP_ */

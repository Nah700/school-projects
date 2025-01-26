/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** ILibHandler
*/

#ifndef ILIBHANDLER_HPP_
    #define ILIBHANDLER_HPP_

    #include <dlfcn.h>

class ILibHandler {
    public:
        virtual ~ILibHandler() = default;
        virtual void ArcadeDlopen(const char *lib) = 0;
        virtual void *ArcadeDlsym(const char *name) = 0;
        virtual void ArcadeDlclose() = 0;
        virtual void ArcadeDlerror() = 0;
        virtual void **getHandler() = 0;
    protected:
    private:
};
#endif /* !ILIBHANDLER_HPP_ */

/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** LibHandler
*/

#include "LibHandler.hpp"
#include "../Utils/Error.hpp"

void LibHandler::ArcadeDlclose()
{
    int check = dlclose(this->_handler);
    if (check != 0)
        throw Error(dlerror());
}

void LibHandler::ArcadeDlopen(const char *lib)
{
    this->_handler = dlopen(lib, RTLD_LAZY);
    if (this->_handler == NULL)
        throw Error(dlerror());
}

void *LibHandler::ArcadeDlsym(const char *name)
{
    void *symbol = dlsym(this->_handler, name);
    if (symbol == NULL)
        throw Error(dlerror());
    return symbol;
}

void LibHandler::ArcadeDlerror()
{
    std::cerr << dlerror() << std::endl;
}

void **LibHandler::getHandler()
{
    return &this->_handler;
}

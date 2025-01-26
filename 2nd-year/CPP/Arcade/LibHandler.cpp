/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** LibHandler
*/

#include "LibHandler.hpp"
#include "LibError.hpp"

namespace arcade {
    void LibHandler::ArcadeDlclose()
    {
        int check = dlclose(this->_handler);
        if (check != 0)
            throw LibError(dlerror());
    }

    void LibHandler::ArcadeDlopen(const char *lib)
    {
        this->_handler = dlopen(lib, RTLD_LAZY);
        if (this->_handler == NULL)
            throw LibError(dlerror());
    }

    void *LibHandler::ArcadeDlsym(const char *name)
    {
        void *symbol = dlsym(this->_handler, name);
        if (symbol == NULL)
            throw LibError(dlerror());
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
};
/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** Nanotekspice
*/

#include "Nanotekspice.hpp"

void destroy_components(std::map<std::string, nts::IComponent *> circuit)
{
    for (auto &it : circuit) {
        delete it.second;
    }
}

void Nanotekspice::run()
{
    while (1)
    {
        std::string input;
        std::cout << "> ";
        if (!std::getline(std::cin, input)) {
            destroy_components(this->getCircuit()->getCircuit());
            delete this->getCircuit();
            std::exit(0);
        }
        input = check_space(input);
        if (input == "exit")
            break;
        else if (input == "display")
            this->getCircuit()->display();
        else if (input == "simulate")
            this->getCircuit()->simulate();
        else if (input == "loop")
            this->getCircuit()->loop();
        else {
            if (!this->getCircuit()->equal_func(input))
                std::cout << "Invalid command" << std::endl;
        }
    }
}
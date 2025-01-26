/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "IComponent.hpp"
#include <regex>

class Circuit {
    public:
        Circuit() = default;
        ~Circuit() = default;
        void addComponent(std::string name, nts::IComponent *component);
        void addComponent_disp(std::string name, std::string comp_name);
        nts::IComponent *getComponent(std::string name);
        std::map<std::string, nts::IComponent *> getCircuit();
        std::map<std::string, std::string> getCircuit_disp();
        std::map<std::string, int> getCircuit_input();
        std::size_t getTick();
        void write_in_file(std::string file_name, std::string name);
        void simulate();
        void display();
        bool equal_func(std::string input);
        void loop();
        int check_4k_comp(std::smatch match);
    protected:
    private:
        std::map<std::string, nts::IComponent *> _circuit;
        std::map<std::string, std::string> _circuit_display;
        std::map<std::string, int> _circuit_input;
        std::size_t _tick = 0;
};

#endif /* !CIRCUIT_HPP_ */

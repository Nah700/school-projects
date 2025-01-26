/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <csignal>

int flag = 0;

std::map<std::string, nts::IComponent *> Circuit::getCircuit()
{
    return this->_circuit;
}

std::map<std::string, std::string> Circuit::getCircuit_disp()
{
    return this->_circuit_display;
}

std::map<std::string, int> Circuit::getCircuit_input()
{
    return this->_circuit_input;
}

std::size_t Circuit::getTick()
{
    return this->_tick;
}

nts::IComponent *Circuit::getComponent(std::string name)
{
    if (this->_circuit.find(name) == this->_circuit.end())
        return nullptr;
    return this->_circuit[name];
}

void Circuit::addComponent(std::string name, nts::IComponent *component)
{
    this->_circuit[name] = component;
}

void Circuit::addComponent_disp(std::string name, std::string comp_name)
{
    this->_circuit_display[name] = comp_name;
}

void Circuit::write_in_file(std::string file_name, std::string name)
{
    char number;

    if (this->_circuit[name]->compute(10) != nts::FALSE || this->_circuit[name]->compute(9) != nts::TRUE)
        return;
    for (int i = 8; i >= 1; i--) {
        if (this->_circuit[name]->compute(i) == nts::UNDEFINED) {
            number = 'U';
            break;
        }
        number = (number << 1) | (this->_circuit[name]->compute(i) == nts::TRUE ? 1 : 0);
    }
    std::ofstream file(file_name, std::ios::app);
    file << number;
}

void Circuit::simulate()
{
    this->_tick++;
    auto circuits = this->getCircuit_input();
    auto circuits_disp = this->getCircuit_disp();
    auto components = this->getCircuit();

    if (!components.empty()) {
        for (const auto &component : components) {
            component.second->setActualTick(this->_tick);
        }
    }
    if (!circuits_disp.empty()) {
        for (const auto &circuit_d : circuits_disp) {
            if (circuit_d.second == "clock" && this->getCircuit()[circuit_d.first]->getStatusSpecial() != nts::UNDEFINED) {
                this->getCircuit()[circuit_d.first]->setStatusSpecial(this->getCircuit()[circuit_d.first]->getStatusSpecial() == nts::TRUE ? nts::FALSE : nts::TRUE);
            }
        }
    }
    if (!circuits.empty()) {
        for (const auto &circuit : circuits) {
            this->getCircuit()[circuit.first]->setStatusSpecial((nts::Tristate)circuit.second);
        }
    }
    if (!circuits_disp.empty()) {
        for (const auto &circuit_d : circuits_disp) {
            if (circuit_d.second == "logger") {
                write_in_file("log.bin", circuit_d.first);
            }
        }
    }
    this->_circuit_input.clear();
}

void Circuit::display()
{
    auto circuits = this->getCircuit();
    auto circuits_disp = this->getCircuit_disp();
    std::cout << "tick: " << this->getTick() << std::endl;
    std::cout << "input(s):" << std::endl;
    for (const auto &circuit : circuits) {
        if (circuits_disp[circuit.first] == "input" || circuits_disp[circuit.first] == "clock") {
            std::cout << "  " << circuit.first << ": " << circuit.second->compute(1) << std::endl;
        }
    }
    std::cout << "output(s):" << std::endl;
    for (const auto &circuit : circuits) {
        if (circuits_disp[circuit.first] == "output")
            std::cout << "  " << circuit.first << ": " << circuit.second->compute(1) << std::endl;
    }
}

std::string rm_space(const std::string &str) {
    std::string s = str;
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char ch) {
        return std::isspace(ch);
    }), s.end());
    return s;
}

bool Circuit::equal_func(std::string input)
{
    std::string tmp = "";
    std::istringstream iss(rm_space(input));
    int tour = 1;
    std::string variable;
    auto circuits = this->getCircuit();
    bool found = false;

    while (getline(iss, tmp, '=')) {
        if (tour == 1) {
            found = false;
            for (const auto &circuit : circuits) {
                if (tmp == circuit.first) {
                    variable = tmp;
                    found = true;
                }
            }
            if (!found)
                return false;
        }
        if (tour == 2) {
            if (tmp != "0" && tmp != "1" && tmp != "U")
                return false;
            else {
                if (tmp == "U")
                    this->_circuit_input[variable] = (-true);
                else
                    this->_circuit_input[variable] = std::stoi(tmp);
                return true;
            }
        }
        tour++;
    }
    return false;
}

void break_loop(int signum)
{
    flag = 1;
}

void Circuit::loop()
{
    flag = 0;
    signal(SIGINT, break_loop);
    while (1) {
        if (flag == 1)
            break;
        this->simulate();
        this->display();
    }
    return;
}


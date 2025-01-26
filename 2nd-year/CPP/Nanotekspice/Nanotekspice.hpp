/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** Nanotekspice
*/

#ifndef NANOTEKSPICE_HPP_
#define NANOTEKSPICE_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include "Circuit.hpp"
#include "specialComponent/TrueComponent.hpp"
#include "specialComponent/FalseComponent.hpp"
#include "specialComponent/ClockComponent.hpp"
#include "specialComponent/InputComponent.hpp"
#include "specialComponent/OutputComponent.hpp"
#include "specialComponent/LoggerComponent.hpp"
#include "elementaryComponent/AndComponent.hpp"
#include "elementaryComponent/OrComponent.hpp"
#include "elementaryComponent/XorComponent.hpp"
#include "elementaryComponent/InverterComponent.hpp"
#include "gateComponent/ForComponent.hpp"
#include "gateComponent/FNorComponent.hpp"
#include "gateComponent/FNandComponent.hpp"
#include "gateComponent/FxorComponent.hpp"
#include "gateComponent/Sinverter.hpp"
#include "gateComponent/FandComponent.hpp"
#include "advancedComponent/C4008.hpp"

class Nanotekspice {
    public:
        Nanotekspice() {
            this->_circuit = new Circuit;
        }
        ~Nanotekspice() = default;
        Circuit *getCircuit(){
            return this->_circuit;
        }
        void setCircuit(Circuit *circuit){
            this->_circuit = circuit;
        }
        void run();
    protected:
    private:
        Circuit *_circuit;
};

std::string check_space(const std::string &str);

#endif /* !NANOTEKSPICE_HPP_ */

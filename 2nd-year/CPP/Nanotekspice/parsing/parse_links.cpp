/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** parse_links
*/

#include "../Nanotekspice.hpp"
#include "../Parser.hpp"

int Circuit::check_4k_comp(std::smatch match)
{
    auto circuits_disp = this->getCircuit_disp();
    if (circuits_disp[match[1]] == "4069") {
        size_t pin1 = stoi(match[2]) < 7 ? stoi(match[2]) - 1 : stoi(match[2]) + 1;
        if (stoi(match[4]) == pin1)
            return 1;
        return 0;
    } else if (circuits_disp[match[1]] == "4008") {
        if (stoi(match[2]) == 10) {
            if (6 == stoi(match[4]) || 7 == stoi(match[4]) || 9 == stoi(match[4]))
                return 1;
            return 0;
        }
        if (stoi(match[2]) == 11) {
            if (4 == stoi(match[4]) || 5 == stoi(match[4]))
                return 1;
            return 0;
        }
        if (stoi(match[2]) == 12) {
            if (2 == stoi(match[4]) || 3 == stoi(match[4]))
                return 1;
            return 0;
        }
        if (stoi(match[2]) == 13) {
            if (1 == stoi(match[4]) || 15 == stoi(match[4]))
                return 1;
            return 0;
        }
    } else if (circuits_disp[match[1]] == "4001" || circuits_disp[match[1]] == "4011" || circuits_disp[match[1]] == "4030" || circuits_disp[match[1]] == "4071" || circuits_disp[match[1]] == "4081") {
        size_t pin1 = stoi(match[2]) == 3 || stoi(match[2]) == 10 ? stoi(match[2]) - 1 : stoi(match[2]) + 1;
        size_t pin2 = stoi(match[2]) == 3 || stoi(match[2]) == 10 ? stoi(match[2]) - 2 : stoi(match[2]) + 2;
        if (stoi(match[4]) == pin1 || stoi(match[4]) == pin2)
            return 1;
        return 0;
    }
    return 1;
}

int isInVector(const std::vector<int> vec, int value) {
    if (vec[0] == -1)
        return 0;
    if (std::find(vec.begin(), vec.end(), value) != vec.end()) {
        return 1;
    } else {
        return 0;
    }
}

void Parser::check_values(std::smatch match, Nanotekspice *nts)
{
    std::map<std::string, nts::IComponent *> circuit = nts->getCircuit()->getCircuit();
    if (circuit.find(match[1]) == circuit.end()) {
        throw Error("Unknow component name \'" + std::string(match[1]) + "\'.\n");
    }
    if (circuit.find(match[3]) == circuit.end()) {
        throw Error("Unknow component name \'" + std::string(match[3]) + "\'.\n");
    }
    if (std::stoi(match[2]) < 1 || std::stoi(match[2]) > nts->getCircuit()->getComponent(match[1])->getMaxPin()) {
        throw Error("Unknow component pin \'" + std::string(match[2]) + "\'.\n");
    }
    if (std::stoi(match[4]) < 1 || std::stoi(match[4]) > nts->getCircuit()->getComponent(match[3])->getMaxPin()) {
        throw Error("Unknow component pin \'" + std::string(match[4]) + "\'.\n");
    }
    if (isInVector(nts->getCircuit()->getComponent(match[1])->getBannedPin(), std::stoi(match[2])) == 1) {
        throw Error("Error: Pin \'" + std::string(match[2]) + "\' is banned\n");
    }
    if (isInVector(nts->getCircuit()->getComponent(match[3])->getBannedPin(), std::stoi(match[4])) == 1) {
        throw Error("Error: Pin \'" + std::string(match[4]) + "\' is banned\n");
    }
    if (std::string(match[1]) == std::string(match[3])) {
        if (nts->getCircuit()->check_4k_comp(match) == 0)
            return;
        throw Error("Error: Can't link a component to itself\n");
    }
}

void Parser::parse_links(std::vector<std::vector<std::string>> &file, Nanotekspice *nts)
{
    std::regex pattern("^(\\w+):(\\d+)\\s(\\w+):(\\d+)(\\s\\w*)?");

    for (int i = 0; i < file[1].size(); i++) {
        std::smatch match;
        if (std::regex_search(file[1][i], match, pattern)) {
            if (std::string(match[1])[0] == '#')
                continue;
            if (match[5] != "" && match[5] != " " && std::string(match[5])[0] != '#')
                throw Error("Error: " + std::string(match[5]) + " doesn't match\n");
            check_values(match, nts);                                        // check if pin is vali
            nts::IComponent *input = nts->getCircuit()->getComponent(match[1]);
            nts->getCircuit()->getComponent(match[3])->setLink(std::stoi(match[4]), input, std::stoi(match[2]));
        } else {
            throw Error("Error: Invalid link\n");
        }
    }

}
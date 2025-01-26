/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** parse_chipset
*/

#include "../Nanotekspice.hpp"
#include "../Parser.hpp"

void compo_switch(Nanotekspice *nts, std::string comp_tmp, std::string line)
{
    if (comp_tmp == "input") {
        nts->getCircuit()->addComponent(line, new nts::InputComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "output") {
        nts->getCircuit()->addComponent(line, new nts::OutputComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "true") {
        nts->getCircuit()->addComponent(line, new nts::TrueComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "false") {
        nts->getCircuit()->addComponent(line, new nts::FalseComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "and") {
        nts->getCircuit()->addComponent(line, new nts::AndComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "or") {
        nts->getCircuit()->addComponent(line, new nts::OrComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "xor") {
        nts->getCircuit()->addComponent(line, new nts::XorComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "not") {
        nts->getCircuit()->addComponent(line, new nts::InverterComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4081") {
        nts->getCircuit()->addComponent(line, new nts::FandComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4001") {
        nts->getCircuit()->addComponent(line, new nts::FNorComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4011") {
        nts->getCircuit()->addComponent(line, new nts::FNandComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4030") {
        nts->getCircuit()->addComponent(line, new nts::FxorComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4069") {
        nts->getCircuit()->addComponent(line, new nts::Sinverter());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4071") {
        nts->getCircuit()->addComponent(line, new nts::ForComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "logger") {
        nts->getCircuit()->addComponent(line, new nts::LoggerComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "clock") {
        nts->getCircuit()->addComponent(line, new nts::ClockComponent());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
    if (comp_tmp == "4008") {
        nts->getCircuit()->addComponent(line, new nts::C4008());
        nts->getCircuit()->addComponent_disp(line, comp_tmp);
    }
}

void Parser::parse_chipset(std::vector<std::vector<std::string>> &file, Nanotekspice *nts)
{
    std::vector<std::string> gates = {"input", "output", "true", "false", "clock", "and", "or", "xor", "not", "4001", "4011", "4030", "4069", "4071", "4081", "4008", "4013", "4017", "4040", "4094", "4512", "4514", "4801", "2716", "logger"};
    bool found = false;
    std::string compo;
    std::regex pattern("^(\\w+)\\s(\\w+)(\\s\\w*)?");

    for (int i = 0; i < file[0].size(); i++) {
       std::smatch match;
        if (std::regex_search(file[0][i], match, pattern)) {
            compo = match[1];
            found = false;
            if (compo[0] == '#')
                continue;
            if (match[3] != "" && match[3] != " " && std::string(match[3])[0] != '#')
                throw Error("Error: " + std::string(match[3]) + " doesn't match\n");
            for (const auto &gate : gates) {
                if (compo == gate) {
                    found = true;
                    break;
                }
            }
            if (found)
                compo_switch(nts, match[1], match[2]);
            else
                throw Error("Error: " + compo + " is an invalid component\n");
        } else {
            if (file[0][i][0] == '#')
                continue;
            throw Error("Error: " + file[0][i] + " is an invalid line\n");
        }
    }
}
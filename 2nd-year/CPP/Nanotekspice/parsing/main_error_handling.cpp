/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** main_error_handling
*/

#include "../Nanotekspice.hpp"
#include "../Parser.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

bool hasNtsExtension(const std::string& filename) {
    if (filename.size() < 4) {
        return false;
    }
    return filename.substr(filename.size() - 4) == ".nts";
}

std::string check_space(const std::string &str)
{
    std::string s = str;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());

    std::istringstream iss(s);
    std::string result;
    std::string word;

    while (iss >> word) {
        if (!result.empty())
            result += " ";
        result += word;
    }

    return result;
}

void Parser::readfile(std::string file, std::vector<std::vector<std::string>> &file_content)
{
    std::string line;
    std::vector<std::string> chipsets;
    std::vector<std::string> links;
    std::ifstream input_file(file);
    int k = 0;

    if (!input_file.is_open() || !hasNtsExtension(file)) {
        throw Error(file + " cannot be open\n");
    }
    while (getline(input_file, file)) {
        file = check_space(file);
        if (k == 1)
            chipsets.push_back(file);
        if (k == 2 && file[0] != '#')
            links.push_back(file);
        if (file.find(".chipsets:") != std::string::npos) {
            if (k != 0)
                throw Error("Wrong order\n");
            k = 1;
            continue;
        }
        if (file.find(".links:") != std::string::npos) {
            if (k != 1)
                throw Error("Wrong order\n");
            k = 2;
            continue;
        }
        if (k == 0 && file[0] != '#' && file[0] != '\0' && file[0] != ' ')
            throw Error("Unknow command\n");
    }
    input_file.close();


    for (int i = 0; i < chipsets.size(); i++) {
        if (chipsets[i] == ".links:" || chipsets[i] == ".chipsets:" || chipsets[i] == "\0") {
            chipsets.erase(chipsets.begin() + i);
            i = 0;
        }
    }
    for (int i = 0; i < links.size(); i++) {
        if (links[i] == ".links:" || links[i] == ".chipsets:" || links[i] == "\0" || links[i] == "\n") {
            links.erase(links.begin() + i);
            i = 0;
        }
    }
    if (chipsets.empty() || links.empty())
        throw Error("Error in file\n");
    file_content.push_back(chipsets);
    file_content.push_back(links);
    if (k != 2)
        throw Error("Error in file\n");
}

void Parser::search_values(std::vector<std::vector<std::string>> &file, Nanotekspice *nts)
{
    parse_chipset(file, nts);
    parse_links(file, nts);
}

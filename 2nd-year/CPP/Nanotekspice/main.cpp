/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** main
*/

#include "Parser.hpp"

int main(int argc, char **argv)
{
    std::vector<std::vector<std::string>> file_content;

    if (argc != 2)
        return 84;

    Nanotekspice nts;
    try {
        Parser::readfile(argv[1], file_content);
        Parser::search_values(file_content, &nts);
    }
    catch (const std::exception &e) {
        std::cerr << e.what();
        exit(84);
    }
    nts.run();
    return 0;
}
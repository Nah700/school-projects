/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-tekspice-julien.dufaur
** File description:
** Parser
*/

#include "Nanotekspice.hpp"
#include <vector>
#include <regex>

#ifndef PARSER_HPP_
#define PARSER_HPP_

class Parser {
    public:
        class Error : public std::exception {
            public:
                Error(const std::string &error) : error(std::move(error))
                {
                };
                const char *what() const noexcept override
                {
                    return this->error.c_str();
                };
            private:
                std::string error;
        };
        static void readfile(std::string file, std::vector<std::vector<std::string>> &file_content);
        static void search_values(std::vector<std::vector<std::string>> &file, Nanotekspice *nts);
        static void parse_chipset(std::vector<std::vector<std::string>> &file, Nanotekspice *nts);
        static void parse_links(std::vector<std::vector<std::string>> &file, Nanotekspice *nts);
        static void check_values(std::smatch match, Nanotekspice *nts);

};

#endif

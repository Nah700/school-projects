/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-julien.dufaur
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <unistd.h>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Core.hpp"

void resetLeaderboardFile() {
    std::ifstream inFile("leaderboard.txt");
    if (!inFile.good()) {
        return;
    }

    std::string line;
    std::regex pattern("^([a-zA-Z0-9_]+) = (\\d+):(E|A)$");
    std::vector<std::string> lines;

    while (std::getline(inFile, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, pattern)) {
            std::string username = matches[1].str();
            int score = std::stoi(matches[2].str());
            if (matches[3].str() == "A") {
                line = username + " = " + std::to_string(score) + ":E";
            }
            lines.push_back(line);
        }
    }
    inFile.close();

    std::ofstream outFile("leaderboard.txt");
    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;

    std::string lib = argv[1];
    arcade::Core core;
    try {
        core.retrieveLibs(lib);
        resetLeaderboardFile();
        core.run();
    } catch (LibError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

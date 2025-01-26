/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** inOneWE
*/

#include "Raytracer.hpp"

void usage()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl <<
        "  SCENE_FILE: scene configuration" << std::endl;
}

int main(int argc, char **argv) {
    std::string filecfg = "";

    if (argc != 2) {
        usage();
        return 84;
    }
    if (argc == 2)
        filecfg = argv[1];
    if (filecfg == "--help") {
        usage();
        return 0;
    }

    try {
        Raytracer::Parser parser(filecfg);
        Raytracer::Raytracer raytracer(parser);
        std::string ppm = raytracer.getCamera()->render(*raytracer.getScene());
        auto plugin = parser.loadPlugin("displayPlugin.so");
        if (!plugin)
            return 0;
        plugin->init(ppm);
        while (plugin->isWindowOpen()) {
            plugin->update();
            plugin->render();
        }
    } catch (const Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

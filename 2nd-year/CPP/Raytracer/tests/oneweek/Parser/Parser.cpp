/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Parser
*/

#include "Parser.hpp"

namespace Raytracer {

    void CfgHandler::loadLib(const std::string &sceneFile) {
        try {
            cfg.readFile(sceneFile.c_str());
        } catch(const libconfig::FileIOException &fioex) {
            throw Error("I/O error while reading file.");
        } catch(const libconfig::ParseException &pex) {
            throw Error("Parse error at " + std::string(pex.getFile()) +
                ":" + std::to_string(pex.getLine()) + " - " + pex.getError());
        }
    }

    void CfgHandler::setCamera() {
        try {
            _camera = &cfg.lookup("camera");
        } catch(const libconfig::SettingNotFoundException &nfex) {
            throw Error("Camera setting not found in configuration file.");
        }
    }

    void CfgHandler::setPrimitives() {
        try {
            _primitives = &cfg.lookup("primitives");
        } catch(const libconfig::SettingNotFoundException &nfex) {
            throw Error("Primitives setting not found in configuration file.");
        }
    }

    void CfgHandler::setPlugins() {
        try {
            _plugins = &cfg.lookup("plugins")["plugins"];
        } catch(const libconfig::SettingNotFoundException &nfex) {
            throw Error("Plugins setting not found in configuration file.");
        }
    }

    libconfig::Setting *CfgHandler::getCamera() {
        return _camera;
    }

    libconfig::Setting *CfgHandler::getPrimitives() {
        return _primitives;
    }

    libconfig::Setting *CfgHandler::getPlugins() {
        return _plugins;
    }
        
    Parser::Parser(const std::string &sceneFile) {
        libHandler.loadLib(sceneFile);
        libHandler.setCamera();
        libHandler.setPrimitives();
        libHandler.setPlugins();
        _camera = libHandler.getCamera();
        _primitives = libHandler.getPrimitives();
        _plugins = libHandler.getPlugins();

        // // Parse lights settings
        // try {
        //     libconfig::Setting &lights = cfg.lookup("lights");
        //     double ambient = lights["ambient"];
        //     double diffuse = lights["diffuse"];
        //     std::cout << "Lights: ambient=" << ambient << ", diffuse=" << diffuse << std::endl;

        // } catch(const libconfig::SettingNotFoundException &nfex) {
        //     throw Error("Lights setting not found in configuration file.");
        // }
    }

    std::tuple<int, int> Parser::getCRes() {
        return {
            (*_camera)["resolution"]["height"],
            (*_camera)["resolution"]["width"]
        };
    }

    std::tuple<int, int, int> Parser::getCPos() {
        return {
            (*_camera)["position"]["x"],
            (*_camera)["position"]["y"],
            (*_camera)["position"]["z"]
        };
    }

    std::tuple<double, double, double> Parser::convertToModal(int x, int y, int z) {
        auto res = this->getCRes();
        std::tuple<double, double, double> ress = {
            static_cast<double>(x) / static_cast<double>(std::get<1>(res)),
            static_cast<double>(y) / static_cast<double>(std::get<0>(res)),
            static_cast<double>(z)
        };
        return ress;
    }

    std::tuple<double, double, double> Parser::convertRGBToModal(int x, int y, int z) {
        std::tuple<double, double, double> ress = {
            static_cast<double>(x) / 255,
            static_cast<double>(y) / 255,
            static_cast<double>(z) / 255
        };
        return ress;
    }

    Math::Point3d Parser::getCOrig() {
        std::tuple<double, double, double> pos = this->getCPos();
        std::tuple<double, double, double> posModal = convertToModal(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos));

        return Math::Point3d(std::get<0>(posModal), std::get<1>(posModal), std::get<2>(posModal));
    }

    float Parser::getCFov() {
        return (*_camera)["fieldOfView"];
    }

    std::vector<std::tuple<double, Math::Point3d, Math::Point3d>> Parser::getSpheres() {
        std::vector<std::tuple<double, Math::Point3d, Math::Point3d>> vecspheres;

        try {
            libconfig::Setting &spheres = (*_primitives)["spheres"];

            for(int i = 0; i < spheres.getLength(); ++i) {
                libconfig::Setting &sphere = spheres[i];
                int x = sphere["x"];
                int y = sphere["y"];
                int z = sphere["z"];
                int radius = sphere["r"];
                int r = sphere["color"]["r"];
                int g = sphere["color"]["g"];
                int b = sphere["color"]["b"];
                std::tuple<double, double, double> pos = convertToModal(x, y, z);
                std::tuple<double, double, double> rgb = convertRGBToModal(r, g, b);
                auto res = this->getCRes();
                double ratioW = static_cast<double>(radius) / static_cast<double>(std::get<1>(res));
                double ratioH = static_cast<double>(radius) / static_cast<double>(std::get<0>(res));
                double rad = sqrt(pow(ratioW, 2) + pow(ratioH, 2));
                vecspheres.push_back({
                    rad,
                    Math::Point3d(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos)),
                    Math::Point3d(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb))});
            }
        } catch(const libconfig::SettingNotFoundException &nfex) {
            throw Error("Spheres setting not found in configuration file.");
        }
        return vecspheres;
    }

    std::vector<std::pair<std::string, CreatePrimitiveFunc>> Parser::loadPlugins() {
        std::vector<std::pair<std::string, CreatePrimitiveFunc>>
            vecprimitives;
        std::vector<std::string> pluginNames;

        for(int i = 0; i < (*_plugins).getLength(); ++i) {
            std::string name;
            try {
                name = (*_plugins)[i]["name"].c_str();
                pluginNames.push_back(name);
            } catch(const libconfig::SettingNotFoundException &nfex) {
                throw Error("Plugin name not found in configuration file.");
            }
        }

        for (const auto & entry : std::filesystem::directory_iterator("plugins")) {
            std::string entryPath = entry.path();

            auto it = std::find_if(pluginNames.begin(), pluginNames.end(), [&entryPath](const std::string& name) {
                return entryPath.find(name)!= std::string::npos;
            });

            if (it != pluginNames.end()) {
                std::cout << "Found " << *it << " in " << entryPath << std::endl;
                LibHandler loader;
                loader.ArcadeDlopen(entryPath.c_str());

                std::string type = reinterpret_cast<std::string(*)()>(loader.ArcadeDlsym("getType"))();
                std::cout << "Type: " << type << std::endl;
                CreatePrimitiveFunc createPrimitive = reinterpret_cast<CreatePrimitiveFunc>(loader.ArcadeDlsym("createPrimitive"));

                vecprimitives.push_back({type, createPrimitive});
                loader.ArcadeDlclose();
            }
        }

        return vecprimitives;
    }

}


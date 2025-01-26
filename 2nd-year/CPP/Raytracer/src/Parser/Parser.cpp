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
    }

    std::pair<int, int> Parser::getRes() {
        int imageWidth = getWidth();
        double ratio = 16.0 / 9.0;

        return std::pair<int, int>(imageWidth, (int(imageWidth / ratio) < 1) ? 1 : int(imageWidth / ratio));
    }

    std::tuple<double, double, double> Parser::convertToModal(double x, double y, double z) {
        auto imageRes = getRes();
        std::tuple<double, double, double> ress = {
            static_cast<double>(x) / static_cast<double>(imageRes.first),
            static_cast<double>(y) / static_cast<double>(imageRes.second),
            static_cast<double>(z)
        };
        return ress;
        // return {x, y, z};
    }

    std::tuple<double, double, double> Parser::convertRGBToModal(double x, double y, double z) {
        std::tuple<double, double, double> ress = {
            static_cast<double>(x) / 255,
            static_cast<double>(y) / 255,
            static_cast<double>(z) / 255
        };
        return ress;
        return {x, y, z};
    }

    int Parser::getWidth() {
        return (*_camera)["imageWidth"];
    }

    int Parser::getSamplesPerPixel() {
        return (*_camera)["samplesPerPixel"];
    }

    double Parser::getFov() {
        return (*_camera)["fov"];
    }

    double Parser::getDefocus() {
        return (*_camera)["defocus"];
    }

    double Parser::getFocus() {
        return (*_camera)["focus"];
    }

    std::pair<Math::Point3d, Math::Point3d> Parser::getLookFromAt() {
        libconfig::Setting &lookFromAt = (*_camera)["lookFromAt"];
        double x = lookFromAt[0]["x"];
        double y = lookFromAt[0]["y"];
        double z = lookFromAt[0]["z"];
        double x2 = lookFromAt[1]["x"];
        double y2 = lookFromAt[1]["y"];
        double z2 = lookFromAt[1]["z"];
        std::tuple<double, double, double> pos = convertToModal(x, y, z);
        std::tuple<double, double, double> pos2 = convertToModal(x2, y2, z2);
        return {Math::Point3d(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos)),
            Math::Point3d(std::get<0>(pos2), std::get<1>(pos2), std::get<2>(pos2))};
    }

    Math::Point3d Parser::getBackground() {
        if (!_camera->exists("background")) {
            return Math::Point3d(-1, -1, -1);
        }

        libconfig::Setting &background = (*_camera)["background"];
        double r = background["r"];
        double g = background["g"];
        double b = background["b"];

        std::tuple<double, double, double> rgb = convertRGBToModal(r, g, b);
        return Math::Point3d(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
    }

    std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>> Parser::getPrimitives(const char *prim_type) {
        std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>> vecspheres;

        std::string primitive_type = prim_type;
        std::transform(primitive_type.begin(), primitive_type.end(), primitive_type.begin(), ::tolower);
        if (primitive_type.back() != 's')
            primitive_type += "s";
        try {
            libconfig::Setting &spheres = (*_primitives)[primitive_type.c_str()];

            for (int i = 0; i < spheres.getLength(); ++i) {
                libconfig::Setting &sphere = spheres[i];
                Math::Point3d origin(sphere["origin"]["x"], sphere["origin"]["y"], sphere["origin"]["z"]);
                double radius = sphere["radius"];
                std::shared_ptr<IMaterial> material;

                auto modOrigin = convertToModal(origin.X, origin.Y, origin.Z);
                origin = Math::Point3d(std::get<0>(modOrigin), std::get<1>(modOrigin), std::get<2>(modOrigin));

                if (sphere.exists("material")) {
                    libconfig::Setting &matType = sphere["material"];

                    if (std::string(matType["type"]) == "lambertian") {
                        auto rgb = Math::Point3d(matType["color"]["r"], matType["color"]["g"], matType["color"]["b"]);
                        auto modColor = convertRGBToModal(rgb.X, rgb.Y, rgb.Z);
                        material = std::make_shared<Lambertian>(Math::Point3d(std::get<0>(modColor), std::get<1>(modColor), std::get<2>(modColor)));
                    } else if (std::string(matType["type"]) == "dielectric") {
                        material = std::make_shared<Dielectric>(matType["refractionIndex"]);
                    } else if (std::string(matType["type"]) == "metal") {
                        auto rgb = Math::Point3d(matType["color"]["r"], matType["color"]["g"], matType["color"]["b"]);
                        auto modColor = convertRGBToModal(rgb.X, rgb.Y, rgb.Z);
                        material = std::make_shared<Metal>(Math::Point3d(std::get<0>(modColor), std::get<1>(modColor), std::get<2>(modColor)), matType["fuzz"]);
                    } else if (std::string(matType["type"]) == "diffuseLight") {
                        auto rgb = Math::Point3d(matType["color"]["r"], matType["color"]["g"], matType["color"]["b"]);
                        auto modColor = convertRGBToModal(rgb.X, rgb.Y, rgb.Z);
                        material = std::make_shared<DiffuseLight>(Math::Point3d(std::get<0>(modColor), std::get<1>(modColor), std::get<2>(modColor)));
                    } else {
                        throw Error("Material type not found in configuration file.");
                    }
                }

                vecspheres.push_back({origin, radius, material});
            }
        } catch (const libconfig::SettingNotFoundException &nfex) {
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
                LibHandler loader;
                loader.ArcadeDlopen(entryPath.c_str());

                std::string type = reinterpret_cast<std::string(*)()>(loader.ArcadeDlsym("getType"))();
                CreatePrimitiveFunc createPrimitive = reinterpret_cast<CreatePrimitiveFunc>(loader.ArcadeDlsym("createPrimitive"));

                vecprimitives.push_back({type, createPrimitive});
                // loader.ArcadeDlclose();
            }
        }

        return vecprimitives;
    }

    std::unique_ptr<IPlugin> Parser::loadPlugin(const char *plugin_name) {
        std::unique_ptr<IPlugin> plugin = nullptr;

        std::vector<std::string> pluginNames;

        for(int i = 0; i < (*_plugins).getLength(); ++i) {
            std::string name;
            try {
                name = (*_plugins)[i]["name"].c_str();
                pluginNames.push_back(name);
            } catch(const libconfig::SettingNotFoundException &nfex) {
                return nullptr;
            }
        }

        for (auto &pluginname : pluginNames) {
            if (pluginname == std::string(plugin_name)) {
                for (const auto & entry : std::filesystem::directory_iterator("plugins")) {
                    std::string entryPath = entry.path();

                    auto it = std::find_if(pluginNames.begin(), pluginNames.end(), [&entryPath](const std::string& name) {
                        return entryPath.find(name)!= std::string::npos;
                    });

                    if (it != pluginNames.end()) {
                        LibHandler loader;
                        loader.ArcadeDlopen(entryPath.c_str());
                        plugin = loader.loadInstance<std::unique_ptr<IPlugin>>();
                        // loader.ArcadeDlclose();
                    }
                }
            }
        }
        return plugin;
    }

}


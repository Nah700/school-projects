/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_
    #include <libconfig.h++>
    #include <iostream>
    #include <tuple>
    #include <memory>
    #include <vector>
    #include <string>
    #include <filesystem>

    #include "../Camera/Camera.hpp"
    #include "../Utils/Error.hpp"
    #include "../LibHandler/LibHandler.hpp"

    using CreatePrimitiveFunc = std::unique_ptr<Raytracer::IPrimitive>(*)(const Math::Point3d&, double, std::shared_ptr<Raytracer::IMaterial>);

namespace Raytracer {
    class CfgHandler {
        public:
            CfgHandler() = default;
            ~CfgHandler() = default;
            void loadLib(const std::string &sceneFile);
            void setCamera();
            void setPrimitives();
            void setPlugins();
            libconfig::Setting *getCamera();
            libconfig::Setting *getPrimitives();
            libconfig::Setting *getPlugins();

        private:
            libconfig::Config cfg;
            libconfig::Setting *_camera;
            libconfig::Setting *_primitives;
            libconfig::Setting *_plugins;

    };
    
    class Parser {
        public:
            Parser(const std::string &sceneFile);
            ~Parser() = default;
            std::tuple<int, int> getCRes();
            std::tuple<int, int, int> getCPos();
            float getCFov();
            Math::Point3d getCOrig();
            std::vector<std::tuple<double, Math::Point3d, Math::Point3d>> getSpheres();
            std::vector<std::pair<std::string, CreatePrimitiveFunc>> loadPlugins();
        protected:
            std::tuple<double, double, double> convertRGBToModal(int x, int y, int z);
            std::tuple<double, double, double> convertToModal(int x, int y, int z);
            libconfig::Setting *_camera;
            libconfig::Setting *_primitives;
            libconfig::Setting *_plugins;
            libconfig::Config cfg;
            CfgHandler libHandler;

        private:
    };
}

#endif /* !PARSER_HPP_ */

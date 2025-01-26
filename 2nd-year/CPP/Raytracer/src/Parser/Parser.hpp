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
    #include "../Display/IPlugin.hpp"

    using CreatePrimitiveFunc = std::shared_ptr<Raytracer::IPrimitive>
        (*)(const Math::Point3d &, double, std::shared_ptr<Raytracer::IMaterial>);

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
  
            // Camera
            int getWidth();
            int getSamplesPerPixel();
            double getFov();
            std::pair<Math::Point3d, Math::Point3d> getLookFromAt();
            double getDefocus();
            double getFocus();
            std::pair<int, int> getRes();
            Math::Point3d getBackground();

            std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>> getPrimitives(const char *prim_type);
            std::vector<std::pair<std::string, CreatePrimitiveFunc>> loadPlugins();
            std::unique_ptr<IPlugin> loadPlugin(const char *plugin_name);

        protected:
            std::tuple<double, double, double> convertRGBToModal(double x, double y, double z);
            std::tuple<double, double, double> convertToModal(double x, double y, double z);
            libconfig::Setting *_camera;
            libconfig::Setting *_primitives;
            libconfig::Setting *_plugins;
            libconfig::Config cfg;
            CfgHandler libHandler;

        private:
    };
}

#endif /* !PARSER_HPP_ */

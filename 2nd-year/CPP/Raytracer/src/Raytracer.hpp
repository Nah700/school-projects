/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

#include <functional>
#include "Ray.hpp"
#include "Utils/RayColor.hpp"
#include "Camera/Camera.hpp"
#include "Scene.hpp"
#include "Primitives/Sphere.hpp"
#include "Textures/Materials.hpp"
#include "Parser/Parser.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Cylinder.hpp"
#include "Primitives/Cone.hpp"
#include "Display/IPlugin.hpp"

namespace Raytracer {
    class Raytracer {
        public:
            Raytracer(Parser &parser) {
                initCamera(parser);
                initScene(parser);
            }
            ~Raytracer() = default;
            void initCamera(Parser &parser);
            void initScene(Parser &parser);
            Camera *getCamera() const;
            Scene *getScene() const;
            template<typename T>
            void initAndAddPrimitive(std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>> &prims) {
                for (const auto &prim : prims) {
                    this->_scene->addPrimitive([&]() -> std::shared_ptr<IPrimitive> {
                        return std::make_shared<T>(std::get<0>(prim), std::get<1>(prim), std::get<2>(prim));
                    });
                }
            }
        protected:
        private:
            std::unique_ptr<Camera> _camera;
            std::unique_ptr<Scene> _scene;
    };
};

#endif /* !RAYTRACER_HPP_ */

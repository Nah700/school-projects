/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "Primitives/IPrimitive.hpp"

namespace Raytracer {
    class Scene {
        public:
            Scene() = default;
            Scene(std::shared_ptr<IPrimitive> object);
            ~Scene() = default;
            void addPrimitive(std::function<std::shared_ptr<IPrimitive>()> func);
            void clear();
            bool hit(const Ray &ray, std::pair<double, double> bornes, RayColor &rayColor, std::shared_ptr<IMaterial> &material) const;
            std::vector<std::shared_ptr<IPrimitive>> &getObjects();
        private:
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
    };
}

#endif /* !SCENE_HPP_ */

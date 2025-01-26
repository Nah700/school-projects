/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Scene
*/

#include "Scene.hpp"

namespace Raytracer {
    Scene::Scene(std::shared_ptr<IPrimitive> object)
    {
        this->_primitives.push_back(object);
    }

    void Scene::addPrimitive(std::function<std::shared_ptr<IPrimitive>()> func)
    {
        std::shared_ptr<IPrimitive> primitive = func();
        this->_primitives.push_back(primitive);
    }

    void Scene::clear()
    {
        this->_primitives.clear();
    }

    bool Scene::hit(const Raytracer::Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<Raytracer::IMaterial> &material) const
    {
        Raytracer::RayColor tmpRayColor;
        std::shared_ptr<Raytracer::IMaterial> tmpMaterial;
        bool isHit = false;
        double closest = bornes.second;

        for (auto &tmp : this->_primitives) {
            if (tmp->hits(ray, {bornes.first, closest}, tmpRayColor, tmpMaterial)) {
                isHit = true;
                closest = tmpRayColor._point;
                rayColor = tmpRayColor;
                material = tmpMaterial;
            }
        }
        return isHit;
    }

    std::vector<std::shared_ptr<IPrimitive>> &Scene::getObjects()
    {
        return this->_primitives;
    }
};

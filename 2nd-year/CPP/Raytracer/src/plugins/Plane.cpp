/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Plane
*/

#include "../Primitives/Plane.hpp"

extern "C" {
    std::string getType() {
        return "Plane";
    }

    std::shared_ptr<Raytracer::IPrimitive> createPrimitive(const Math::Point3d &center, double length,
        std::shared_ptr<Raytracer::IMaterial> material) {
        return std::make_shared<Raytracer::Plane>(center, length, material);
    }
}

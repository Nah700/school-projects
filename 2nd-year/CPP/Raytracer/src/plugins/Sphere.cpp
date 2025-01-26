/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Sphere
*/

#include "../Primitives/Sphere.hpp"

extern "C" {
    std::string getType() {
        return "Sphere";
    }

    std::shared_ptr<Raytracer::IPrimitive> createPrimitive(const Math::Point3d &center, double radius,
        std::shared_ptr<Raytracer::IMaterial> material) {
        return std::make_shared<Raytracer::Sphere>(center, radius, material);
    }

}

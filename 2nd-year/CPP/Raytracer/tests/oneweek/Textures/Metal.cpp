/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Metal
*/

#include "Materials.hpp"

namespace Raytracer {

    Metal::Metal(const Math::Point3d &albedo, double fuzz)
    {
        this->setAlbedo(albedo);
        this->_fuzz = fuzz < 1 ? fuzz : 1;
    }

    bool Metal::scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor, Math::Point3d &attenuation,
    Raytracer::Ray &rayOut) const {
        Math::Vector3d reflected = Math::MathUtils::reflect(ray.getDirection(), rayColor._normal);
        reflected = (reflected).normalizeVec(reflected) + (Math::MathUtils::randomUnitVector() * this->_fuzz);
        rayOut = Raytracer::Ray(rayColor._pixel, reflected);
        attenuation = this->getAlbedo();
        return (rayOut.getDirection().dot(rayColor._normal) > 0);
    }
}
/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Lambertian
*/

#include "Materials.hpp"

namespace Raytracer {

    bool Lambertian::scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
        Math::Point3d &attenuation, Raytracer::Ray &rayOut) const {
        (void)ray;
        Math::Vector3d scatter_direction = rayColor._normal + Math::MathUtils::randomUnitVector();
        if (scatter_direction.near_zero())
            scatter_direction = rayColor._normal;
        rayOut = Raytracer::Ray(rayColor._pixel, scatter_direction);
        attenuation = this->getAlbedo();
        return true;
    }
}

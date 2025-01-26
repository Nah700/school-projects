/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Dielectric
*/

#include "Materials.hpp"

namespace Raytracer {

    double Dielectric::reflectance(double cosine, double refractionIndex)
    {
        double r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

    bool Dielectric::scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
        Math::Point3d &attenuation, Raytracer::Ray& scattered) const {

        attenuation = Math::Point3d(1.0, 1.0, 1.0);
        double ri = rayColor.frontFace ? (1.0 / this->_refractionIndex) : this->_refractionIndex;

        Math::Vector3d tmp = ray.getDirection();
        Math::Vector3d unit_direction = tmp.normalizeVec(tmp);
        double cos_theta = fmin(rayColor._normal.dot(unit_direction * -1), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        Math::Vector3d direction;

        if (cannot_refract || reflectance(cos_theta, ri) > Math::Random::random_double())
            direction = Math::MathUtils::reflect(unit_direction, rayColor._normal);
        else
            direction = Math::MathUtils::refract(unit_direction, rayColor._normal, ri);

        scattered = Raytracer::Ray(rayColor._pixel, direction);
        return true;
    }
}
/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** DiffuseLight
*/

#include "Materials.hpp"

namespace Raytracer {
    DiffuseLight::DiffuseLight(const Math::Point3d& albedo)
    {
        this->setAlbedo(albedo);
    }

    Math::Point3d DiffuseLight::emitted() const
    {
        return _albedo;
    }
    bool DiffuseLight::scatter(const Raytracer::Ray& ray, const Raytracer::RayColor& rayColor,
        Math::Point3d& attenuation, Raytracer::Ray& scattered) const
    {
        return false;
    }
};
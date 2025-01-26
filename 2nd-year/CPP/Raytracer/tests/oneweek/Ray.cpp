/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Ray
*/

#include "Ray.hpp"

namespace Raytracer {
    Ray::Ray(const Math::Point3d &origin, const Math::Vector3d &direction)
    {
        this->_origin = origin;
        this->_direction = direction;
    }
    const Math::Point3d &Ray::getOrigin() const
    {
        return this->_origin;
    }
    const Math::Vector3d &Ray::getDirection() const
    {
        return this->_direction;
    }
    Math::Point3d Ray::at(double t) const
    {
        return this->_origin + this->_direction * t;
    }
};

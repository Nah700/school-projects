/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Plane
*/

#include "Plane.hpp"

namespace Raytracer {
    Plane::Plane(const Math::Point3d &center, double length, std::shared_ptr<IMaterial> material)
    {
        this->setOrigin(center);
        this->u = Math::Vector3d(length, 0, 0);
        this->v = Math::Vector3d(0, length, 0);
        Math::Vector3d n = u.cross(v);
        this->_normal = n.normalizeVec(n);
        this->_distance = _normal.dot(Math::MathUtils::transformPointToVector(this->getOrigin()));
        this->w = n / n.dot(n);
        this->setMaterial(material);
    }

    bool Plane::hits(const Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<IMaterial> &materials) const
    {
        double denominator = this->_normal.dot(ray.getDirection());
        double point = 0;

        if (std::fabs(denominator) < 1e-8)
            return false;
        point = (this->_distance - this->_normal.dot(Math::MathUtils::transformPointToVector(ray.getOrigin()))) / denominator;
        if (!Math::MathUtils::contains(point, bornes.first, bornes.second))
            return false;
        Math::Vector3d vec = Math::MathUtils::transformPointToVector(ray.at(point) - this->getOrigin());
        if (Math::MathUtils::contains(w.dot(vec.cross(v)), 0, 1) && Math::MathUtils::contains(w.dot(u.cross(vec)), 0, 1)) {
            rayColor._point = point;
            rayColor._pixel = ray.at(point);
            materials = this->getMaterial();
            rayColor.setFaceNormal(ray, this->_normal);
            return true;
        }
        return false;
    }
};

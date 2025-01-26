/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** sphere
*/

#include "Sphere.hpp"

namespace Raytracer {
    Sphere::Sphere(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material)
    {
        this->setOrigin(center);
        this->_radius = std::fmax(0, radius);
        this->setMaterial(material);
    }

    bool Sphere::hits(const Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<IMaterial> &material) const {
        bool isHit = false;
        Math::Vector3d vec = Math::MathUtils::transformPointToVector(this->getOrigin() - ray.getOrigin());
        double a = ray.getDirection().lengthSquared();
        double b = ray.getDirection().dot(vec);
        double discriminant = b * b - a * (vec.lengthSquared() - this->_radius * this->_radius);

        if (discriminant < 0)
            return false;
        double rootMinus = (b - sqrt(discriminant)) / a;
        double rootPlus = (b + sqrt(discriminant)) / a;
        if (Math::MathUtils::surrounds(rootMinus, bornes.first, bornes.second)){
            rayColor._point = rootMinus;
            rayColor._pixel = ray.at(rayColor._point);
            Math::Vector3d normal = Math::MathUtils::transformPointToVector(rayColor._pixel - this->getOrigin()) / this->_radius;
            rayColor.setFaceNormal(ray, normal);
            material = this->getMaterial();
            isHit = true;
        }
        if (Math::MathUtils::surrounds(rootPlus, bornes.first, bornes.second) && isHit == false){
            rayColor._point = rootPlus;
            rayColor._pixel = ray.at(rayColor._point);
            Math::Vector3d normal = Math::MathUtils::transformPointToVector(rayColor._pixel - this->getOrigin()) / this->_radius;
            rayColor.setFaceNormal(ray, normal);
            material = this->getMaterial();
            isHit = true;
        }
        return isHit;
    }
};

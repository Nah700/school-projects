/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace Raytracer {

    Cylinder::Cylinder(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material)
    {
        this->setOrigin(center);
        this->radius = std::fmax(0, radius);
        this->setMaterial(material);
    }

    bool Cylinder::hits(const Ray &ray, std::pair<double, double> bounds, Raytracer::RayColor &rayColor, std::shared_ptr<IMaterial> &material) const {
        bool isHit = false;
        Math::Vector3d adjustedOrigin = Math::MathUtils::transformPointToVector(ray.getOrigin() - this->getOrigin());

        double a = ray.getDirection().X * ray.getDirection().X + ray.getDirection().Z * ray.getDirection().Z;
        double b = 2 * (adjustedOrigin.X * ray.getDirection().X + adjustedOrigin.Z * ray.getDirection().Z);
        double c = adjustedOrigin.X * adjustedOrigin.X + adjustedOrigin.Z * adjustedOrigin.Z - this->radius * this->radius;

        double discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            double sqrtDiscriminant = sqrt(discriminant);
            double t1 = (-b - sqrtDiscriminant) / (2 * a);
            double t2 = (-b + sqrtDiscriminant) / (2 * a);

            double ts[] = {t1, t2};
            for (double t : ts) {
                double y = ray.at(t).Y - this->getOrigin().Y;
                if (t >= bounds.first && t <= bounds.second && y >= 0 && y <= this->height) {
                    rayColor._point = t;
                    rayColor._pixel = ray.at(t);
                    Math::Vector3d normal(rayColor._pixel.X - this->getOrigin().X, 0, rayColor._pixel.Z - this->getOrigin().Z);
                    normal.normalizeVec(normal);
                    rayColor.setFaceNormal(ray, normal);
                    material = this->getMaterial();
                    isHit = true;
                    break;  // Remove break if we need all intersections
                }
            }
        }
        return isHit;
    }
};
/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Cone
*/

#include "Cone.hpp"

namespace Raytracer {

    Cone::Cone(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material)
    {
        this->setOrigin(center);
        this->radius = std::fmax(0, radius);
        this->setMaterial(material);
    }

    bool Cone::hits(const Ray &ray, std::pair<double, double> bounds, RayColor &rayColor, std::shared_ptr<IMaterial> &material) const {
        bool isHit = false;
        Math::Vector3d adjustedOrigin = Math::MathUtils::transformPointToVector(ray.getOrigin() - this->getOrigin());
        double a = ray.getDirection().X * ray.getDirection().X + ray.getDirection().Z * ray.getDirection().Z - (ray.getDirection().Y * ray.getDirection().Y * (radius / height) * (radius / height));
        double b = 2 * (adjustedOrigin.X * ray.getDirection().X + adjustedOrigin.Z * ray.getDirection().Z - adjustedOrigin.Y * ray.getDirection().Y * (radius / height));
        double c = adjustedOrigin.X * adjustedOrigin.X + adjustedOrigin.Z * adjustedOrigin.Z - adjustedOrigin.Y * adjustedOrigin.Y * (radius / height) * (radius / height) - this->radius * this->radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            double sqrtDiscriminant = sqrt(discriminant);
            double t1 = (-b - sqrtDiscriminant) / (2 * a);
            double t2 = (-b + sqrtDiscriminant) / (2 * a);
            double ts[] = {t1, t2};
            for (double t : ts) {
                double y = ray.at(t).Y - this->getOrigin().Y;
                if (t >= bounds.first && t <= bounds.second && y >= 0 && y <= this->height) {
                    double coneRadius = this->radius * (1 - y / this->height);
                    if (sqrt(pow(ray.at(t).X - this->getOrigin().X, 2) + pow(ray.at(t).Z - this->getOrigin().Z, 2)) <= coneRadius) {
                        rayColor._point = t;
                        rayColor._pixel = ray.at(t);
                        Math::Vector3d normal(rayColor._pixel.X - this->getOrigin().X, y / this->height, rayColor._pixel.Z - this->getOrigin().Z);
                        normal.normalizeVec(normal);
                        rayColor.setFaceNormal(ray, normal);
                        material = this->getMaterial();
                        isHit = true;
                        break;
                    }
                }
            }
        }
        Math::Vector3d capNormal(0, 1, 0);
        double dotProduct = ray.getDirection().dot(capNormal);
        if (dotProduct!= 0) {
            double t = (this->height - adjustedOrigin.Y) / dotProduct;
            if (t >= bounds.first && t <= bounds.second) {
                Math::Point3d intersection = ray.at(t);
                if (sqrt(pow(intersection.X - this->getOrigin().X, 2) + pow(intersection.Z - this->getOrigin().Z, 2)) <= this->radius) {
                    rayColor._point = t;
                    rayColor._pixel = intersection;
                    rayColor.setFaceNormal(ray, capNormal);
                    material = this->getMaterial();
                    isHit = true;
                }
            }
        }
        return isHit;
    }
};
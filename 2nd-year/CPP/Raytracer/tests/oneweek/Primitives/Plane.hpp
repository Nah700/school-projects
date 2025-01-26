/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** plane
*/

#ifndef PLANE_HPP_
    #define PLANE_HPP_

#include "APrimitive.hpp"

namespace Raytracer {
    class Plane : public APrimitive {
        public:
            Plane(const Math::Point3d &center, double length, std::shared_ptr<IMaterial> mat);
            bool hits(const Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<IMaterial> &materials) const override;
        private:
            Math::Vector3d u, v, w, _normal;
            double _distance;
    };
};

#endif /* !PLANE_HPP_ */

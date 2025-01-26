/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "APrimitive.hpp"

namespace Raytracer {
    class Cylinder : public APrimitive {
        public:
            Cylinder(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material);
            ~Cylinder() = default;

            bool hits(const Ray &ray, std::pair<double, double> bornes, RayColor &rayColor, std::shared_ptr<IMaterial> &material) const;
            double getHeight() const
            {
                return this->height;
            }
        private:
            double radius;
            double height = 1.0;
    };
};

#endif /* !CYLINDER_HPP_ */

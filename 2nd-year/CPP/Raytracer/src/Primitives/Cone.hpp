/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "APrimitive.hpp"

namespace Raytracer {
    class Cone : public APrimitive {
        public:
            Cone(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material);
            ~Cone() = default;

            bool hits(const Ray &ray, std::pair<double, double> bounds, RayColor &rayColor, std::shared_ptr<IMaterial> &material) const;

            double getHeight() const { return this->height; }
            double getRadius() const { return this->radius; }

        private:
            double radius;
            double height = 2.0;
    };
};

#endif /*!CONE_HPP_ */

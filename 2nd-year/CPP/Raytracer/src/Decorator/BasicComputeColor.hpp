/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** BasicComputeColor
*/

#ifndef BASICCOMPUTECOLOR_HPP_
#define BASICCOMPUTECOLOR_HPP_

#include "IComputeColor.hpp"

namespace Raytracer {
    class BasicComputeColor : public IComputeColor {
        public:
            Math::Point3d computeColor(const Ray &ray, int depth, const Scene &world, Math::Point3d background) const override {
                (void)world;
                (void)depth;
                (void)background;
                Math::Vector3d tmp = ray.getDirection();
                Math::Vector3d direction = tmp.normalizeVec(tmp);
                double a = (direction.Y + 1.0) * 0.5;
                return  Math::Point3d(1.0, 1.0, 1.0) * (1.0 - a) + Math::Point3d(0.5, 0.7, 1.0) * a;
            }
    };
};

#endif /* !BASICCOMPUTECOLOR_HPP_ */

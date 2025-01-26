/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** BackgroundDecorator
*/

#ifndef BACKGROUNDDECORATOR_HPP_
#define BACKGROUNDDECORATOR_HPP_

#include "IComputeColor.hpp"

namespace Raytracer {
    class BackgroundDecorator : public IComputeColor {
        public:
            Math::Point3d computeColor(const Ray &ray, int depth, const Scene &world, Math::Point3d background) const override {
                (void)world;
                (void)depth;
                (void)ray;
                return background;
            }
    };
};

#endif /* !BACKGROUNDDECORATOR_HPP_ */

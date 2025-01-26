/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** MaterialComputeColor
*/

#ifndef MATERIALCOMPUTECOLOR_HPP
#define MATERIALCOMPUTECOLOR_HPP

#include "IComputeColor.hpp"

namespace Raytracer {
    class MaterialComputeColor : public IComputeColor {
        public:
            MaterialComputeColor(std::shared_ptr<IComputeColor> component) : _component(component) {}
            Math::Point3d computeColor(const Ray &ray, int depth, const Scene &world, Math::Point3d background) const override {
                RayColor rayColor;
                std::shared_ptr<IMaterial> material;

                if (depth <= 0)
                    return Math::Point3d(0,0,0);
                if (world.hit(ray, {0.001, Math::MathUtils::posInfinity}, rayColor, material)) {
                    Ray scattered;
                    Math::Point3d attenuation;
                    if (material->scatter(ray, rayColor, attenuation, scattered)) {
                        return material->emitted() + attenuation * computeColor(scattered, depth - 1, world, background);
                    }
                    return material->emitted();
                }
                return _component->computeColor(ray, depth, world, background);
            }
        private:
            std::shared_ptr<IComputeColor> _component;
    };
};

#endif // MATERIALCOMPUTECOLOR_HPP

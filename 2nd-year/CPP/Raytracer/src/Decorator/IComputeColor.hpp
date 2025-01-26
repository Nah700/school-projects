/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** IComputeColor
*/

#ifndef ICOMPUTECOLOR_HPP_
#define ICOMPUTECOLOR_HPP_

#include "../Ray.hpp"
#include "../Scene.hpp"
#include "../Maths/MathUtils.hpp"

namespace Raytracer {
    class IComputeColor {
        public:
            virtual ~IComputeColor() = default;
            virtual Math::Point3d computeColor(const Ray &ray, int depth, const Scene &world, Math::Point3d background) const = 0;
        protected:
        private:
    };
};

#endif /* !ICOMPUTECOLOR_HPP_ */

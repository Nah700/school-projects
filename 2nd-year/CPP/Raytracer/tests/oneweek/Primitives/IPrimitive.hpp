/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "../Ray.hpp"
#include "../Textures/Materials.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual bool hits(const Raytracer::Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<Raytracer::IMaterial> &material) const = 0;
            virtual Math::Point3d getOrigin() const = 0;
            virtual std::shared_ptr<IMaterial> getMaterial() const = 0;
            virtual void setOrigin(const Math::Point3d &origin) = 0;
            virtual void setMaterial(std::shared_ptr<IMaterial> material) = 0;
        protected:
        private:
    };
};

#endif /* !IPRIMITIVE_HPP_ */

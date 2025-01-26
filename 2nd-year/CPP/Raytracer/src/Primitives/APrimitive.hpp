/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** APrimitives
*/

#ifndef APRIMITIVES_HPP_
#define APRIMITIVES_HPP_

#include "IPrimitive.hpp"

namespace Raytracer {
    class APrimitive : public IPrimitive{
        public:
            APrimitive() = default;
            ~APrimitive() = default;
            Math::Point3d getOrigin() const override {
                return this->_origin;
            }
            std::shared_ptr<IMaterial> getMaterial() const override {
                return this->_material;
            }
            void setOrigin(const Math::Point3d &origin) override {
                this->_origin = origin;
            }
            void setMaterial(std::shared_ptr<IMaterial> material) override {
                this->_material = material;
            }
            virtual bool hits(const Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<IMaterial> &material) const = 0;
        protected:
        private:
            Math::Point3d _origin;
            std::shared_ptr<IMaterial> _material;
    };
};

#endif /* !APRIMITIVES_HPP_ */

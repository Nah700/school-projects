#ifndef HITTABLE_H
#define HITTABLE_H

#include "../Ray.hpp"
#include "../Maths/MathUtils.hpp"

namespace Raytracer {
    class RayColor {
        public:
            Math::Point3d _pixel;
            Math::Vector3d _normal;
            double _point;
            bool frontFace;
            void setFaceNormal(const Raytracer::Ray &r, const Math::Vector3d &normal) {
                this->frontFace = normal.dot(r.getDirection()) < 0;
                this->_normal = this->frontFace ? normal : normal * -1;
            }
    };
}

#endif
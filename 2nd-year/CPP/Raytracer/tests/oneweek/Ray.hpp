#ifndef RAY_H
#define RAY_H

#include "Maths/MathUtils.hpp"

namespace Raytracer {
    class Ray {
        public:
            Ray() = default;
            Ray(const Math::Point3d &origin, const Math::Vector3d &direction);
            ~Ray() = default;
            const Math::Point3d &getOrigin() const;
            const Math::Vector3d &getDirection() const;
            Math::Point3d at(double t) const;
        private:
            Math::Point3d _origin;
            Math::Vector3d _direction;
    };
}

#endif

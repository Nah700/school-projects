#ifndef SPHERE_H
#define SPHERE_H

#include "APrimitive.hpp"

namespace Raytracer {
  class Sphere : public APrimitive {
      public:
        Sphere(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material);
        ~Sphere() = default;

        bool hits(const Ray &ray, std::pair<double, double> bornes, Raytracer::RayColor &rayColor, std::shared_ptr<IMaterial> &material) const override;
      private:
        double _radius;
  };
}

#endif

#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Utils/RayColor.hpp"

namespace Raytracer {
    class IMaterial {
        public:
            virtual ~IMaterial() = default;
            virtual Math::Point3d getAlbedo() const = 0;
            virtual void setAlbedo(const Math::Point3d &albedo) = 0;
            virtual Math::Point3d emitted() const = 0;
            virtual bool scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
              Math::Point3d &attenuation, Raytracer::Ray &rayOut) const = 0;
    };

    class AMaterial : public IMaterial {
        public:
            AMaterial() = default;
            ~AMaterial() = default;

            Math::Point3d getAlbedo() const override
            {
                return this->_albedo;
            }
            void setAlbedo(const Math::Point3d &albedo) {
                this->_albedo = albedo;
            }
            Math::Point3d emitted() const
            {
                return Math::Point3d(0, 0, 0);
            }
            bool scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
              Math::Point3d &attenuation, Raytracer::Ray &rayOut) const
            {
                (void)ray;
                (void)rayColor;
                (void)attenuation;
                (void)rayOut;
                return false;
            }
        private:
            Math::Point3d _albedo;
    };

    class Lambertian : public AMaterial {
        public:
            Lambertian(const Math::Point3d &albedo)
            {
                this->setAlbedo(albedo);
            }
            bool scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
            Math::Point3d &attenuation, Raytracer::Ray &rayOut) const override;
    };

    class Metal : public AMaterial {
        public:
            Metal(const Math::Point3d &albedo, double fuzz);
            bool scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
            Math::Point3d &attenuation, Raytracer::Ray &rayOut) const override;
        private:
            double _fuzz;
    };

    class Dielectric : public AMaterial {
        public:
            Dielectric(double refractionIndex) {
              this->_refractionIndex = refractionIndex;
            }
            bool scatter(const Raytracer::Ray &ray, const Raytracer::RayColor &rayColor,
            Math::Point3d &attenuation, Raytracer::Ray &rayOut) const override;
            static double reflectance(double cosine, double refractionIndex);
        private:
            double _refractionIndex;
    };

    class DiffuseLight : public AMaterial {
        public:
            DiffuseLight(const Math::Point3d& albedo);
            bool scatter(const Raytracer::Ray& ray, const Raytracer::RayColor& rayColor,
                Math::Point3d &attenuation, Raytracer::Ray &rayOut) const override;
            Math::Point3d emitted() const override;
    };
};

#endif

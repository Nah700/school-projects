/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** MathUtils
*/

#ifndef MATHUTILS_HPP_
#define MATHUTILS_HPP_

#include <cmath>
#include "Point3d.hpp"

namespace Math {
    class MathUtils {
        public:
            static Vector3d transformPointToVector(Point3d point);
            static Point3d transformVectorToPoint(Vector3d vector);
            static double degreeToRadian(double degree);
            static double size(double min, double max);
            static bool contains(double x, double min, double max);
            static bool surrounds(double x, double min, double max);
            static double clamp(double x, double min, double max);
            static Math::Vector3d randomUnit();
            static Math::Vector3d randomUnitSphere();
            static Math::Vector3d randomUnitVector();
            static Math::Vector3d randomHemisphere(const Math::Vector3d &normal);
            static Math::Vector3d reflect(const Math::Vector3d &vec, const Math::Vector3d &normal);
            static Math::Vector3d refract(const Math::Vector3d &uv, const Math::Vector3d &normal, double etat);
            static constexpr double posInfinity = std::numeric_limits<double>::infinity();
            static constexpr double negInfinity = std::numeric_limits<double>::infinity();
            static constexpr double pi = M_PI;
    };
};

#endif /* !MATHUTILS_HPP_ */

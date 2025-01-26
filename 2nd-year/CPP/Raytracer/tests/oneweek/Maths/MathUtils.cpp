/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** MathUtils
*/

#include "MathUtils.hpp"

namespace Math {
    Vector3d MathUtils::transformPointToVector(Point3d point) {
        return Vector3d(point.X, point.Y, point.Z);
    }
    Point3d MathUtils::transformVectorToPoint(Vector3d vector) {
        return Point3d(vector.X, vector.Y, vector.Z);
    }
    double MathUtils::degreeToRadian(double degree) {
        return degree * pi / 180.0;
    }
    double MathUtils::size(double min, double max) {
        return max - min;
    }
    bool MathUtils::contains(double x, double min, double max) {
        return min <= x && x <= max;
    }
    bool MathUtils::surrounds(double x, double min, double max) {
        return min < x && x < max;
    }
    double MathUtils::clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
    Math::Vector3d MathUtils::randomUnit() {
        while (true) {
            Math::Vector3d pixel = Math::Vector3d(Math::Random::random_double(-1,1), Math::Random::random_double(-1,1), 0);
            if (pixel.lengthSquared() < 1)
                return pixel;
        }
    }
    Math::Vector3d MathUtils::randomUnitSphere() {
        while (true) {
            Math::Vector3d pixel = Math::Vector3d::random(-1,1);
            if (pixel.lengthSquared() < 1)
                return pixel;
        }
    }
    Math::Vector3d MathUtils::randomUnitVector() {
        return (randomUnitSphere()).normalizeVec((randomUnitSphere()));
    }
    Math::Vector3d MathUtils::randomHemisphere(const Math::Vector3d &normal) {
        Math::Vector3d unit = randomUnitVector();
        if (unit.dot(normal) > 0.0)
            return unit;
        return unit * -1;
    }
    Math::Vector3d MathUtils::reflect(const Math::Vector3d &vec, const Math::Vector3d &normal) {
        return vec - normal * 2 * vec.dot(normal);
    }
    Math::Vector3d MathUtils::refract(const Math::Vector3d &uv, const Math::Vector3d &normal, double etat) {
        double cosinus = fmin(normal.dot(uv * -1), 1.0);
        Math::Vector3d rayPerpendicular =  (uv + normal * cosinus) * etat;
        Math::Vector3d rayParallel = normal * -sqrt(std::fabs(1.0 - rayPerpendicular.lengthSquared()));
        return rayPerpendicular + rayParallel;
    }
};
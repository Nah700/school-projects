/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Vector3d
*/

#include <complex>
#include "Vector3d.hpp"
#include "Point3d.hpp"

namespace Math {
    Vector3d::Vector3d()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vector3d::Vector3d(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    Vector3d::Vector3d(const Vector3d &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
    }

    Vector3d::Vector3d(Vector3d &&other) noexcept
    {
        X = std::move(other.X);
        Y = std::move(other.Y);
        Z = std::move(other.Z);
    }

    double Vector3d::length() const
    {
        return sqrt(X * X + Y * Y + Z * Z);
    }

    double Vector3d::lengthSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }
} // namespace Math

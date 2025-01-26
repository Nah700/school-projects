/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Point3d
*/

#include "Point3d.hpp"

namespace Math {
    Point3d::Point3d()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    Point3d::Point3d(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    Point3d::Point3d(const Point3d &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
    }

    double Point3d::length() const
    {
        return sqrt(X * X + Y * Y + Z * Z);
    }

    double Point3d::lengthSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }
} // namespace Math

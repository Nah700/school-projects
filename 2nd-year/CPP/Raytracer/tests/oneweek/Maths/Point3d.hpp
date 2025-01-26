/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Math::Point3d
*/

#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <complex>
#include <ostream>
#include <iomanip>
#include "Vector3d.hpp"

namespace Math {
    class Point3d {
        public:
            Point3d();
            Point3d(double x, double y, double z);
            ~Point3d() = default;
            Point3d(const Point3d &other);
            Point3d &operator=(const Point3d& other) {
                if (this != &other) {
                    X = other.X;
                    Y = other.Y;
                    Z = other.Z;
                }
                return *this;
            }
            Point3d &operator=(Point3d&& other) noexcept {
                if (this != &other) {
                    X = std::move(other.X);
                    Y = std::move(other.Y);
                    Z = std::move(other.Z);
                }
                return *this;
            }
            Point3d operator+(const Point3d &other) const {
                return Point3d(X + other.X, Y + other.Y, Z + other.Z);
            }
            Point3d operator-(const Point3d &other) const {
                return Point3d(X - other.X, Y - other.Y, Z - other.Z);
            }
            Point3d operator+(const Vector3d &other) const {
                std::tuple<double, double, double> t = other.getXYZ();
                return Point3d(X + std::get<0>(t), Y + std::get<1>(t), Z + std::get<2>(t));
            }
            Point3d operator-(const Vector3d &other) const {
                std::tuple<double, double, double> t = other.getXYZ();
                return Point3d(X - std::get<0>(t), Y - std::get<1>(t), Z - std::get<2>(t));
            }
            bool operator==(const Point3d &other) const {
                if (X == other.X && Y == other.Y && Z == other.Z)
                    return true;
                return false;
            }
            Point3d operator+=(const Point3d &other) {
                X += other.X;
                Y += other.Y;
                Z += other.Z;
                return *this;
            }
            Point3d operator-=(const Point3d &other) {
                X -= other.X;
                Y -= other.Y;
                Z -= other.Z;
                return *this;
            }
            Point3d operator+=(const Vector3d &other) {
                std::tuple<double, double, double> t = other.getXYZ();
                X += std::get<0>(t);
                Y += std::get<1>(t);
                Z += std::get<2>(t);
                return *this;
            }
            Point3d operator-=(const Vector3d &other) {
                std::tuple<double, double, double> t = other.getXYZ();
                X -= std::get<0>(t);
                Y -= std::get<1>(t);
                Z -= std::get<2>(t);
                return *this;
            }
            Point3d operator*(const double &other) const {
                return Point3d(X * other, Y * other, Z * other);
            }
            Point3d operator*(const Point3d &other) const {
                return Point3d(X * other.X, Y * other.Y, Z * other.Z);
            }
            Point3d operator/(const double &other) const {
                return Point3d(X / other, Y / other, Z / other);
            }
            Point3d operator*=(const double &other) {
                X *= other;
                Y *= other;
                Z *= other;
                return *this;
            }
            Point3d operator/=(const double &other) {
                X /= other;
                Y /= other;
                Z /= other;
                return *this;
            }
            Point3d operator+(const double &other) const {
                return Point3d(X + other, Y + other, Z + other);
            }
            Point3d operator-(const double &other) const {
                return Point3d(X - other, Y - other, Z - other);
            }
            std::tuple<double, double, double> getXYZ() const {
                return std::make_tuple(X, Y, Z);
            }

            friend std::ostream& operator<<(std::ostream& os, const Point3d& p) {
                return os << std::fixed << std::setprecision(3) << "Point3d(" << p.X << ", " << p.Y << ", " << p.Z << ")";
            }
            Math::Point3d getCenterPix(float focal, std::pair<Math::Vector3d, Math::Vector3d> screen, std::pair<Math::Vector3d, Math::Vector3d> pixel)
            {
                Math::Point3d upperLeft = (*this) - Math::Vector3d(0, 0 , focal) - screen.first - screen.second;
                return (upperLeft + (pixel.first + pixel.second) * 0.5);
            }
            static Math::Point3d random() {
                return Math::Point3d(Math::Random::random_double(), Math::Random::random_double(), Math::Random::random_double());
            }

            static Math::Point3d random(double min, double max) {
                return Math::Point3d(Math::Random::random_double(min,max), Math::Random::random_double(min,max), Math::Random::random_double(min,max));
            }
            double length() const;
            double lengthSquared() const;

            double X;
            double Y;
            double Z;
        protected:
        private:
    };
};

#endif /* !POINT3_HPP_ */

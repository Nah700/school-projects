/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Vector3d
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <iomanip>
#include "Random.hpp"

namespace Math {
    class Vector3d {
        public:
            Vector3d();
            Vector3d(double x, double y, double z);
            ~Vector3d() = default;
            Vector3d(const Vector3d &other);
            Vector3d(Vector3d &&other) noexcept;

            void setValues(double x, double y, double z) {
                X = x;
                Y = y;
                Z = z;
            }
            Vector3d perpendicular()
            {
                // Check if the vector is mostly pointing in x or z direction
                if (std::fabs(this->X) < std::fabs(this->Z)) {
                    return {this->Y, -this->X, 0};  // Cross product with unit vector along z-axis if x is smaller
                } else {
                    return {0, -this->Z, this->Y};  // Otherwise, cross with unit vector along x-axis
                }
            }
            Vector3d &operator=(const Vector3d& other) {
                if (this != &other) {
                    X = other.X;
                    Y = other.Y;
                    Z = other.Z;
                }
                return *this;
            }
            Vector3d &operator=(Vector3d&& other) noexcept {
                if (this != &other) {
                    X = std::move(other.X);
                    Y = std::move(other.Y);
                    Z = std::move(other.Z);
                }
                return *this;
            }
            double length() const;
            Vector3d operator+(const Vector3d &other) const {
                return Vector3d(X + other.X, Y + other.Y, Z + other.Z);
            }
            Vector3d operator-(const Vector3d &other) const {
                return Vector3d(X - other.X, Y - other.Y, Z - other.Z);
            }
            Vector3d operator*(const Vector3d &other) const {
                return Vector3d(X * other.X, Y * other.Y, Z * other.Z);
            }
            Vector3d operator/(const Vector3d &other) const {
                return Vector3d(X / other.X, Y / other.Y, Z / other.Z);
            }
            Vector3d operator+=(const Vector3d &other) {
                X += other.X;
                Y += other.Y;
                Z += other.Z;
                return *this;
            }
            Vector3d operator-=(const Vector3d &other) {
                X -= other.X;
                Y -= other.Y;
                Z -= other.Z;
                return *this;
            }
            Vector3d operator*=(const Vector3d &other) {
                X *= other.X;
                Y *= other.Y;
                Z *= other.Z;
                return *this;
            }
            Vector3d operator/=(const Vector3d &other) {
                X /= other.X;
                Y /= other.Y;
                Z /= other.Z;
                return *this;
            }
            Vector3d operator+(const double &other) const {
                return Vector3d(X + other, Y + other, Z + other);
            }
            Vector3d operator-(const double &other) const {
                return Vector3d(X - other, Y - other, Z - other);
            }
            Vector3d operator*(const double &other) const {
                return Vector3d(X * other, Y * other, Z * other);
            }
            Vector3d operator/(const double &other) const {
                return Vector3d(X / other, Y / other, Z / other);
            }
            Vector3d operator+=(const double &other) {
                X += other;
                Y += other;
                Z += other;
                return *this;
            }
            Vector3d operator-=(const double &other) {
                X -= other;
                Y -= other;
                Z -= other;
                return *this;
            }
            Vector3d operator*=(const double &other) {
                X *= other;
                Y *= other;
                Z *= other;
                return *this;
            }
            Vector3d operator/=(const double &other) {
                X /= other;
                Y /= other;
                Z /= other;
                return *this;
            }
            double dot(const Vector3d& other) const {
                return X * other.X + Y * other.Y + Z * other.Z;
            }
            Vector3d cross(const Vector3d& other) const {
                return Vector3d(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
            }
            std::tuple<double, double, double> getXYZ() const {
                return std::make_tuple(X, Y, Z);
            }

            Vector3d normalizeVec(const Vector3d &vec) {
                return vec / vec.length();
            }

            bool near_zero() const {
                auto s = 1e-8;
                return (fabs(X) < s) && (fabs(Y) < s) && (fabs(Z) < s);
            }

            static Vector3d reflect(const Vector3d& v, const Vector3d& n) {
                return v - n * v.dot(n) * 2;
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector3d& p) {
                return os << std::fixed << std::setprecision(3) << "Vector3d(" << p.X << ", " << p.Y << ", " << p.Z << ")";
            }

            double lengthSquared() const;

            Math::Vector3d refract(const Math::Vector3d& uv, const Math::Vector3d& n, double etai_over_etat) {
                auto cos_theta = fmin(n.dot(uv * -1), 1.0);
                Math::Vector3d r_out_perp =  (uv + n * cos_theta) * etai_over_etat;
                Math::Vector3d r_out_parallel = n * -sqrt(fabs(1.0 - r_out_perp.lengthSquared()));
                return r_out_perp + r_out_parallel;
            }
            static Math::Vector3d random() {
                return Math::Vector3d(Math::Random::random_double(), Math::Random::random_double(), Math::Random::random_double());
            }

            static Math::Vector3d random(double min, double max) {
                return Math::Vector3d(Math::Random::random_double(min,max), Math::Random::random_double(min,max), Math::Random::random_double(min,max));
            }

            double X;
            double Y;
            double Z;
        protected:
        private:
    };
};

#endif /* !VECTOR3D_HPP_ */

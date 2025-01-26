/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Raytracer {
    Camera::Camera(int imageWidth, int samplesPerPixel, double fov, std::pair<Math::Point3d, Math::Point3d> lookFromAt, double defocus, double focus, Math::Point3d background)
    {
        this->_samplesPerPixel = samplesPerPixel;
        this->vfov = fov;
        this->_lookFromAt = lookFromAt;
        this->_defocusAngle = defocus;
        this->_focusDist = focus;
        this->_background = background;
        this->_pixelSamplesScale = 1.0 / this->_samplesPerPixel;
        this->_center = this->_lookFromAt.first;

        this->_imageRes = std::pair<int, int>(imageWidth, (int(imageWidth / _ratio) < 1) ? 1 : int(imageWidth / this->_ratio));
        double viewportHeight = 2 * tan(Math::MathUtils::degreeToRadian(vfov) / 2) * _focusDist;
        double viewportWidth = viewportHeight * (double(imageWidth)/this->_imageRes.second);
        Math::Point3d fromAtCalc = this->_lookFromAt.first - this->_lookFromAt.second;
        Math::Vector3d w = Math::MathUtils::transformPointToVector(fromAtCalc).normalizeVec(Math::MathUtils::transformPointToVector(fromAtCalc));
        Math::Vector3d u = vup.cross(w).normalizeVec(vup.cross(w));
        Math::Vector3d v = w.cross(u);
        this->_pixelDelta.first = (u * viewportWidth) / imageWidth;
        this->_pixelDelta.second = (v * -1 * viewportHeight) / this->_imageRes.second;
        Math::Point3d viewportUpperLeft = this->_center - (w * _focusDist) - (u * viewportWidth) / 2 - (v * -1 * viewportHeight) / 2;
        this->_pixelCenter = viewportUpperLeft + (this->_pixelDelta.first + this->_pixelDelta.second) * 0.5;
        double defocusRadius = _focusDist * tan(Math::MathUtils::degreeToRadian(this->_defocusAngle / 2));
        this->_defocusDisk.first = u * defocusRadius;
        this->_defocusDisk.second = v * defocusRadius;
        if (background == Math::Point3d(-1, -1, -1))
            this->_decorator = std::make_shared<Raytracer::BasicComputeColor>();
        else
            this->_decorator = std::make_shared<Raytracer::BackgroundDecorator>();
        this->_decorator = std::make_shared<Raytracer::MaterialComputeColor>(this->_decorator);
    }

    std::tuple<int, int, int> Camera::convertModalToColor(const Math::Point3d &color)
    {
        int r = int(256 * Math::MathUtils::clamp((color.X > 0 ? sqrt(color.X) : 0.0), 0.0, 0.9));
        int g = int(256 * Math::MathUtils::clamp((color.Y > 0 ? sqrt(color.Y) : 0.0), 0.0, 0.9));
        int b = int(256 * Math::MathUtils::clamp((color.Z > 0 ? sqrt(color.Z) : 0.0), 0.0, 0.9));
        return std::make_tuple(r, g, b);
    }

    Math::Point3d Camera::getSampleColor(int i, int j, const Raytracer::Scene &scene)
    {
        Math::Point3d pixelColor(0, 0, 0);
        for (int s = 0; s < this->_samplesPerPixel; s++) {
            Raytracer::Ray r = getRay(i, j);
            pixelColor += this->_decorator->computeColor(r, this->_maxDepth, scene, this->_background);
        }
        return pixelColor;
    }

    void createLoadingBar(int j, int loadingMax, int imageHeight)
    {
        int loadingActual = (j * loadingMax) / imageHeight;
        int percentage = (j * 100) / imageHeight + 1;
        std::string bar = std::string(loadingActual, ' ') + "🚀";

        for (int i = 0; i < loadingMax - loadingActual - 1; i++)
            bar += "•";
        std::cerr << "\r[" << bar << "🌔] " << percentage << "%" << std::flush;
    }

    std::string Camera::render(const Raytracer::Scene &scene)
    {
        std::string buffer;
        int loadingMax = 50;

        buffer += "P3\n" + std::to_string(this->_imageRes.first) + " " + std::to_string(this->_imageRes.second) + "\n255\n";
        for (int j = 0; j < this->_imageRes.second; j++) {
            createLoadingBar(j, loadingMax, this->_imageRes.second);
            for (int i = 0; i < this->_imageRes.first; i++) {
                Math::Point3d pixelColor = getSampleColor(i, j, scene);
                std::tuple<int, int, int> tmp = convertModalToColor(pixelColor * _pixelSamplesScale);
                buffer += (std::to_string(std::get<0>(tmp)) + " " + std::to_string(std::get<1>(tmp)) + " " + std::to_string(std::get<2>(tmp)) + "\n");
            }

        }
        std::cout << buffer;
        std::cerr << "\r" << std::string(loadingMax + 10, ' ') << "\r";
        std::cerr << "\rRaytracer goes to the Moon !" << std::endl;
        return buffer;
    }


    Raytracer::Ray Camera::getRay(int i, int j) const
    {
        Math::Vector3d offset = sampleSquare();
        Math::Point3d pixel = _pixelCenter + (this->_pixelDelta.first * (i + offset.X)) + (this->_pixelDelta.second * (j + offset.Y));
        Math::Point3d origin = (_defocusAngle <= 0) ? this->_center : defocusDiskSample();
        Math::Vector3d direction = Math::MathUtils::transformPointToVector(pixel - origin);
        return Raytracer::Ray(origin, direction);
    }

    Math::Vector3d Camera::sampleSquare() const
    {
        return Math::Vector3d(Math::Random::random_double() - 0.5, Math::Random::random_double() - 0.5, 0);
    }

    Math::Point3d Camera::defocusDiskSample() const
    {
        Math::Vector3d pixel = Math::MathUtils::randomUnit();
        return this->_center + (this->_defocusDisk.first * pixel.X) + (this->_defocusDisk.second * pixel.Y);
    }
};

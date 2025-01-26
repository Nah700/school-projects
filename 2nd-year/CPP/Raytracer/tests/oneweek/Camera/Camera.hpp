/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../Textures/Materials.hpp"
#include "../Scene.hpp"
#include "../Decorator/BasicComputeColor.hpp"
#include "../Decorator/MaterialComputeColor.hpp"
#include "../Decorator/BackgroundDecorator.hpp"

namespace Raytracer {
    class Camera {
        public:
            Camera(int imageWidth, int samplesPerPixel, double fov, std::pair<Math::Point3d, Math::Point3d> lookFromAt, double defocus, double focus, Math::Point3d background = Math::Point3d(-1, -1, -1));
            ~Camera() = default;

            void render(const Scene &world);
            Ray getRay(int i, int j) const;
            Math::Vector3d sampleSquare() const;
            Math::Point3d defocusDiskSample() const;
            std::tuple<int, int, int> convertModalToColor(const Math::Point3d &color);
            Math::Point3d getSampleColor(int i, int j, const Scene &scene);
        private:
            std::pair<int, int> _imageRes;
            Math::Point3d _center, _pixelCenter, _background;
            double _pixelSamplesScale, vfov, _defocusAngle, _focusDist;
            std::pair<Math::Vector3d, Math::Vector3d> _pixelDelta, _defocusDisk;

            double _ratio = 16.0 / 9.0;
            int _samplesPerPixel;
            int _maxDepth = 50;
            std::pair<Math::Point3d, Math::Point3d> _lookFromAt;
            Math::Vector3d vup = Math::Vector3d(0,1,0);
            std::shared_ptr<IComputeColor> _decorator;
    };
};

#endif /* !CAMERA_HPP_ */

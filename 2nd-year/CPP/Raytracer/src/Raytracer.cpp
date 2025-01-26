/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-nahim.kandari
** File description:
** Raytracer
*/

#include "Raytracer.hpp"

namespace Raytracer {

    void Raytracer::initCamera(Parser &parser)
    {
        this->_camera = std::make_unique<Camera>(parser.getWidth(), parser.getSamplesPerPixel(), parser.getFov(), parser.getLookFromAt(), parser.getDefocus(), parser.getFocus(), parser.getBackground());
    }

    void Raytracer::initScene(Parser &parser)
    {
        this->_scene = std::make_unique<Scene>();
        std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>>  primsSphere = parser.getPrimitives("spheres");
        this->initAndAddPrimitive<Sphere>(primsSphere);
        std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>>  primsPlanes = parser.getPrimitives("planes");
        this->initAndAddPrimitive<Plane>(primsPlanes);
        // std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>>  primsCylinders = parser.getPrimitives("cylinders");
        // this->initAndAddPrimitive<Cylinder>(primsCylinders);
        // std::vector<std::tuple<Math::Point3d, double, std::shared_ptr<IMaterial>>>  primsCones = parser.getPrimitives("cones");
        // this->initAndAddPrimitive<Cone>(primsCones);
    }

    Camera *Raytracer::getCamera() const
    {
        return this->_camera.get();
    }

    Scene *Raytracer::getScene() const
    {
        return this->_scene.get();
    }
}
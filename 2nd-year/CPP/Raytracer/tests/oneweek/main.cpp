/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** inOneWE
*/

#include <functional>
#include "Ray.hpp"
#include "Utils/RayColor.hpp"
#include "Camera/Camera.hpp"
#include "Scene.hpp"
#include "Primitives/Sphere.hpp"
#include "Textures/Materials.hpp"
#include "Parser/Parser.hpp"
#include "Primitives/Plane.hpp"

void usage()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl <<
        "  SCENE_FILE: scene configuration" << std::endl;
}

int main(int argc, char **argv) {
    std::string filecfg = "";

    if (argc != 2) {
        usage();
        return 84;
    }
    if (argc == 2)
        filecfg = argv[1];
    if (filecfg == "--help") {
        usage();
        return 0;
    }

    Raytracer::Parser parser(filecfg);
    Raytracer::Scene world;

    auto ground_material = std::make_shared<Raytracer::Lambertian>(Math::Point3d(0.5, 0.5, 0.5));
    auto origin = Math::Point3d(0, -1000, 0);
    auto radius = 1000.0;

    std::vector<std::pair<std::string, CreatePrimitiveFunc>> plugins = parser.loadPlugins();

    for (auto &plugin : plugins) {
        if (plugin.first == "Sphere") {
            std::cout << "PLUGIN: " << plugin.first << std::endl;
            world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, ground_material, plugin]() {
                return plugin.second(origin, radius, ground_material);
            }));
        } else if (plugin.first == "Plane") {
            world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, ground_material, plugin]() {
                return plugin.second(origin, radius, ground_material);
            }));
        }
    }

    // world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, ground_material]() {
    //     return std::make_shared<Raytracer::Sphere>(origin, radius, ground_material);
    // }));
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = Math::Random::random_double();
            Math::Point3d center(a + 0.9 * Math::Random::random_double(), 0.2, b + 0.9 * Math::Random::random_double());
            if ((center - Math::Point3d(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Raytracer::IMaterial> sphere_material;
                if (choose_mat < 0.8) {
                    auto albedo = Math::Point3d::random() * Math::Point3d::random();
                    sphere_material = std::make_shared<Raytracer::Lambertian>(albedo);
                    radius = 0.2;
                    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([center, radius, sphere_material]() {
                        return std::make_shared<Raytracer::Sphere>(center, radius, sphere_material);
                    }));
                } else if (choose_mat < 0.95) {
                    auto albedo = Math::Point3d::random(0.5, 1);
                    auto fuzz = Math::Random::random_double(0, 0.5);
                    radius = 0.2;
                    sphere_material = std::make_shared<Raytracer::Metal>(albedo, fuzz);
                    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([center, radius, sphere_material]() {
                        return std::make_shared<Raytracer::Sphere>(center, radius, sphere_material);
                    }));
                } else {
                    sphere_material = std::make_shared<Raytracer::Dielectric>(1.5);
                    radius = 0.2;
                    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([center, radius, sphere_material]() {
                        return std::make_shared<Raytracer::Sphere>(center, radius, sphere_material);
                    }));
                }
            }
        }
    }

    auto material1 = std::make_shared<Raytracer::Dielectric>(1.5);
    origin = Math::Point3d(0, 1, 0);
    radius = 1.0;
    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, material1]() {
        return std::make_shared<Raytracer::Sphere>(origin, radius, material1);
    }));

    auto material2 = std::make_shared<Raytracer::Lambertian>(Math::Point3d(0.4, 0.2, 0.1));
    origin = Math::Point3d(-4, 1, 0);
    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, material2]() {
        return std::make_shared<Raytracer::Sphere>(origin, radius, material2);
    }));

    auto material3 = std::make_shared<Raytracer::Metal>(Math::Point3d(0.7, 0.6, 0.5), 0.0);
    origin = Math::Point3d(4, 1, 0);
    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, material3]() {
        return std::make_shared<Raytracer::Sphere>(origin, radius, material3);
    }));

    auto material4 = std::make_shared<Raytracer::Lambertian>(Math::Point3d(0.2, 1, 0.2));
    origin = Math::Point3d(-2, 1, 0);
    radius = 4.0;
    world.addPrimitive(std::function<std::shared_ptr<Raytracer::IPrimitive>()>([origin, radius, material4]() {
        return std::make_shared<Raytracer::Plane>(origin, radius, material4);
    }));
    Raytracer::Camera cam(400, 10, 20, std::pair<Math::Point3d, Math::Point3d>(Math::Point3d(13,2,3), Math::Point3d(0,0,0)), 0.6, 10.0);
    cam.render(world);
}

**Raytracer**

***Introduction:***

"Raytracer" project is an implementation of a software in C++ allowing to generate realistic images by simulating the inverse path of light, a technique called ray tracing.
The program is designed to create an image from a file describing the scene.

This project must use interfaces for primitives and lights to allow extensibility. It must also use at least two design patterns from a provided list, such as factory, builder, composite, etc. 
Authorized libraries include libconfig++ for parsing the scene configuration file and SFML 2.5.1 for displaying.

Project build can be done using either Makefile or CMake, and plugins can be used to extend functionalities

***Installation:***

Clone the repository
 ```bash
 git clone https://github.com/EpitechPromo2027/B-OOP-400-STG-4-1-raytracer-nahim.kandari.git
 ```

Navigate into the project directory:
```bash
cd B-OOP-400-STG-4-1-raytracer-nahim.kandari
```

Compilation
```bash
sudo apt install libconfig++-dev
./build.sh
raytracer scenes/scene.cfg
```

***Usage:***

To run Raytracer, execute the binary with the required parameters:

```bash
./raytracer <SCENE_FILE>
```

.``SCENE_FILE``: configuration file for a scene with the setup of the camera, some primitives, textures and lights

Here an example of the content from SCENE_FILE

```cpp
# Configuration of the camera
camera :
{
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = -100; z = 20; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0; # In degree
};
# Primitives in the scene
primitives :
{
    # List of spheres
    spheres = (
        { x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; } ,
        { x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
    ) ;
    # List of planes
    planes = (
        { axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
    ) ;
};
# Light configuration
lights :
{
    ambient = 0.4; # Multiplier of ambient light
    diffuse = 0.6; # Multiplier of diffuse light
    # List of point lights
    point = (
        { x = 400; y = 100; z = 500; };
    ) ;
    # List of directional lights
    directional = () ;
};
```

***User documentation:***

To create new scene to run into the binary, go to the "scene" folder, and you can create a new scene following steps from the default ``scene.cfg`` file.

***Developer documentation***

How to create a primitive:

Start by creating a header file for your new primitive, for example, MyPrimitive.hpp.
Declare your class inheriting from APrimitive and include the necessary dependencies.

```cpp
#ifndef MYPRIMITIVE_HPP_
#define MYPRIMITIVE_HPP_

#include "APrimitive.hpp" // Include the header file of the base class

namespace Raytracer {
    class MyPrimitive : public APrimitive {
        // Function and member declarations
    };
}

#endif /* !MYPRIMITIVE_HPP_ */
```

Add the necessary members and functions for your primitive, using the base class as a template.

```cpp
class MyPrimitive : public APrimitive {
public:
    MyPrimitive(const Math::Point3d &center, double radius, std::shared_ptr<IMaterial> material);
    ~MyPrimitive() = default;

    bool hits(const Ray &ray, std::pair<double, double> bounds, RayColor &rayColor, std::shared_ptr<IMaterial> &material) const override;

    double getHeight() const {
        return this->height;
    }

private:
    double radius;
    double height = 1.0;
};
```

Implement the hits() function to determine if a ray intersects your primitive.

```cpp
bool MyPrimitive::hits(const Ray &ray, std::pair<double, double> bounds, RayColor &rayColor, std::shared_ptr<IMaterial> &material) const {
    // Implement the intersection logic of your primitive here
}
```

Once your primitive class is defined, you can use it in your ray tracing application.

```cpp
MyPrimitive myPrimitive(/* initialization parameters */);
scene.addPrimitive(std::make_shared<MyPrimitive>(myPrimitive));
```

How to make a materials:

Start by creating a new header file for your Metal material, for example, Metal.hpp.
Declare your class inheriting from AMaterial and include the necessary dependencies.

```cpp
#ifndef METAL_HPP_
#define METAL_HPP_

#include "AMaterial.hpp" // Include the header file of the base class

namespace Raytracer {
    class Metal : public AMaterial {
        // Function and member declarations
    };
}

#endif /* !METAL_HPP_ */
```

Implement the constructor to initialize the metal material with the given albedo and fuzziness.

```cpp
class Metal : public AMaterial {
public:
    Metal(const Math::Point3d &albedo, double fuzz);
};
```

Implement the scatter() function to determine how rays interact with the Metal surface.
Utilize the provided logic for generating scattered rays.

```cpp
bool Metal::scatter(const Ray &ray, const RayColor &rayColor, Math::Point3d &attenuation, Ray &rayOut) const override;
```
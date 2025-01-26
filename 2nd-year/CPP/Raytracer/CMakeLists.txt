cmake_minimum_required(VERSION 3.10)
project(B_OOP_400)
set(CMAKE_CXX_COMPILER "g++")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_compile_options(-std=c++20 -g -Wall -Wextra -O3 -flto -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../plugins/")
set(SRC "src")

add_executable(
    raytracer
    ${SRC}/Camera/Camera.cpp
    ${SRC}/Scene.cpp
    ${SRC}/Maths/Point3d.cpp
    ${SRC}/Maths/Vector3d.cpp
    ${SRC}/Maths/MathUtils.cpp
    ${SRC}/Parser/Parser.cpp
    ${SRC}/LibHandler/LibHandler.cpp
    ${SRC}/Primitives/Plane.cpp
    ${SRC}/Primitives/Sphere.cpp
    ${SRC}/Primitives/Cylinder.cpp
    ${SRC}/Primitives/Cone.cpp
    ${SRC}/Textures/Dielectric.cpp
    ${SRC}/Textures/Lambertian.cpp
    ${SRC}/Textures/Metal.cpp
    ${SRC}/Textures/DiffuseLight.cpp
    ${SRC}/Ray.cpp
    ${SRC}/Raytracer.cpp
    ${SRC}/main.cpp
)
target_link_libraries(raytracer ${LIBCONFIG_LIBRARIES})
target_compile_options(raytracer PUBLIC ${LIBCONFIG_CFLAGS_OTHER})
target_include_directories(raytracer PUBLIC ${LIBCONFIG_INCLUDE_DIRS})

add_library( displayPlugin SHARED
    ${SRC}/Display/DisplayPlugin.cpp
)
target_link_libraries(displayPlugin sfml-graphics sfml-window sfml-system)
set_target_properties(displayPlugin PROPERTIES PREFIX "")

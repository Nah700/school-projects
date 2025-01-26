#!/bin/bash

rm raytracer
mkdir -p build
cd build/
cmake ..
cmake --build .
cd ..

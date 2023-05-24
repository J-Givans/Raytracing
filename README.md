# Raytracing
---

This is a simple path tracer based on [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Build
---

### Prerequisites 
---
CMake v3.20
Conan v3.16
Microsoft Guidelines Support Library v4.0.0
Google Test cci.20210126

### Build And Run
---
1. From the parent directory, run `conan install . -if=build -pr:b=default` to install external dependencies
2. To set up the build, run `cmake -S . -B build --preset release`
3. To build the project, run `cmake --build build --target raytracer`
4. To run the application, `build/raytracer`.
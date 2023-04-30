#include "Common.hpp"
#include "Colour.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

#include <iostream>

using namespace rt;

/// \brief Linearly blend white and blue colours
/// \param[in] ray The ray whose colour at a point is to be computed
/// \returns A blended colour of white and blue
Colour rayColour(Ray const& ray, Hittable const& world) noexcept;

int main()
{
    // Image
    static constexpr double aspectRatio {16.0 / 9.0};
    static constexpr int imgWidth {400};
    static constexpr auto imgHeight = static_cast<int>(imgWidth / aspectRatio);
    static constexpr int samplesPerPixel = 100;

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera cam;

    // Render
    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

    for (auto j = imgHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << '\n' << std::flush;

        for (auto i = 0; i < imgWidth; ++i) {
            Colour pixelColour;

            for (int s = 0; s < samplesPerPixel; ++s) {
                auto const rand = randomDouble();

                auto u = (i + rand) / (imgWidth - 1);
                auto v = (j + rand) / (imgHeight - 1);

                Ray ray = cam.getRay(u, v);
                pixelColour += rayColour(ray, world);
            }

            writeColour(std::cout, pixelColour, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
    return EXIT_SUCCESS;
}

Colour rayColour(Ray const& ray, Hittable const& world) noexcept
{
    if (HitRecord record; world.hit(ray, 0, infinity, record)) {
        return 0.5 * (record.normal + Colour(1, 1, 1));
    }

    Vec3 unitDirection = unitVector(ray.getDirection());    // scale the ray direction to unit length
    auto const t = 0.5 * (unitDirection.y() + 1.0);
    
    // Linearly blend white and blue depending on the height of the y coordinate
    // blendedValue = (1 - t) * startValue + t * endValue
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}
#include "Colour.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Material.hpp"

#include <iostream>

using namespace rt;

/// \brief Linearly blend white and blue colours
/// \param[in] ray The ray whose colour at a point is to be computed
/// \returns A blended colour of white and blue
Colour rayColour(Ray const& ray, Hittable const& world, int recursionDepth) noexcept;

int main()
{
    // Image
    static constexpr double aspectRatio {16.0 / 9.0};
    static constexpr int imgWidth {400};
    static constexpr auto imgHeight = static_cast<int>(imgWidth / aspectRatio);
    static constexpr int samplesPerPixel = 100;
    static constexpr int maxRecursionDepth = 50;

    // World
    HittableList world;

    auto materialGround = std::make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<Lambertian>(Colour(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<Dielectric>(1.5);
    auto materialRight = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.0);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

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
                pixelColour = pixelColour + rayColour(ray, world, maxRecursionDepth);
            }

            writeColour(std::cout, pixelColour, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
    return EXIT_SUCCESS;
}

Colour rayColour(Ray const& ray, Hittable const& world, int recursionDepth) noexcept
{
    // If we've exceeded the ray bounce limit, no more light is gathered
    if (recursionDepth <= 0) {
        return Colour(0, 0, 0);
    }

    if (HitRecord record; world.hit(ray, 0.001, infinity, record)) {
        Ray scattered;
        
        if (Colour attenuation; record.materialPtr->scatter(ray, record, attenuation, scattered)) {
            return attenuation * rayColour(scattered, world, recursionDepth - 1);
        }
        else {
            return Colour(0, 0, 0);
        }
    }

    Vec3 unitDirection = unitVector(ray.getDirection());    // scale the ray direction to unit length
    auto const t = 0.5 * (unitDirection.y() + 1.0);
    
    // Linearly blend white and blue depending on the height of the y coordinate
    // blendedValue = (1 - t) * startValue + t * endValue
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}
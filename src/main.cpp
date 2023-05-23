#include "Colour.hpp"
#include "Common.hpp"
#include "HittableList.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Material.hpp"

#include <iostream>

using namespace rt;

namespace
{
    /// \brief Linearly blend white and blue colours
    /// \param[in] ray The ray whose colour at a point is to be computed
    /// \returns A blended colour of white and blue
    Colour rayColour(Ray const& ray, Hittable const& world, int recursionDepth) noexcept;

    /// \brief Generate lots of random spheres
    /// \returns A list of randomly generated spheres
    HittableList randomScene();
}

int main()
{
    // Image
    static constexpr double aspectRatio {3.0 / 2.0};
    static constexpr int imgWidth {1200};
    static constexpr auto imgHeight = static_cast<int>(imgWidth / aspectRatio);
    static constexpr int samplesPerPixel = 500;
    static constexpr int maxRecursionDepth = 50;

    // World
    HittableList world = randomScene();

    // Camera
    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0, 0, 0);
    Vec3 viewUp(0, 1, 0);
    auto distanceToFocus = 10.0;
    auto aperture = 0.1;
    
    Camera cam(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture, distanceToFocus);

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

namespace 
{
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

    HittableList randomScene()
    {
        auto groundMaterial = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
        
        HittableList world;
        world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

        for (int a = -11; a < 11; ++a) {
            for (int b = -11; b < 11; ++b) {
                auto chooseMaterial = randomDouble();
                auto centre = Point3(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

                if ((centre - Point3(4, 0.2, 0)).length() > 0.9) {
                    std::shared_ptr<Material> sphereMaterial;

                    if (chooseMaterial < 0.8) {
                        // Diffuse
                        auto albedo = Colour::random() * Colour::random();
                        sphereMaterial = std::make_shared<Lambertian>(albedo);
                        world.add(std::make_shared<Sphere>(centre, 0.2, sphereMaterial));
                    }
                    else if (chooseMaterial < 0.95) {
                        // Metal
                        auto albedo = Colour::random(0.5, 1);
                        auto fuzz = randomDouble(0, 0.5);
                        sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                        world.add(std::make_shared<Sphere>(centre, 0.2, sphereMaterial));
                    }
                    else {
                        // Glass
                        sphereMaterial = std::make_shared<Dielectric>(1.5);
                        world.add(std::make_shared<Sphere>(centre, 0.2, sphereMaterial));
                    }
                }
            }
        }

        auto mat1 = std::make_shared<Dielectric>(1.5);
        world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, mat1));

        auto mat2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
        world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, mat2));

        auto mat3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
        world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, mat3));

        return world;
    }
}
#include "Colour.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

#include <iostream>

/// \brief Linearly blend white and blue colours
/// \param[in] ray The ray whose colour at a point is to be computed
/// \returns A blended colour of white and blue
constexpr Colour rayColour(Ray const& ray) noexcept;

int main()
{
    // Image
    static constexpr double aspectRatio {16.0 / 9.0};
    static constexpr int imgWidth {400};
    static constexpr auto imgHeight = static_cast<int>(imgWidth / aspectRatio);

    // Camera
    // The viewport is the region of space that can potentially be imaged onto the film
    static constexpr auto viewportHeight {2.0};
    static constexpr auto viewportWidth {aspectRatio * viewportHeight};
    static constexpr auto focalLength {1.0};    // The distance from the camera to the viewport

    static constexpr Point3 origin; // The position of the camera

    // Offset vectors along the viewport sides used to move the ray endpoint across the viewport
    static constexpr Vec3 horizontal(viewportWidth, 0, 0);
    static constexpr Vec3 vertical(0, viewportHeight, 0);
    
    // The lower-left corner of the viewport
    static constexpr Vec3 lowerLeftCorner { origin - (horizontal / 2) - (vertical / 2) - Vec3(0, 0, focalLength) };

    // Render
    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

    for (auto j = imgHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << '\n' << std::flush;

        for (auto i = 0; i < imgWidth; ++i) {
            // Used to scale the horizontal offset to specify an exact location in the viewport
            auto u = static_cast<double>(i) / (imgWidth - 1);
            
            // Used to scale the vertical offset to specify an exact location in the viewport
            auto v = static_cast<double>(j) / (imgHeight - 1);

            // We traverse the viewport from the upper-left corner, and create a ray at each position
            Ray ray(origin, lowerLeftCorner + (u * horizontal) + (v * vertical) - origin);
            
            // Determine the colour of the ray just created
            Colour pxColour = rayColour(ray);
            
            // Write this colour to stdout
            writeColour(std::cout, pxColour);
        }
    }

    std::cerr << "\nDone.\n";
    return EXIT_SUCCESS;
}

constexpr Colour rayColour(Ray const& ray) noexcept
{
    Vec3 unitDirection = unitVector(ray.getDirection());    // scale the ray direction to unit length
    auto t = 0.5 * (unitDirection.y() + 1.0);
    
    // Linearly blend white and blue depending on the height of the y coordinate
    // blendedValue = (1 - t) * startValue + t * endValue
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}
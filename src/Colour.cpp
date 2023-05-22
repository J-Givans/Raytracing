#include "Colour.hpp"
#include "Common.hpp"

namespace rt
{
    void writeColour(std::ostream& out, Colour const& pixelColour, int const samplesPerPixel)
    {
        auto r = pixelColour.x();
        auto g = pixelColour.y();
        auto b = pixelColour.z();

        // Divide the colour by the number of samples and gamma-correct for gamma = 2.0
        double const scale = 1.0 / samplesPerPixel;

        r = std::sqrt(scale * r);
        g = std::sqrt(scale * g);
        b = std::sqrt(scale * b);

        // Write the translated [0, 255] value of each colour component
        out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
    }
}

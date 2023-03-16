#include "Colour/Colour.hpp"
#include "Common/Common.hpp"

void writeColour(std::ostream& out, Colour const& pixelColour, int const samplesPerPixel)
{
    // Divide the colour by the number of pixels
    double const scale = 1.0 / samplesPerPixel;

    double const r = pixelColour.x() * scale;
    double const g = pixelColour.y() * scale;
    double const b = pixelColour.z() * scale;

    // Write the translated [0, 255] value of each colour component
    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}

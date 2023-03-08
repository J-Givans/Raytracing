#include "Colour.hpp"
#include "Vec3.hpp"

#include <iostream>

int main()
{
    // Image
    static constexpr int imgWidth {256};
    static constexpr int imgHeight {256};

    // Render
    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

    for (auto j = imgHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << '\n' << std::flush;

        for (auto i = 0; i < imgWidth; ++i) {
            Colour pxColour(static_cast<double>(i) / (imgWidth - 1), static_cast<double>(j) / (imgHeight - 1), 0.25);
            writeColour(std::cout, pxColour);
        }
    }

    std::cerr << "\nDone.\n";
    return EXIT_SUCCESS;
}
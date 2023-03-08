#include <iostream>
#include <array>
#include <numeric>

int main()
{
    static constexpr int imgWidth {256};
    static constexpr int imgHeight {256};

    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

    for (auto j = imgHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << '\n' << std::flush;

        for (auto i = 0; i < imgWidth; ++i) {
            auto r = static_cast<double>(i) / (imgWidth - 1);
            auto g = static_cast<double>(j) / (imgHeight - 1);
            static constexpr double b {0.25};
            
            auto ir = static_cast<int>(255.999 * r);
            auto ig = static_cast<int>(255.999 * g);
            auto ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr << "Done.\n";

    return EXIT_SUCCESS;
}
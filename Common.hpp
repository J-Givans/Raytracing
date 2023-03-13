#ifndef COMMON_HPP
#define COMMON_HPP

#include "Ray.hpp"
#include "Vec3.hpp"

#include <cmath>
#include <limits>
#include <random>

inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

constexpr double degreesToRadians(double const degrees) noexcept
{
    return degrees * pi / 180.0;
}

/// \brief Generate a random number between [0.0, 1.0)
/// \returns A random number of type double
inline double randomDouble()
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<> distribution(0.0, 1.0);
    
    return distribution(generator);
}

#endif
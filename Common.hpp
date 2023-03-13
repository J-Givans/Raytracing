#ifndef COMMON_HPP
#define COMMON_HPP

#include "Ray.hpp"
#include "Vec3.hpp"

#include <cmath>
#include <limits>

inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

constexpr double degreesToRadians(double const degrees) noexcept
{
    return degrees * pi / 180.0;
}

#endif
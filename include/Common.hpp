#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>
#include <limits>
#include <random>

namespace rt
{
    inline constexpr double infinity = std::numeric_limits<double>::infinity();
    inline constexpr double pi = 3.1415926535897932385;

    constexpr double degreesToRadians(double const degrees) noexcept
    {
        return degrees * pi / 180.0;
    }

    /// \brief Generate a random number between [0.0, 1.0)
    /// \returns A random real number between [0, 1)
    inline double randomDouble()
    {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        
        return distribution(generator);
    }

    /// \brief Generate a random real number between [min, max)
    /// \param[in] min The lower bound in the range of possible outputs
    /// \param[in] max The upper bound in the range of possible outputs
    /// \returns A random real number between [min, max)
    inline double randomDouble(double const min, double const max)
    {
        return min + (max - min) * randomDouble();
    }

    /// \brief Clamps a value between a pair of boundary value
    /// \param[in] x The input value to be clamped
    /// \param[in] min The lower bound
    /// \param[in] max The upper bound
    /// \returns A value lying within the range [min, max]
    constexpr double clamp(double const x, double const min, double const max) noexcept
    {
        if (x < min) {
            return min;
        }
        else if (x > max) {
            return max;
        }
        else {
            return x;
        }
    }
}

#endif
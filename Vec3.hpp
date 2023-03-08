#ifndef VEC3_HPP
#define VEC3_HPP

#include <array>

class Vec3
{
public:
    /// \brief Default constructor
    /// The (x, y, z) coordinates are set to (0, 0, 0) by default
    constexpr Vec3() noexcept = default;

    /// \brief Constructor. Initialises the vector with parameters x, y, and z
    /// @param x The x-coordinate of the vector
    /// @param y The y-coordinate of the vector
    /// @param z The z-coordinate of the vector
    constexpr Vec3(double const x, double const y, double const z) noexcept : m_vec { x, y, z }
    {
    }

private:
    std::array<double, 3> m_vec {};
};

#endif

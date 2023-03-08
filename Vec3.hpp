#ifndef VEC3_HPP
#define VEC3_HPP

#include <array>
#include <cmath>

#include <gsl/assert>

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

    /// \brief Get the x-coordinate of the vector
    constexpr double x() const& noexcept { return m_vec[0]; }

    /// \brief Get the y-coordinate of the vector
    constexpr double y() const& noexcept { return m_vec[1]; }

    /// \brief Get the z-coordinate of the vector
    constexpr double z() const& noexcept { return m_vec[2]; }

    /// \brief Negate this vector.
    /// \returns A new vector with x, y, and z-coordinates of opposite polarity
    constexpr Vec3 operator-() const& noexcept { return Vec3(-m_vec[0], -m_vec[1], -m_vec[2]); }

    /// \brief Get the vector coordinate at index i
    /// \param i An index into the vector
    /// \returns A copy of the coordinate at index i
    constexpr double operator[](std::size_t const i) const& noexcept 
    {
        Expects(i >= 0 and i <= 2);
        return m_vec[i];
    }

    /// \brief Get the vector coordinate at index i
    /// \param i An index into the vector
    /// \returns A reference to the coordinate at index i
    constexpr double& operator[](std::size_t const i) & noexcept
    {
        Expects(i >= 0 and i <= 2);
        return m_vec[i];
    }

    /// \brief Perform component-wise vector addition
    /// \param v The vector to be added to this vector
    /// \returns This vector with the results of the vector addition as its components
    constexpr Vec3& operator+=(Vec3 const& v) & noexcept
    {
        m_vec[0] += v[0];
        m_vec[1] += v[1];
        m_vec[2] += v[2];

        return *this;
    }

    /// \brief Scale this vector by a factor of t
    /// \param t The scalar with which the vector is multiplied
    /// \returns This vector scaled by a factor of t
    constexpr Vec3& operator*=(double const t) & noexcept
    {
        for (auto& elem : m_vec) {
            elem *= t;
        }

        return *this;
    }

    /// \brief Scale this vector by a factor of 1/t
    /// \param t The scalar with which the vector is multiplied
    /// \returns This vector scaled by a factor of 1/t
    constexpr Vec3& operator/=(double const t) & noexcept
    {
        return *this *= (1 / t);
    }

    /// \brief Get the length of the vector
    double length() const& noexcept
    {
        return std::sqrt(lengthSquared());
    }

    /// \brief Get the dot product of the vector with itself
    constexpr double lengthSquared() const& noexcept
    {
        return (m_vec[0] * m_vec[0]) + (m_vec[1] * m_vec[1]) + (m_vec[2] * m_vec[2]);
    }

private:
    std::array<double, 3> m_vec {};
};

#endif

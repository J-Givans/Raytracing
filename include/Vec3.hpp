#ifndef VEC3_HPP
#define VEC3_HPP

#include <array>
#include <cmath>
#include <ostream>
#include <limits>

#include <gsl/assert>
#include <gsl/util>

namespace rt
{
    class Vec3
    {
    public:
        /// \brief Default constructor
        /// The (x, y, z) coordinates are set to (0, 0, 0) by default
        constexpr Vec3() noexcept = default;

        /// \brief Constructor. Initialises the vector with parameters x, y, and z
        /// \param[in] x The x-coordinate of the vector
        /// \param[in] y The y-coordinate of the vector
        /// \param[in] z The z-coordinate of the vector
        constexpr Vec3(double const x, double const y, double const z) noexcept : m_vec { x, y, z }
        {
        }

        /// \brief Get the x-coordinate of the vector
        [[nodiscard]] constexpr double x() const& noexcept 
        {
            Ensures(m_vec[0] >= std::numeric_limits<double>::lowest() and m_vec[0] <= std::numeric_limits<double>::max()); 
            return m_vec[0]; 
        }

        /// \brief Get the y-coordinate of the vector
        [[nodiscard]] constexpr double y() const& noexcept 
        { 
            Ensures(m_vec[1] >= std::numeric_limits<double>::lowest() and m_vec[1] <= std::numeric_limits<double>::max()); 
            return m_vec[1]; 
        }

        /// \brief Get the z-coordinate of the vector
        [[nodiscard]] constexpr double z() const& noexcept 
        { 
            Ensures(m_vec[2] >= std::numeric_limits<double>::lowest() and m_vec[2] <= std::numeric_limits<double>::max()); 
            return m_vec[2]; 
        }

        /// \brief Negate this vector.
        /// \returns A new vector with x, y, and z-coordinates of opposite polarity
        [[nodiscard]] constexpr Vec3 operator-() const& noexcept 
        {
            auto const v = Vec3(-m_vec[0], -m_vec[1], -m_vec[2]);

            Ensures(v[0] >= std::numeric_limits<double>::lowest() and v[0] <= std::numeric_limits<double>::max());
            Ensures(v[1] >= std::numeric_limits<double>::lowest() and v[1] <= std::numeric_limits<double>::max());
            Ensures(v[2] >= std::numeric_limits<double>::lowest() and v[2] <= std::numeric_limits<double>::max());

            return v;
        }

        /// \brief Get the vector coordinate at index i
        /// \param[in] i An index into the vector
        /// \returns A copy of the coordinate at index i
        [[nodiscard]] constexpr double operator[](gsl::index i) const& noexcept 
        {
            Expects(i >= 0 and i <= 2);
            Ensures(m_vec[i] >= std::numeric_limits<double>::lowest() and m_vec[i] <= std::numeric_limits<double>::max());
            
            return m_vec[i];
        }

        /// \brief Get the vector coordinate at index i
        /// \param[in] i An index into the vector
        /// \returns A reference to the coordinate at index i
        [[nodiscard]] constexpr double& operator[](gsl::index i) & noexcept
        {
            Expects(i >= 0 and i <= 2);
            Ensures(m_vec[i] >= std::numeric_limits<double>::lowest() and m_vec[i] <= std::numeric_limits<double>::max());
            
            return m_vec[i];
        }

        /// \brief Perform component-wise vector addition
        /// \param[in] v The vector to be added to this vector
        /// \returns This vector with the results of the vector addition as its components
        [[nodiscard]] constexpr Vec3& operator+=(Vec3 const& v) & noexcept
        {
            m_vec[0] += v[0];
            m_vec[1] += v[1];
            m_vec[2] += v[2];

            return *this;
        }

        /// \brief Scale this vector by a factor of t
        /// \param[in] t The scalar with which the vector is multiplied
        /// \returns This vector scaled by a factor of t
        constexpr Vec3& operator*=(double const t) & noexcept
        {
            for (auto& elem : m_vec) {
                elem *= t;
            }

            return *this;
        }

        /// \brief Scale this vector by a factor of 1/t
        /// \param[in] t The scalar with which the vector is multiplied
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
        std::array<double, 3> m_vec {0, 0, 0};
    };

    /// \brief Write the contents of the vector @param v to the output stream @param out
    /// This function is not marked @c noexcept because @c std::ostream might throw.
    /// \returns A reference to the output stream @param out
    inline std::ostream& operator<<(std::ostream& out, Vec3 const& v)
    {
        return out << v[0] << ' ' << v[1] << ' ' << v[2];
    }

    /// \brief Create a new vector from the sum of two other vectors
    /// \returns A new vector whose coordinates are the sums of @param u and @param v coordinates
    constexpr Vec3 operator+(Vec3 const& u, Vec3 const& v) noexcept
    {
        return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
    }

    /// \brief Create a new vector from the difference of two other vectors
    /// \returns A new vector whose coordinates are the differences of @param u and @param v coordinates
    constexpr Vec3 operator-(Vec3 const& u, Vec3 const& v) noexcept
    {
        return Vec3(u[0] - v[0],u[1] - v[1], u[2] - v[2]);
    }

    /// \brief Create a new vector from the component-wise products of two other vectors
    /// \returns A new vector whose coordinates are the products of @param u and @param v coordinates
    constexpr Vec3 operator*(Vec3 const& u, Vec3 const& v) noexcept
    {
        return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
    }

    /// \brief Create a new vector from scaling another vector
    /// \returns A new vector which is just @param v scaled by a factor of @param t
    constexpr Vec3 operator*(double const t, Vec3 const& v) noexcept
    {
        return Vec3(t * v[0], t * v[1], t * v[2]);
    }

    /// \brief Create a new vector from scaling another vector
    /// \returns A new vector which is just @param v scaled by a factor of @param t
    constexpr Vec3 operator*(Vec3 const& v, double const t) noexcept
    {
        return t * v;
    }

    /// \brief Create a new vector from scaling another vector
    /// \returns A new vector which is just @param v scaled by a factor of 1 / @param t
    constexpr Vec3 operator/(Vec3 const& v, double const t) noexcept
    {
        return (1 / t) * v;
    }

    /// \brief Get the dot product of the two vectors @param u and @param v
    /// \return The dot (or inner) product of @param u and @param v
    constexpr double dot(Vec3 const& u, Vec3 const& v) noexcept
    {
        return (u[0] * v[0]) + (u[1] * v[1]) + (u[2] * v[2]);
    }

    /// \brief Get the cross product of two vectors
    /// \param[in] u, v The vectors whose cross product is to be computed
    /// \returns The cross product of @param u and @param v
    constexpr Vec3 cross(Vec3 const& u, Vec3 const& v) noexcept
    {
        return Vec3(
            u[1] * v[2] - u[2] * v[1],
            u[2] * v[0] - u[0] * v[2],
            u[0] * v[1] - u[1] * v[0]  
        );
    }

    /// \brief Get the unit vector of a vector
    /// \param[in] v The vector whose unit vector is to be computed
    /// \returns The unit vector of @param[in] v
    Vec3 unitVector(Vec3 const& v) noexcept;
}

#endif

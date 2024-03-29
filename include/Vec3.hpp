#ifndef VEC3_HPP
#define VEC3_HPP

#include <array>
#include <cmath>
#include <ostream>
#include <limits>
#include <algorithm>

#include <gsl/assert>
#include <gsl/util>

#include "Common.hpp"

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

            Ensures(
                std::all_of(m_vec.cbegin(), m_vec.cend(), [](double d) {
                    return d >= std::numeric_limits<double>::lowest() and d <= std::numeric_limits<double>::max();
                })
            );
            
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
        constexpr Vec3& operator+=(Vec3 const& v) & noexcept
        {
            m_vec[0] += v[0];
            m_vec[1] += v[1];
            m_vec[2] += v[2];

            Ensures(
                std::all_of(m_vec.cbegin(), m_vec.cend(), [](double d) {
                    return d >= std::numeric_limits<double>::lowest() and d <= std::numeric_limits<double>::max();
                })
            );

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

            Ensures(
                std::all_of(m_vec.cbegin(), m_vec.cend(), [](double d) {
                    return d >= std::numeric_limits<double>::lowest() and d <= std::numeric_limits<double>::max();
                })
            );

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
            auto const dotProduct = (m_vec[0] * m_vec[0]) + (m_vec[1] * m_vec[1]) + (m_vec[2] * m_vec[2]);
            
            Ensures(dotProduct >= std::numeric_limits<double>::lowest() and dotProduct <= std::numeric_limits<double>::max());

            return dotProduct;
        }

        /// \brief Determine whether the vector is close to zero in all dimensions
        /// \retval true Vector is close to zero in all dimensions
        /// \retval false Otherwise
        constexpr bool isNearZero() const& noexcept
        {
            // Return true if the vector is close to zero in all dimensions
            auto const s = 1e-8;
            return (std::fabs(m_vec[0]) < s) and (std::fabs(m_vec[1]) < s) and (std::fabs(m_vec[2]) < s);
        }

        /// \brief Create a new vector with randomly generated coordinates
        /// \returns A new vector with randomly-generated coordinates
        static Vec3 random();

        /// \brief Create a new vector with randomly-generated coordinates 
        /// \returns A new vector with randomly-generated coordinates
        static Vec3 random(double min, double max);

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
    extern Vec3 unitVector(Vec3 const& v) noexcept;

    inline Vec3 Vec3::random()
    {
        auto const x = randomDouble();
        auto const y = randomDouble();
        auto const z = randomDouble();

        Expects((x >= 0.0 and x < 1.0) and (y >= 0.0 and y < 1.0) and (z >= 0.0 and z < 1.0));

        return Vec3(x, y, z);
    }

    inline Vec3 Vec3::random(double min, double max)
    {
        auto const x = randomDouble(min, max);
        auto const y = randomDouble(min, max);
        auto const z = randomDouble(min, max);

        Expects((x >= min and x < max) and (y >= min and y < max) and (z >= min and z < max));

        return Vec3(x, y, z);
    }

    /// \brief Get a random point in a sphere of unit radius
    /// \details This function repeatedly computes random points and checks whether they lie inside a sphere of unit radius.
    /// If so, it picks this point and immdiately returns it, otherwise it proceeds to the next loop iteration
    /// \returns A point lying inside a sphere of unit radius
    extern Vec3 randomInUnitSphere();

    /// \brief Pick random points in a unit sphere and then normalise them
    /// \returns A normalised point vector
    extern Vec3 randomUnitVector();

    /// \brief Get the reflected ray given the incident ray and the normal
    /// \param[in] incidentRay The ray of incidence
    /// \param[in] normal The normal at the point of intersection
    /// \returns The reflected ray
    constexpr Vec3 getReflectedRay(Vec3 const& incidentRay, Vec3 const& normal)
    {
        return incidentRay - (2 * dot(incidentRay, normal) * normal);
    }

    /// \brief Get the refracted ray given the incident ray, the normal, and the 
    /// ratio of the refractive indices of the media through which light is travelling
    /// \param[in] incidentRay The ray of incidence
    /// \param[in] normal The normal at the point of intersection
    /// \param[in] etaQuotient The ratio between the refractive index of the medium through which the incident ray
    /// is travelling and that of the medium through which the refracted ray is travelling
    /// \returns The refracted ray
    constexpr Vec3 getRefractedRay(Vec3 const& incidentRay, Vec3 const& normal, double etaQuotient)
    {
        auto cosTheta = std::fmin(dot(-incidentRay, normal), 1.0);
        auto refractedPerpendicular = Vec3(etaQuotient * (incidentRay + (cosTheta * normal)));
        auto refractedParallel = Vec3(-std::sqrt(std::fabs(1.0 - refractedPerpendicular.lengthSquared())) * normal);

        return refractedPerpendicular + refractedParallel;
    }

    /// \brief Generate random rays originating from inside a disk centered at a point
    /// \returns A random ray originating from a point
    extern Vec3 randomInUnitDisk();
}

#endif

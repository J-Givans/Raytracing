#ifndef RAY_HPP
#define RAY_HPP

#include "Vec3/Vec3.hpp"

/// \brief 3d point
using Point3 = Vec3;

class Ray
{
public:
    /// \brief Default constructor
    constexpr Ray() noexcept = default;

    /// \brief Construct a ray given its origin and direction of travel
    /// \param[in] origin The origin of the ray
    /// \param[in] direction The direction towards which the ray is travelling
    constexpr Ray(Point3 const& origin, Vec3 const& direction) noexcept
    :   m_origin(origin), m_direction(direction)
    {
    }

    /// \brief Get the origin of this ray
    /// \returns The origin of the ray
    constexpr Point3 getOrigin() const& noexcept { return m_origin; }

    /// \brief Get the direction of this ray
    /// \returns The direction towards which the ray is travelling
    constexpr Vec3 getDirection() const& noexcept { return m_direction; }

    /// \brief Get the point at distance @param t units from the origin
    /// \param[in] t The distance from the origin. 
    ///     Positive values of t give points in front of the origin.
    ///     Negative values give points behind the origin
    /// \returns The point @param t units away from the origin.
    constexpr Point3 at(double const t) const& noexcept
    {
        return m_origin + (t * m_direction);
    }

private:
    Point3 m_origin;
    Vec3 m_direction;
};

#endif
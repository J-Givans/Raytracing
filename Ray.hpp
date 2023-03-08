#ifndef RAY_HPP
#define RAY_HPP

#include "Vec3.hpp"

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

private:
    Point3 m_origin;
    Vec3 m_direction;
};

#endif
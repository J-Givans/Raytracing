#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Hittable.hpp"
#include "Vec3.hpp"

namespace rt
{
    class Sphere : public Hittable
    {
    public:
        /// \brief Default constructor
        Sphere() noexcept = default;

        /// \brief Constructor
        /// \param[in] center The center of the sphere
        /// \param[in] radius The radius of the sphere
        Sphere(Point3 center, double radius) noexcept;

        /// \brief Determine if the ray hit the sphere
        /// \param[in] ray The ray under investigation
        /// \param[in] tMin The minimum t-value acceptable for a hit
        /// \param[in] tMax The maximum t-value acceptable for a hit
        /// \param[in] record 
        /// \returns true if the ray hit the sphere
        /// \returns false otherwise
        bool hit(Ray const& ray, double tMin, double tMax, HitRecord& record) const noexcept override;

    private:
        Point3 m_center {};
        double m_radius {};
    };
}

#endif
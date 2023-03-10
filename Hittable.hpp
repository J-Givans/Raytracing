#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "Vec3.hpp"

struct HitRecord
{
    Point3 point;
    Vec3 normal;
    double t;
    bool frontFace;     // In which direction is the normal pointing towards from the surface?

    /// \brief Set the frontFace and the normal
    /// \param[in] ray The incidence ray
    /// \param[in] outwardNormal The normal at the point of ray-sphere intersection
    constexpr void setFaceNormal(Ray const& ray, Vec3 const& outwardNormal) & noexcept;
};

constexpr void HitRecord::setFaceNormal(Ray const& ray, Vec3 const& outwardNormal) & noexcept
{
    auto const setFrontFace = [&ray, &outwardNormal]() noexcept {
        if (dot(ray.getDirection(), outwardNormal) < 0) {
            return false;
        }

        return true;
    };

    frontFace = setFrontFace();

    normal = frontFace ? outwardNormal : -outwardNormal;
}

class Hittable
{
public:
    virtual ~Hittable() = default;
    
    virtual bool hit(Ray const& ray, double tMin, double tMax, HitRecord& record) const noexcept = 0;
};

#endif
#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "Vec3.hpp"

struct HitRecord
{
    Point3 point;
    Vec3 normal;
    double t;
};

class Hittable
{
public:
    virtual ~Hittable() = default;
    
    virtual bool hit(Ray const& ray, double tMin, double tMax, HitRecord& record) const noexcept = 0;
};

#endif
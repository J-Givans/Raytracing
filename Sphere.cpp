#include "Sphere.hpp"

Sphere::Sphere(Point3 center, double radius) noexcept : m_center(center), m_radius(radius)
{
}

bool Sphere::hit(Ray const& ray, double tMin, double tMax, HitRecord& record) const noexcept
{
    Vec3 oc = ray.getOrigin() - m_center;
    auto a = ray.getDirection().lengthSquared();
    auto b = dot(oc, ray.getDirection());
    auto c = oc.lengthSquared() - (m_radius * m_radius);

    auto discriminant = (b * b) - (a * c);

    if (discriminant < 0) {
        return false;
    }

    auto sqrtDisciriminant = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-b -sqrtDisciriminant) / a;

    if (root < tMin or root > tMax) {
        root = (-b + sqrtDisciriminant) / a;

        if (root < tMin or root > tMax) {
            return false;
        }
    }

    record.t = root;
    record.point = ray.at(record.t);

    Vec3 const outwardNormal = (record.point - m_center) / m_radius;
    record.setFaceNormal(ray, outwardNormal);

    return true;
}
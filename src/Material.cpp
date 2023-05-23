#include "Material.hpp"
#include "Hittable.hpp"
#include "Vec3.hpp"

namespace rt
{
    Lambertian::Lambertian(Colour const& c) : m_albedo(c)
    {
    }

    bool Lambertian::scatter([[maybe_unused]] Ray const& incidentRay, HitRecord const& record, Colour& attenuation, Ray& scattered) const
    {
        auto scatterDirection = record.normal + randomUnitVector();

        // Catch degenerate scatter direction
        if (scatterDirection.isNearZero()) {
            scatterDirection = record.normal;
        }

        scattered = Ray(record.point, scatterDirection);
        attenuation = m_albedo;
        
        return true;
    }
}
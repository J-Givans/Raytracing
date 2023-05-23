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

    Metal::Metal(Colour const& albedo, double fuzziness) noexcept : m_albedo(albedo), m_fuzziness(fuzziness < 1 ? fuzziness : 1)
    {
    }

    bool Metal::scatter(Ray const& incidentRay, HitRecord const& record, Colour& attenuation, Ray& scattered) const
    {
        auto reflectedRay = getReflectedRay(unitVector(incidentRay.getDirection()), record.normal);
        scattered = Ray(record.point, reflectedRay + m_fuzziness * randomInUnitSphere());
        attenuation = m_albedo;

        if (dot(scattered.getDirection(), record.normal) > 0) {
            return true;
        }
        else {
            return false;
        }
    }

    Dielectric::Dielectric(double refractiveIndex) : m_refractiveIndex(refractiveIndex)
    {
    }
}
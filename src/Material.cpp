#include "Material.hpp"
#include "Common.hpp"
#include "Hittable.hpp"
#include "Vec3.hpp"

#include <functional>

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

    bool Dielectric::scatter(Ray const& incidentRay, HitRecord const& record, Colour& attenuation, Ray& scattered) const
    {
        // Attenuation is always 0 because glass surfaces don't absorb any light
        attenuation = Colour(1.0, 1.0, 1.0);
        double const refractionRatio = record.frontFace ? (1.0 / m_refractiveIndex) : m_refractiveIndex;

        Vec3 const unitDirection = unitVector(incidentRay.getDirection());
        double const cosTheta = std::fmin(dot(-unitDirection, record.normal), 1.0);
        double const sinTheta = std::sqrt(1 - std::pow(cosTheta, 2));

        bool const cannotRefract = std::invoke([&refractionRatio, &sinTheta] {
            if (refractionRatio * sinTheta > 1.0) {
                return true;
            }
            else {
                return false;
            }
        });

        Vec3 direction;

        if (cannotRefract or getReflectance(cosTheta, refractionRatio) > randomDouble()) {
            direction = getReflectedRay(unitDirection, record.normal);
        }
        else {
            direction = getRefractedRay(unitDirection, record.normal, refractionRatio);
        }

        scattered = Ray(record.point, direction);

        return true;
    }

    double Dielectric::getReflectance(double cosine, double refractiveIndex)
    {
        // Use Schlick's approximation for reflectance
        auto r_0 = (1 - refractiveIndex) / (1 + refractiveIndex);
        r_0 *= r_0;
        
        return r_0 + (1 - r_0) * std::pow((1 - cosine), 5);
    }
}
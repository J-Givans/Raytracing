#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Common.hpp"

namespace rt 
{
    struct HitRecord;
    class Ray;
    class Colour;

    class Material
    {
    public:
        virtual bool scatter(Ray const& incidentRay, HitRecord const& record, Colour& attenuation, Ray& scattered) const = 0;

        virtual ~Material() = default;
    };
}

#endif
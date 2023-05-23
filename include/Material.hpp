#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Common.hpp"
#include "Colour.hpp"

namespace rt 
{
    struct HitRecord;
    class Ray;

    /// \brief This class describes the type of material that a rendered object is made up of
    /// \details The material represented here does two things:
    /// \details 1. It absorbs an incident ray (and produces a scattered ray)
    /// \details 2. If a scattered ray is produced, it says how much the ray should be attenuated
    class Material
    {
    public:
        /// \brief Determine if a scattered ray is produced from the interaction of an incident ray with an object
        /// \param[in] incidentRay The incoming ray to the object
        /// \param[inout] record A description of ray-object intersections
        /// \param[in] attenuation The degree to which the colour intensity should be reduced
        /// \param[inout] scattered The outward ray
        /// \returns True if a scattered ray was produced, false otherwise
        virtual bool scatter(Ray const& incidentRay, HitRecord const& record, Colour& attenuation, Ray& scattered) const = 0;

        virtual ~Material() = default;
    };
}

#endif
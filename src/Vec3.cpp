#include "Vec3.hpp"

namespace rt
{
    Vec3 unitVector(Vec3 const& v) noexcept
    {
        return v / v.length();
    }

    Vec3 randomInUnitSphere()
    {
        while (true) {
            if (auto point = Vec3::random(-1, 1); point.lengthSquared() >= 1) {
                continue;
            }
            else {
                return point;
            }
        }
    }

    Vec3 randomUnitVector()
    {
        return unitVector(randomInUnitSphere());
    }
}
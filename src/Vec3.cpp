#include "Vec3.hpp"

namespace rt
{
    Vec3 unitVector(Vec3 const& v) noexcept
    {
        return v / v.length();
    }
}
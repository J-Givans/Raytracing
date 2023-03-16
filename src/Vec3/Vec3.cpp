#include "Vec3/Vec3.hpp"

Vec3 unitVector(Vec3 const& v) noexcept
{
    return v / v.length();
}
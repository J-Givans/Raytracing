#include "Ray.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gtest/gtest_pred_impl.h>

using namespace rt;
using namespace ::testing;

[[nodiscard]] 
testing::AssertionResult operator==(Vec3 const& u, Vec3 const& v) noexcept
{
    if (u.x() == v.x() and u.y() == v.y() and u.z() == v.z()) {
        return testing::AssertionSuccess();
    }
    else {
        return testing::AssertionFailure() << " are unequal.";
    }
}

[[nodiscard]]
testing::AssertionResult operator==(Ray const& r, Ray const& t) noexcept
{
    if (r.getOrigin() == t.getOrigin() and r.getDirection() == t.getDirection()) {
        return testing::AssertionSuccess();
    }
    else {
        return testing::AssertionFailure() << " are unequal.";
    }
}

TEST(RayTest, IsPositionedAtOriginWithZeroDirectionVectorByDefault)
{
    constexpr Ray ray;
    
    ASSERT_TRUE(ray.getOrigin() == Vec3(0, 0, 0));
    ASSERT_TRUE(ray.getDirection() == Vec3(0, 0, 0));
}

TEST(RayTest, CanSpecifyOriginAndPositionWhenCreated)
{
    constexpr auto ray = Ray(Point3(0, 0, 0), Vec3(1, 1, 1));

    ASSERT_TRUE(ray.getOrigin() == Point3(0, 0, 0));
    ASSERT_TRUE(ray.getDirection() == Vec3(1, 1, 1));
}
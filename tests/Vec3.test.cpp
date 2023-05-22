#include "Vec3.hpp"

#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;
using rt::Vec3;

TEST(Vec3Test, ContainsZerosByDefault)
{
    Vec3 vector;
    
    for (int i = 0; i < 3; ++i) {
        ASSERT_FLOAT_EQ(vector[i], 0);
    }
}

TEST(Vec3Test, AssigningValuesInConstructorIsSuccessful)
{
    Vec3 vec_;

    auto const vec = Vec3(0, 0, 0);
    
    ASSERT_FLOAT_EQ(vec_[0], vec[0]);
    ASSERT_FLOAT_EQ(vec_[1], vec[1]);
    ASSERT_FLOAT_EQ(vec_[2], vec[2]);
}

TEST(Vec3Test, MethodXReturnsFirstValue)
{
    Vec3 vec_;
    ASSERT_FLOAT_EQ(vec_.x(), vec_[0]);
}

TEST(Vec3Test, MethodYReturnsSecondValue)
{
    Vec3 vec_;
    ASSERT_FLOAT_EQ(vec_.y(), vec_[1]);
}

TEST(Vec3Test, MethodZReturnsLastValue)
{
    Vec3 vec_;
    ASSERT_FLOAT_EQ(vec_.z(), vec_[2]);
}

TEST(Vec3Test, IndexingPastLegalBoundsTerminatesTheProgram)
{
    Vec3 vec_;
    ASSERT_DEATH([[maybe_unused]] auto const val = vec_[-1], "");
    ASSERT_DEATH([[maybe_unused]] auto const val = vec_[4], "");
}

TEST(Vec3Test, VectorNegationResultsInANewVectorWithComponentWiseNegatedElements)
{
    Vec3 vec_;
    auto const vec = -vec_;
    
    ASSERT_FLOAT_EQ(vec[0], -vec_[0]);
    ASSERT_FLOAT_EQ(vec[1], -vec_[1]);
    ASSERT_FLOAT_EQ(vec[2], -vec_[2]);

    constexpr Vec3 vec2(4, 5, 6);
    auto const v2 = -vec2;

    ASSERT_FLOAT_EQ(v2[0], -vec2[0]);
    ASSERT_FLOAT_EQ(v2[1], -vec2[1]);
    ASSERT_FLOAT_EQ(v2[2], -vec2[2]);
}

TEST(Vec3Test, UnaryVectorAdditionAddsElementsComponentWise)
{
    Vec3 vec_;
    auto const v = Vec3(1, 2, 3);
    auto const result = vec_ + v;

    ASSERT_FLOAT_EQ(result[0], vec_[0] + v[0]);
    ASSERT_FLOAT_EQ(result[1], vec_[1] + v[1]);
    ASSERT_FLOAT_EQ(result[2], vec_[2] + v[2]);
}

class VectorTest : public Test
{
public:
    Vec3 vec { 3.14159, 200, 1.143495 };
};

TEST_F(VectorTest, VectorScalingIsAppliedComponentWise)
{
    auto const pre = vec;
    auto& post = vec *= 5;

    ASSERT_FLOAT_EQ(post[0], pre[0] * 5);
    ASSERT_FLOAT_EQ(post[1], pre[1] * 5);
    ASSERT_FLOAT_EQ(post[2], pre[2] * 5);

    post = post / 5;

    ASSERT_FLOAT_EQ(post[0], pre[0]);
    ASSERT_FLOAT_EQ(post[1], pre[1]);
    ASSERT_FLOAT_EQ(post[2], pre[2]);
}

TEST(vec3test, MethodLengthSquaredComputesTheDotProduct)
{
    Vec3 v1(1, 1, 1);
    Vec3 v2(2, 2, 2);

    ASSERT_FLOAT_EQ(v1.lengthSquared(), dot(v1, v1));
    ASSERT_FLOAT_EQ(v2.lengthSquared(), dot(v2, v2));
}

TEST(vec3Test, StaticMethodsCreateVectorsWithRandomCoordinates)
{
    auto v = Vec3::random();

    ASSERT_THAT(v.x() >= 0 and v.x() < 1, Eq(true));
    ASSERT_THAT(v.y() >= 0 and v.y() < 1, Eq(true));
    ASSERT_THAT(v.z() >= 0 and v.z() < 1, Eq(true));

    v = Vec3::random(2, 5);

    ASSERT_THAT(v.x() >= 2 and v.x() < 5, Eq(true));
    ASSERT_THAT(v.y() >= 2 and v.y() < 5, Eq(true));
    ASSERT_THAT(v.z() >= 2 and v.z() < 5, Eq(true));
}
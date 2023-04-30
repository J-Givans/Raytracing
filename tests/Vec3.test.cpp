#include "Vec3.hpp"

#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

class Vec3Test : public Test
{
public:
    rt::Vec3 vec_;
};

TEST_F(Vec3Test, IsAllZerosWhenCreated)
{
    for (int i = 0; i < 3; ++i) {
        ASSERT_FLOAT_EQ(vec_[i], 0);
    }
}

TEST_F(Vec3Test, MethodXReturnsFirstValue)
{
    ASSERT_FLOAT_EQ(vec_.x(), vec_[0]);
}

TEST_F(Vec3Test, MethodYReturnsSecondValue)
{
    ASSERT_FLOAT_EQ(vec_.y(), vec_[1]);
}

TEST_F(Vec3Test, MethodZReturnsLastValue)
{
    ASSERT_FLOAT_EQ(vec_.z(), vec_[2]);
}

TEST_F(Vec3Test, IndexingPastLegalBoundsTerminatesTheProgram)
{
    ASSERT_DEATH([[maybe_unused]] auto const val = vec_[-1], "");
    ASSERT_DEATH([[maybe_unused]] auto const val = vec_[4], "");
}

TEST_F(Vec3Test, AssigningValuesInConstructorIsSuccessful)
{
    auto const vec = rt::Vec3({ 0, 0, 0 });
    
    ASSERT_FLOAT_EQ(vec_[0], vec[0]);
    ASSERT_FLOAT_EQ(vec_[1], vec[1]);
    ASSERT_FLOAT_EQ(vec_[2], vec[2]);
}

TEST_F(Vec3Test, VectorNegationResultsInANewVectorWithComponentWiseNegatedElements)
{
    auto const vec = -vec_;
    
    ASSERT_FLOAT_EQ(vec[0], -vec_[0]);
    ASSERT_FLOAT_EQ(vec[1], -vec_[1]);
    ASSERT_FLOAT_EQ(vec[2], -vec_[2]);

    constexpr rt::Vec3 vec2(4, 5, 6);
    auto const v2 = -vec2;

    ASSERT_FLOAT_EQ(v2[0], -vec2[0]);
    ASSERT_FLOAT_EQ(v2[1], -vec2[1]);
    ASSERT_FLOAT_EQ(v2[2], -vec2[2]);
}

TEST_F(Vec3Test, UnaryVectorAdditionAddsElementsComponentWise)
{
    auto const v = rt::Vec3(1, 2, 3);
    auto const result = vec_ + v;

    ASSERT_FLOAT_EQ(result[0], vec_[0] + v[0]);
    ASSERT_FLOAT_EQ(result[1], vec_[1] + v[1]);
    ASSERT_FLOAT_EQ(result[2], vec_[2] + v[2]);
}
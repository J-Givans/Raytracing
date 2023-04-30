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
    ASSERT_DEATH(vec_[-1], "");
    ASSERT_DEATH(vec_[4], "");
}


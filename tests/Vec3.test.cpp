#include "Vec3.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Vec3Test : public ::testing::Test
{
public:
    rt::Vec3 vec_;
};

TEST_F(Vec3Test, IsAllZerosWhenCreated)
{
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(vec_[i] == 0);
    }
}
#include <gtest/gtest.h>
#include "../src/math.h"

TEST(MathAddTest, PositiveNum) { 
    EXPECT_EQ(2, math::add(1, 1));
    EXPECT_EQ(10, math::add(2, 8));
    EXPECT_EQ(100, math::add(50, 50));
}

TEST(MathAddTest, ZeroB) { 
    EXPECT_EQ(1, math::add(1, 0));
    EXPECT_EQ(10, math::add(10, 0));
    EXPECT_EQ(100, math::add(100, 0));
}

TEST(MathSubTest, PositiveNum) { 
    EXPECT_EQ(0, math::sub(1, 1));
    EXPECT_EQ(-6, math::sub(2, 8));
    EXPECT_EQ(100, math::sub(150, 50));
}

TEST(MathSubTest, ZeroB) { 
    EXPECT_EQ(1, math::sub(1, 0));
    EXPECT_EQ(10, math::sub(10, 0));
    EXPECT_EQ(100, math::sub(100, 0));
}

TEST(MathMulTest, PositiveNum) { 
    EXPECT_EQ(1, math::mul(1, 1));
    EXPECT_EQ(16, math::mul(2, 8));
    EXPECT_EQ(1500, math::mul(150, 10));
}

TEST(MathMulTest, ZeroB) { 
    EXPECT_EQ(0, math::mul(1, 0));
    EXPECT_EQ(0, math::mul(10, 0));
    EXPECT_EQ(0, math::mul(100, 0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

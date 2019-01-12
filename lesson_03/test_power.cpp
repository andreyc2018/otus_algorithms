#include "power.h"
#include <gtest/gtest.h>
#include <functional>

TEST(Power, Init)
{
    // auto sum = [](int a, int b) { return a + b; };
    auto mul = [](int a, int b) { return a * b; };

    EXPECT_EQ(9, power(3, 2, mul));
    EXPECT_EQ(639128961, power(159, 4, mul));
}

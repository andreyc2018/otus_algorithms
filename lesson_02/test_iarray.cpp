#include "IArray.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(BArray, Init)
{
    IArray<int> b;

    EXPECT_EQ(0, b.size());
}

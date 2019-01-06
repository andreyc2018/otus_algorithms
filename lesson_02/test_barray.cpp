#include "BArray.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(BArray, Init)
{
    BArray<int> b;

    EXPECT_EQ(0, b.size());
    EXPECT_EQ(DefaultBlock, b.allocated_size());
}

TEST(BArray, SmallBlock)
{
    BArray<int> b(2);

    EXPECT_EQ(0, b.size());
    EXPECT_EQ(2, b.allocated_size());

    b.add(3, 3);
    EXPECT_EQ(4, b.size());
    EXPECT_EQ(5, b.allocated_size());

    for (int i = 0; i < b.size(); ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    b.add(0, 0);
    EXPECT_EQ(4, b.size());
    EXPECT_EQ(5, b.allocated_size());
}

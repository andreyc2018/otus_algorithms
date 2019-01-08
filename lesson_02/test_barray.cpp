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

    b.add(1, 99);
    EXPECT_EQ(4, b.size());
    EXPECT_EQ(5, b.allocated_size());

    EXPECT_EQ(99, b.get(1));

    for (int i = 0; i < b.allocated_size(); ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    b.set(1, 34);
    EXPECT_EQ(34, b.get(1));

    b.add(7, 107);
    EXPECT_EQ(107, b.get(7));
    EXPECT_EQ(8, b.size());
    EXPECT_EQ(9, b.allocated_size());

}

#include "IArray.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(BArray, Init)
{
    IArray<int> b(3);

    EXPECT_EQ(0, b.size());
}

TEST(BArray, Add)
{
    IArray<int> b(2);

    EXPECT_EQ(0, b.size());

    for (int i = 0; i<10; i++)
        b.add(i, i*i);

    for (int i = 0; i < 5; i++)
        std::cout << b.get(i) << "\n";
}

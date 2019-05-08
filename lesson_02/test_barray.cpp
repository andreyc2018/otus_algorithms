#include "BArray.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(BArray, Init)
{
    BArray<int> b;

    EXPECT_EQ(0, b.size());
    EXPECT_EQ(0, b.allocated_size());
}

TEST(BArray, SmallBlock)
{
    BArray<int> b(2);

    EXPECT_EQ(0, b.size());
    EXPECT_EQ(0, b.allocated_size());

    b.add(3, 3);
    EXPECT_EQ(4, b.size());
    EXPECT_EQ(5, b.allocated_size());

    for (int i = 0; i < b.size(); ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    b.add(0, 567);
    EXPECT_EQ(5, b.size());
    EXPECT_EQ(7, b.allocated_size());

    b.add(1, 99);
    EXPECT_EQ(6, b.size());
    EXPECT_EQ(7, b.allocated_size());

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

TEST(BArray, InsertInMiddle)
{
    BArray<int> b(10);

    for (int i = 1; i <= 5; ++i) {
        b.add(i-1, i*i);
    }

    for (int i = 1; i <= 5; ++i) {
        std::cout << "b[" << i-1 << "] = " << b.get(i-1) << "\n";
        EXPECT_EQ(i*i, b.get(i-1));
    }

    b.add(2, 99);

    for (int i = 0; i < b.size(); ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    EXPECT_EQ(6, b.size());
    EXPECT_EQ(10, b.allocated_size());
    EXPECT_EQ(99, b.get(2));
    EXPECT_EQ(9, b.get(3));
    EXPECT_EQ(16, b.get(4));
    EXPECT_EQ(25, b.get(5));

    b.add(0, 187);
    EXPECT_EQ(187, b.get(0));
    EXPECT_EQ(99, b.get(3));
    EXPECT_EQ(9, b.get(4));
    EXPECT_EQ(16, b.get(5));
    EXPECT_EQ(25, b.get(6));
    EXPECT_EQ(7, b.size());
    EXPECT_EQ(10, b.allocated_size());
}

TEST(BArray, Remove)
{
    BArray<int> b(3);

    // add 1, 4, 9, 16, 25
    for (int i = 1; i <= 5; ++i) {
        b.add(i-1, i*i);
    }

    for (int i = 1; i <= 5; ++i) {
        std::cout << "b[" << i-1 << "] = " << b.get(i-1) << "\n";
        EXPECT_EQ(i*i, b.get(i-1));
    }

    // remove 4
    b.remove(1);
    EXPECT_EQ(9, b.get(1));

    for (int i = 0; i < 5; ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    // remove 1
    b.remove(0);
    EXPECT_EQ(9, b.get(0));

    // remove 25
    int last = b.size()-1;
    b.remove(last);
    EXPECT_EQ(16, b.get(last-1));

    // add 15 and extend an array to 8 elements
    // content: 9, 16, 0, 0, 0, 0, 0, 15
    b.add(7, 15);
    EXPECT_EQ(0, b.get(6));

    for (int i = 0; i < b.size(); ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    EXPECT_EQ(8, b.size());

    // remove all 0 between 16 and 15
    for (int i = b.size()-2; i > 1; i = b.size()-2) {
        b.remove(i);
    }

    EXPECT_EQ(3, b.size());

    for (int i = 0; i < b.size(); ++i) {
        std::cout << "b[" << i << "] = " << b.get(i) << "\n";
    }

    b.remove(-1);
    EXPECT_EQ(3, b.size());
    b.remove(5);
    EXPECT_EQ(3, b.size());
    EXPECT_EQ(9, b.get(0));
    EXPECT_EQ(16, b.get(1));
    EXPECT_EQ(15, b.get(2));
    EXPECT_EQ(0, b.get(5));
}

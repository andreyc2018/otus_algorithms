#include "OList.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(OList, AddRemoveItems)
{
    OList<int> l;

    EXPECT_EQ(0, l.size());
    EXPECT_EQ(0, l.head());
    EXPECT_EQ(0, l.tail());

    for (int i = 0; i < 7; ++i) {
        l.add(i);
    }
    EXPECT_EQ(7, l.size());
    EXPECT_EQ(0, l.head());
    EXPECT_EQ(6, l.tail());

    for (int i = 0; i < 2; ++i) {
        l.pop_head();
        l.pop_tail();
    }
    EXPECT_EQ(3, l.size());
    EXPECT_EQ(2, l.head());
    EXPECT_EQ(4, l.tail());
}

TEST(OList, SingleItem)
{
    OList<int> l;

    EXPECT_EQ(0, l.size());
    EXPECT_EQ(0, l.head());
    EXPECT_EQ(0, l.tail());

    l.add(1);
    EXPECT_EQ(1, l.size());
    EXPECT_EQ(1, l.head());
    EXPECT_EQ(1, l.tail());

    l.pop_head();
    l.pop_tail();
    EXPECT_EQ(0, l.size());
    EXPECT_EQ(0, l.head());
    EXPECT_EQ(0, l.tail());
}

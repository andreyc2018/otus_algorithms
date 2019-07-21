#include "avltree.h"
#include <gtest/gtest.h>

TEST(AvlNode, Init)
{
    hw::AvlNode n(-1);

    std::cout << "v = " << n.value << " h = " << n.height << " b = " << n.balance
              << " l = " << n.left << " r = " << n.right << "\n";
    EXPECT_EQ(-1, n.value);
    EXPECT_EQ(-1, n.height);
    EXPECT_EQ(0, n.balance);
    EXPECT_EQ(nullptr, n.left);
    EXPECT_EQ(nullptr, n.right);

    hw::AvlNode n1;

    std::cout << "v = " << n1.value << " h = " << n1.height << " b = " << n1.balance
              << " l = " << n1.left << " r = " << n1.right << "\n";
    EXPECT_EQ(0, n1.value);
    EXPECT_EQ(-1, n1.height);
    EXPECT_EQ(0, n1.balance);
    EXPECT_EQ(nullptr, n1.left);
    EXPECT_EQ(nullptr, n1.right);
}

TEST(AvlTree, Init)
{
    hw::AvlTree t;
    EXPECT_EQ(-1, t.height());
    EXPECT_EQ(0, t.balance());
    EXPECT_TRUE(t.empty());
}

/*
 * ['J', 'F', 'P', 'D', 'G', 'L', 'V', 'C', 'N', 'S', 'X', 'Q', 'U']
 * [ 74,  70,  80,  68,  71,  76,  86,  67,  78,  83,  88,  81,  85]
 */
TEST(AvlTree, Insert)
{
    hw::AvlTree t;
    t.insert(74);
    EXPECT_EQ(1, t.height());
    EXPECT_EQ(0, t.balance());
    EXPECT_FALSE(t.empty());
}

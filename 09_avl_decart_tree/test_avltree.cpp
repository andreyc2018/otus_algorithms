#include "avltree.h"
#include <gtest/gtest.h>

TEST(AvlNode, Init)
{
    hw::AvlNode n(-1);

    std::cout << "v = " << n.value << " h = " << n.height << " b = " << n.balance
              << " l = " << n.left << " r = " << n.right << "\n";
    EXPECT_EQ(-1, n.value);
    EXPECT_EQ(1, n.height);
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
 *
 * ['C', 'D', 'F', 'G', 'J', 'L', 'N', 'P', 'Q', 'S', 'U', 'V', 'X']
 * [ 67,  68,  70,  71,  74,  76,  78,  80,  81,  83,  85,  86,  88]
 */
TEST(AvlTree, Insert)
{
    hw::AvlTree t;
    t.insert(67);
    EXPECT_EQ(1, t.height());
    EXPECT_EQ(0, t.balance());
    EXPECT_FALSE(t.empty());

    t.insert(68);
    EXPECT_EQ(2, t.height());
    EXPECT_EQ(1, t.balance());
    auto l = t.root()->left;
    auto r = t.root()->right;
    EXPECT_EQ(1, r->height);
    EXPECT_EQ(0, r->balance);
    EXPECT_EQ(nullptr, l);

    t.insert(70);
    EXPECT_EQ(3, t.height());
    EXPECT_EQ(2, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(2, r->height);
    EXPECT_EQ(1, r->balance);
    EXPECT_EQ(nullptr, l);

    /*
    t.insert(70);
    EXPECT_EQ(2, t.height());
    EXPECT_EQ(0, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(1, l->height);
    EXPECT_EQ(0, l->balance);
    EXPECT_EQ(1, r->height);
    EXPECT_EQ(0, r->balance);

    t.insert(71);
    EXPECT_EQ(3, t.height());
    EXPECT_EQ(-1, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(2, l->height);
    EXPECT_EQ(-1, l->balance);
    EXPECT_EQ(1, r->height);
    EXPECT_EQ(0, r->balance);

    t.insert(74);
    EXPECT_EQ(3, t.height());
    EXPECT_EQ(-1, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(2, l->height);
    EXPECT_EQ(0, l->balance);
    EXPECT_EQ(1, r->height);
    EXPECT_EQ(0, r->balance);

    t.insert(76);
    EXPECT_EQ(3, t.height());
    EXPECT_EQ(0, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(2, l->height);
    EXPECT_EQ(0, l->balance);
    EXPECT_EQ(2, r->height);
    EXPECT_EQ(-1, r->balance);

    t.insert(78);
    EXPECT_EQ(3, t.height());
    EXPECT_EQ(0, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(2, l->height);
    EXPECT_EQ(0, l->balance);
    EXPECT_EQ(2, r->height);
    EXPECT_EQ(0, r->balance);

    t.insert(80);
    EXPECT_EQ(4, t.height());
    EXPECT_EQ(-1, t.balance());
    l = t.root()->left;
    r = t.root()->right;
    EXPECT_EQ(3, l->height);
    EXPECT_EQ(-1, l->balance);
    EXPECT_EQ(2, r->height);
    EXPECT_EQ(0, r->balance);
*/
}

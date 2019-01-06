#include "PriorityQueue.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(PriorityQueue, Init)
{
    PriorityQueue<int> pq;

    std::cout << pq.size() << "\n";

    EXPECT_EQ(0, pq.size());
}
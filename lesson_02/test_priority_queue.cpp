#include "PriorityQueue.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(PriorityQueue, Init)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());
}

TEST(PriorityQueue, Enqueue)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());

    pq.enqueue();
}
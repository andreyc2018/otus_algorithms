#include "PriorityQueue.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(PriorityQueue, Init)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());
    EXPECT_EQ(0, pq.dequeue());
}

TEST(PriorityQueue, Enqueue)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());

    for (int i = 0; i < 7; ++i) {
        pq.enqueue(1, i);
    }
    EXPECT_EQ(1, pq.highest());
    EXPECT_EQ(7, pq.size());

    for (int i = 0; i < 12; ++i) {
        pq.enqueue(i, i*i);
    }
    EXPECT_EQ(11, pq.highest());
    EXPECT_EQ(19, pq.size());
}

TEST(PriorityQueue, EnqueueDequeue)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());

    for (int i = 0; i < 7; ++i) {
        pq.enqueue(1, i);
    }
    EXPECT_EQ(1, pq.highest());
    EXPECT_EQ(7, pq.size());

    for (int i = 0; i < 5; ++i) {
        int v = pq.dequeue();
        EXPECT_EQ(i, v);
    }

    EXPECT_EQ(2, pq.size());
}

TEST(PriorityQueue, InvertPriorityEnqueueDequeue)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());

    for (int i = 0, p = 10; i < 7; ++i, --p) {
        pq.enqueue(p, i);
    }
    EXPECT_EQ(10, pq.highest());
    EXPECT_EQ(7, pq.size());

    for (int i = 0; i < 5; ++i) {
        int v = pq.dequeue();
        EXPECT_EQ(i, v);
    }

    EXPECT_EQ(2, pq.size());
}

TEST(PriorityQueue, PriorityEnqueueDequeue)
{
    PriorityQueue<int> pq;
    EXPECT_EQ(0, pq.size());

    for (int i = 0, p = 0; i < 7; ++i, ++p) {
        pq.enqueue(p, i);
    }
    EXPECT_EQ(6, pq.highest());
    EXPECT_EQ(7, pq.size());

    for (int i = 6; i >= 0; --i) {
        int v = pq.dequeue();
        EXPECT_EQ(i, v);
    }

    EXPECT_EQ(0, pq.size());

    pq.enqueue(1, 99);
    pq.enqueue(10, 2);
    pq.enqueue(139, 1);
    EXPECT_EQ(3, pq.size());
    EXPECT_EQ(1, pq.dequeue());
    EXPECT_EQ(2, pq.dequeue());
    EXPECT_EQ(99, pq.dequeue());
    EXPECT_EQ(139, pq.highest());
}

TEST(PriorityQueue, SingleEnqueueDequeue)
{
    PriorityQueue<int> pq;
    pq.enqueue(1, 1);
    pq.dequeue();
}

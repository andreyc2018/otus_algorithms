#pragma once

#include <stddef.h>

template<typename T>
class Queue
{
    public:
        void enqueue(int priority, T item)
        {

        }

        T dequeue()
        {

        }

    private:
        T* 
};

template<typename T>
class PriorityQueue
{
    public:
        PriorityQueue(int max_priorities)
            : max_priorities_(max_priorities)
        {

        }

        void enqueue(int priority, T item)
        {

        }

        T dequeue()
        {

        }

        size_t size()
        {
            return -1;
        }

    private:
        int max_priorities_;
};

#pragma once

#include <cmath>
#include <algorithm>

template <typename T>
T parent(T i)
{
    return static_cast<T>(std::floor((i - 1) / 2));
}

template <typename T>
T left(T i)
{
    return i * 2 + 1;
}

template <typename T>
T right(T i)
{
    return i * 2 + 2;
}

template <typename H, typename I>
void swap(H& heap, I i, I largest)
{
//    std::swap(heap[i], heap[largest]);
    auto tmp = heap[i];
    heap[i] = heap[largest];
    heap[largest] = tmp;
}

template <typename H, typename I>
void drown(H& heap, I i, I size)
{
    auto l = left(i);
    auto r = right(i);

    I largest;
    if (l <= size && heap[l] > heap[r]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r <= size && heap[r] > heap[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(heap, i, largest);
        drown(heap, largest, size);
    }
}

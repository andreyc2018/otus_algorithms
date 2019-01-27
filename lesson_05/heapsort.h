#pragma once

#include <cmath>
#include <iostream>
//#include <algorithm>

namespace details {

template <typename T>
T parent(T i) { return static_cast<T>(std::floor((i - 1) / 2)); }

template <typename T>
T left(T i) { return i * 2 + 1; }

template <typename T>
T right(T i) { return i * 2 + 2; }

template <typename T>
T floor_half(T size) { return parent(size); }

template <typename H, typename I>
void swap(H& heap, I i, I largest)
{
//    std::swap(heap[i], heap[largest]);
    auto tmp = heap[i];
    heap[i] = heap[largest];
    heap[largest] = tmp;
}

template <typename T>
void print_array(T& array, const std::string& msg)
{
    std::cout << msg;
    for (const auto& i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}
}

template <typename H, typename I>
void drown(H& heap, I i, I size)
{
    auto l = details::left(i);
    auto r = details::right(i);

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
        details::swap(heap, i, largest);
        drown(heap, largest, size);
    }
}

template <typename T>
void build_heap(T& array)
{
    for (ssize_t i = details::floor_half(array.size()); i >= 0; --i) {
        drown(array, i, array.size());
    }
}

template <typename T>
void heapsort(T& array)
{
    details::print_array(array, "initial\n");
    using size_type = typename T::size_type;
    auto size = array.size();
    build_heap(array);
    details::print_array(array, "after build_heap\n");
    for (auto i = size - 1; i >= 1; --i) {
        --size;
        details::swap(array, static_cast<size_type>(0), i);
        details::print_array(array, "after swap\n");
        drown(array, static_cast<size_type>(0), size);
        details::print_array(array, "after drown\n");
    }
}

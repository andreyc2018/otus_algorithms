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

}

template<typename T>
void print_array(const T& array, const std::string& msg = "")
{
    if (!msg.empty()) {
        std::cout << msg;
    }
    for (const auto& i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

namespace otus {

template <typename H, typename I>
void drown(H& heap, I i, I last)
{
//    std::cout << i << ", " << last << ": ";
//    print_array(heap);
    auto l = details::left(i);
    auto r = details::right(i);

    I largest = i;
    if (l <= last && heap[l] > heap[largest]) {
        largest = l;
    }

    if (r <= last && heap[r] > heap[largest]) {
        largest = r;
    }

    if (largest != i) {
        details::swap(heap, i, largest);
        drown(heap, largest, last);
    }
}

template <typename T>
void build_heap(T& array)
{
    using idx_t = typename T::difference_type;
    idx_t last = array.size() - 1;
    for (idx_t i = details::floor_half(array.size()); i >= 0; --i) {
        drown(array, i, last);
    }
}

template <typename T>
void heapsort(T& array)
{
//    print_array(array, "initial\n");
    using idx_t = typename T::difference_type;
    idx_t first = 0;
    idx_t last = array.size()-1;
    build_heap(array);
//    print_array(array, "after build_heap\n");
    for (auto i = last; i > 0; --i) {
        --last;
        details::swap(array, first, i);
//        print_array(array, "after swap\n");
        drown(array, first, last);
//        print_array(array, "after drown\n");
    }
}
}

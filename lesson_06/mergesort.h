#pragma once

#include <iterator>
#include <iostream>

namespace otus {

template <typename T>
void debug_print(const T& array)
{
    for (const auto& v : array) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

template <typename T, typename S = typename T::size_type>
void debug_print(T& array, S b, S e, const std::string& msg)
{
    std::cout << msg << " " << b << ":" << e << " - ";
    for (auto i = b; i < e; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

template <typename T, typename S = typename T::size_type>
void merge(T& copy, S b, S m, S e, T& array)
{
    debug_print(array, b, m, "merge array b m");
    debug_print(array, m, e, "merge array m e");
    debug_print(copy, b, m, "merge copy b m");
    debug_print(copy, m, e, "merge copy m e");
    auto f = b;
    auto s = m;
    for (auto i = b; i < e; ++i) {
        if (f < m && (s >= e || array[f] <= array[s])) {
            copy[i] = array[f];
            ++f;
        } else {
            copy[i] = array[s];
        }
    }
    debug_print(array, b, e, "after merge array");
    debug_print(copy, b, e, "after merge copy");
}

template <typename T, typename S = typename T::size_type>
void split_merge(T& copy, S b, S e, T& array)
{
    if (e - b < 2) {
        return;
    }

    auto m = (e + b) / 2;
    split_merge(array, b, m, copy);
    split_merge(array, m, e, copy);
    merge(copy, b, m, e, array);
}

template <typename T>
void merge_sort(T& array)
{
    if (array.size() < 2) {
        return;
    }
    T copy(array);

    debug_print(array);
    debug_print(copy);
    split_merge(copy, 0ul, array.size(), array);
    debug_print(array);
    debug_print(copy);
}

}

#pragma once

#include <iterator>
#include <future>
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
    auto f = b;
    auto s = m;
    for (auto i = b; i < e; ++i) {
        if (f < m && (s >= e || array[f] <= array[s])) {
            copy[i] = array[f];
            ++f;
        } else {
            copy[i] = array[s];
            ++s;
        }
    }
}

template <typename T, typename S = typename T::size_type>
void split_merge(T& copy, S b, S e, T& array, unsigned int fork_join_limit)
{
    if (e - b < 2) {
        return;
    }

    auto m = (e + b) / 2;
    if (fork_join_limit > 0 && m - b >= fork_join_limit) {
        auto handle = std::async(std::launch::async,
                                 split_merge<T>, std::ref(array), b, m, std::ref(copy),
                                 fork_join_limit);
        handle.wait();
    } else {
        split_merge(array, b, m, copy, fork_join_limit);
    }
    split_merge(array, m, e, copy, fork_join_limit);
    merge(copy, b, m, e, array);
}

template <typename T>
void merge_sort(T& array, unsigned int fork_join_limit = 1000)
{
    if (array.size() < 2) {
        return;
    }
    T copy(array);

    split_merge(array, 0ul, array.size(), copy, fork_join_limit);
}

}

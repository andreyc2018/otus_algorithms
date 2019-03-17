#pragma once
#include <iostream>
#include <test_tools.h>

namespace otus {

template <typename T>
void count_sort(T& array, typename T::value_type k, typename T::value_type idx)
{
    using element_t = decltype (k);
    T count (k, 0);

//    std::cout << "\t";
//    test_tools::debug_print(std::cout, count);

    for (const auto& item : array) {
        count[(item/idx)%k] ++;
    }

//    std::cout << "\t";
//    test_tools::debug_print(std::cout, count);

    for (element_t i = 1; i <= k; ++i) {
        count[i] += count[i-1];
    }

//    std::cout << "\t";
//    test_tools::debug_print(std::cout, count);

    T sorted(array.size());

    std::for_each(std::rbegin(array), std::rend(array), [&sorted, &count, &k, &idx](const element_t& item) {
        auto i = (item/idx)%k;
        count[i] -= 1;
        sorted[count[i]] = item;
    });

//    std::cout << "\t";
//    test_tools::debug_print(std::cout, sorted);

    std::copy(std::begin(sorted), std::end(sorted), std::begin(array));
}

template <typename T>
void radix_sort(T& array, typename T::value_type k)
{
//    std::cout << "k = " << k << "\n";
    for (int i = 1; i <= k; i *= 10) {
//        std::cout << "i = " << i << "\n\t";
//        test_tools::debug_print(std::cout, array);
        count_sort(array, 10, i);
    }
}

}

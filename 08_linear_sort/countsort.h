#pragma once

#include <test_tools.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

namespace otus {
namespace original {

template <typename T>
void count_sort(T& array, typename T::value_type k)
{
    using element_t = decltype (k);
    T count (k+1, 0);

//    test_tools::debug_print(std::cout, count);

    for (const auto& i : array) {
        count[i] ++;
    }

//    test_tools::debug_print(std::cout, count);

    for (element_t i = 1; i <= k; ++i) {
        count[i] += count[i-1];
    }

//    test_tools::debug_print(std::cout, count);

    T sorted(array.size());

//    test_tools::debug_print(std::cout, sorted);

    std::for_each(std::rbegin(array), std::rend(array), [&sorted, &count](const element_t& item) {
        count[item] -= 1;
        sorted[count[item]] = item;
    });

//    test_tools::debug_print(std::cout, sorted);

    std::copy(std::begin(sorted), std::end(sorted), std::begin(array));
}

}
/**
 * Vector Of Structs
 */
namespace vos {
/**
 * @brief count_sort_vos - Count sort using vector of structs
 * @param array - array to sort
 * @param k - max element in te array
 */
template <typename T>
void count_sort(T& array, typename T::value_type k)
{
    using element_t = decltype (k);
    struct CounterValue
    {
        CounterValue(element_t v, element_t c) : value(v), count(c) {}
        element_t value = 0;
        element_t count = 0;
    };

    using counter_t = std::vector<CounterValue>;
    counter_t counter;
    counter.reserve(k + 1);
    for (element_t i = 0; i <= k; ++i) {
        counter.emplace_back(i, 0);
    }

    for (const auto& i : array) {
        counter[i].count ++;
    }

    element_t counter_pointer = 0;
    element_t array_pointer = 0;

    while (counter_pointer <= k) {
        if (counter[counter_pointer].count == 0) {
            counter_pointer += 1;
        } else {
            counter[counter_pointer].count -= 1;
            array[array_pointer] = counter[counter_pointer].value;
            array_pointer ++;
        }
    }
}

}

/**
 * Struct Of Vectors
 */
namespace sov {
/**
 * @brief count_sort_vos - Count sort using struct of vectors
 * @param array - array to sort
 * @param k - max element in te array
 */
template <typename T>
void count_sort(T& array, typename T::value_type k)
{
    using element_t = decltype (k);
    struct CounterValue
    {
        CounterValue(element_t k) : value(k+1), count(k+1, 0) {
            std::iota(std::begin(value), std::end(value), 0);
        }

        std::vector<element_t> value;
        std::vector<element_t> count;
    };

    using counter_t = CounterValue;
    counter_t counter(k);

    std::for_each(std::begin(array), std::end(array), [&counter](const element_t& i) {
        counter.count[i]++;
    });

    element_t counter_pointer = 0;
    element_t array_pointer = 0;

    while (counter_pointer <= k) {
        if (counter.count[counter_pointer] == 0) {
            counter_pointer += 1;
        } else {
            counter.count[counter_pointer] -= 1;
            array[array_pointer] = counter.value[counter_pointer];
            array_pointer ++;
        }
    }
}
}

}

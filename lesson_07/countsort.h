#pragma once

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

namespace otus {
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

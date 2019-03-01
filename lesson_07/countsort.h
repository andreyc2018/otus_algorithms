#pragma once

#include <vector>
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

//    for (const auto& i : counter) {
//        std::cout << "value = " << i.value << ", count = " << i.count << "\n";
//    }

    for (const auto& i : array) {
        counter[i].count ++;
//        std::cout << "counter[" << i << "] = " << counter[i].count << "\n";
    }

    int j = 0;
    for (const auto& i : counter) {
        std::cout << "j = " << j << " value = " << i.value << ", count = " << i.count << "\n";
        ++j;
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
        CounterValue() = default;
        CounterValue(element_t k) { value.reserve(k), count.reserve(k); }
        void push_back(element_t v, element_t c) {
            value.push_back(v);
            count.push_back(c);
        }

        element_t& operator[](element_t& i) {
            return count[i];
        }

        std::vector<element_t> value;
        std::vector<element_t> count;
    };

    using counter_t = CounterValue;
    counter_t counter;
    for (element_t i = 0; i <= k; ++i) {
        counter.push_back(i, 0);
    }

    for (auto& i : array) {
        counter[i] ++;
//        std::cout << i << " : " << counter.value[i] << " : " << counter.count[i] << "\n";
    }

    for (element_t i = 0; i <= k; ++i) {
        std::cout << "i = " << i << " value = " << counter.value[i] << ", count = " << counter.count[i] << "\n";
    }

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

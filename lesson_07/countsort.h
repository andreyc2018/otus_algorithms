#pragma once

#include <vector>
#include <iostream>

namespace otus {

struct CounterValue
{
    size_t value = 0;
    size_t counter = 0;
};

template <typename T>
void count_sort(T& array, typename T::value_type k)
{
    using counter_t = std::vector<CounterValue>;
    counter_t counter;
    counter.reserve(k + 1);
    for (decltype (k) i = 0; i <= k; ++i) {
        counter.emplace_back();
    }

    for (const auto& i : counter) {
        std::cout << "counter[" << i.first << "] = " << i.second << "\n";
    }

    for (const auto& i : array) {
        ++counter[i];
    }

    for (const auto& i : counter) {
        std::cout << "counter[" << i.first << "] = " << i.second << "\n";
    }

    size_t counter_pointer = 0;
    size_t array_pointer = 0;

    while (counter_pointer < k) {
        if (counter[counter_pointer] == 0) {
            counter_pointer += 1;
        } else {
            counter[counter_pointer] -= 1;
            array[array_pointer];
        }
    }
}

}

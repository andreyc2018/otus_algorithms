#include "radixsort.h"
#include <test_tools.h>
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

static constexpr size_t ArraySize = 150000;

TEST(RadixSort, PrintDigits)
{
    std::vector<int> array { 301, 4987, 23, 1 };
    auto k = *(std::max_element(std::begin(array), std::end(array)));

    for (int i = 1; i <= k; i *= 10) {
        std::cout << "i = " << i << "\n";
        for (const auto& a : array) {
            std::cout << "\t" << a << " => " << (a/i)%10 << "\n";
        }
    }
    otus::count::radix_sort(array, k);
}

TEST(RadixSort, Unsorted_Short)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, 5, 1000);
    test_tools::debug_print(std::cout, array);
    test_tools::debug_print(std::cout, expected_array);

    auto k = expected_array.back();
    otus::count::radix_sort(array, k);
    test_tools::debug_print(std::cout, array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(RadixSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, ArraySize, 10000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::count::radix_sort(array, k); }, "Unsorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(RadixSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, ArraySize, 10000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::count::radix_sort(array, k); }, "Sorted:            ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(RadixSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, ArraySize, 10000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::count::radix_sort(array, k); }, "Reversed:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(Trie, CanCreateEmptyTrie)
{
    otus::trie::RadixTrie<int> t;
    size_t expected = 0;
    EXPECT_EQ(expected, t.size());
}

TEST(Trie, CanAddElements)
{
    otus::trie::RadixTrie<int> t;
    t.add(321);
    size_t expected = 1;
    EXPECT_EQ(expected, t.size());
}

TEST(RadixSort, Trie_Unsorted_Short)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, 5, 10);
    test_tools::debug_print(std::cout, array);
    test_tools::debug_print(std::cout, expected_array);

    auto k = expected_array.back();
    otus::trie::radix_sort(array, k);
    test_tools::debug_print(std::cout, array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

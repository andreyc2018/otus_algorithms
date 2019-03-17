#include "countsort.h"
#include <test_tools.h>
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

static constexpr size_t ArraySize = 1500000;

TEST(CountSort, Unsorted_Short_Original)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, 15, 10);
    test_tools::debug_print(std::cout, array);
    test_tools::debug_print(std::cout, expected_array);

    auto k = expected_array.back();
    otus::original::count_sort(array, k);
    test_tools::debug_print(std::cout, array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Unsorted_Short_Vos)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, 15, 10);
    test_tools::debug_print(std::cout, array);
    test_tools::debug_print(std::cout, expected_array);

    auto k = expected_array.back();
    otus::vos::count_sort(array, k);
    test_tools::debug_print(std::cout, array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Unsorted_Short_Sov)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, 15, 10);
    test_tools::debug_print(std::cout, array);
    test_tools::debug_print(std::cout, expected_array);

    auto k = expected_array.back();
    otus::sov::count_sort(array, k);
    test_tools::debug_print(std::cout, array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Unsorted_Original)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::original::count_sort(array, k); }, "Unsorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Unsorted_Vos)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::vos::count_sort(array, k); }, "Unsorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Unsorted_Sov)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::sov::count_sort(array, k); }, "Unsorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Sorted_Original)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::original::count_sort(array, k); }, "Sorted:            ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Sorted_Vos)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::vos::count_sort(array, k); }, "Sorted:            ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Sorted_Sov)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::sov::count_sort(array, k); }, "Sorted:            ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Reversed_Original)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::original::count_sort(array, k); }, "Reversed:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Reversed_Vos)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::vos::count_sort(array, k); }, "Reversed:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

TEST(CountSort, Reversed_Sov)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::sov::count_sort(array, k); }, "Reversed:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    size_t expected = 0;
    EXPECT_EQ(expected, diff.size());
}

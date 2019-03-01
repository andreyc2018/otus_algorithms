#include "countsort.h"
#include <test_tools.h>
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

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
    EXPECT_EQ(0, diff.size());
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
    EXPECT_EQ(0, diff.size());
}

TEST(CountSort, Unsorted_Vos)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, test_tools::ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::vos::count_sort(array, k); }, "Unsorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(CountSort, Unsorted_Sov)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, test_tools::ArraySize, 1000000);

    auto k = expected_array.back();
    test_tools::timed_run(std::cout,
                          [&array, k]() { otus::sov::count_sort(array, k); }, "Unsorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

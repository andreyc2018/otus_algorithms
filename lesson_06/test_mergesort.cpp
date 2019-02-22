#include "mergesort.h"

#include <test_tools.h>
#include <gtest/gtest.h>

TEST(MergeSort, Unsorted_Short)
{
    using array_t = std::vector<int>;
    array_t array { 3, 7, 1, 4, 5 };
    otus::merge_sort(array);
}

TEST(MergeSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, test_tools::ArraySize);

    test_tools::timed_run(std::cout,
                          [&array]() { otus::merge_sort(array); }, "Unsorted:        ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(MergeSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, test_tools::ArraySize, 3000);

    test_tools::timed_run(std::cout, [&array]() { otus::merge_sort(array); }, "Sorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(MergeSort, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_partially_sorted_array(array, expected_array, test_tools::ArraySize, 2000);

    test_tools::timed_run(std::cout, [&array]() { otus::merge_sort(array); }, "Partially sorted:");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(MergeSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, test_tools::ArraySize, 5050);

    test_tools::timed_run(std::cout, [&array]() { otus::merge_sort(array); }, "Reversed:        ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

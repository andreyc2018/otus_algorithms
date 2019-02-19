#include "heapsort.h"
#include <test_tools.h>
#include <gtest/gtest.h>

TEST(HeapSort, BuildHeap)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, test_tools::ArraySize, 1);

    std::make_heap(std::begin(expected_array), std::end(expected_array));

    otus::build_heap(array);
    otus::build_heap(array);
    otus::build_heap(array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, test_tools::ArraySize);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort(array); }, "Unsorted:        ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, test_tools::ArraySize, 3000);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort(array); }, "Sorted:          ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_partially_sorted_array(array, expected_array, test_tools::ArraySize, 2000);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort(array); }, "Partially sorted:");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, test_tools::ArraySize, 5050);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort(array); }, "Reversed:        ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, BuildHeap)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, test_tools::ArraySize, 1);

    std::make_heap(std::begin(expected_array), std::end(expected_array));

    otus::build_heap_loop(array);
    otus::build_heap_loop(array);
    otus::build_heap_loop(array);

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, test_tools::ArraySize);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort_loop(array); }, "Unsorted:         ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_sorted_array(array, expected_array, test_tools::ArraySize, 3000);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort_loop(array); }, "Sorted:           ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_partially_sorted_array(array, expected_array, test_tools::ArraySize, 2000);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort_loop(array); }, "Partially sorted:");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_reversed_array(array, expected_array, test_tools::ArraySize, 5050);

    test_tools::timed_run(std::cout, [&array]() { otus::heapsort_loop(array); }, "Reversed:        ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

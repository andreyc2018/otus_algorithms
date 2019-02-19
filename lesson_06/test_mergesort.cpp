#include "mergesort.h"

#include <test_tools.h>
#include <gtest/gtest.h>

TEST(MergeSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    test_tools::create_random_array(array, expected_array, 9/*test_tools::ArraySize*/);

    test_tools::timed_run(std::cout, [&array]() { otus::merge_sort(array); }, "Unsorted:        ");

    std::vector<int> diff;
    test_tools::diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

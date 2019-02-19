#include "mergesort.h"

#include <test_tools.h>
#include <gtest/gtest.h>

TEST(MergeSort, Merge)
{
    using array_t = std::vector<int>;
    array_t array { 3, 7, 1, 4, 5 };
    auto l = std::begin(array);
    auto r = std::next(l, 2);
    otus::view_range<array_t> left(array, l, r);
    otus::view_range<array_t> right(array, r, std::end(array));
    otus::merge(left, right);
}

//TEST(MergeSort, Unsorted)
//{
//    std::vector<int> array          /*{3, 5, 2, 1, 7, 4, 6, 9, 8}*/;
//    std::vector<int> expected_array /*{1, 2, 3, 4, 5, 6, 7, 8, 9}*/;
//    test_tools::create_random_array(array, expected_array, 9/*test_tools::ArraySize*/);

//    test_tools::timed_run(std::cout,
//                          [&array]() { otus::merge_sort(array); }, "Unsorted:        ");

//    std::vector<int> diff;
//    test_tools::diff_arrays(array, expected_array, diff);
//    EXPECT_EQ(0, diff.size());
//}

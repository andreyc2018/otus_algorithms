#include "insertion_sort.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <gtest/gtest.h>

std::random_device rd;
std::mt19937 rng(rd());

TEST(InsertionSort, Unsorted)
{
    std::vector<int> array;
    std::generate_n(std::back_inserter(array), 100, std::ref(rng)); 
    std::vector<int> expected_array = array;
    std::sort(expected_array.begin(), expected_array.end());
    // std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\n";
    
    // std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\n";

    insertion_sort(array);

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(), 
                        expected_array.begin(), expected_array.end(), 
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());


    // std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\n";
}
#include "sort_algorithms.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <gtest/gtest.h>

namespace {
std::random_device rd;
std::mt19937 rng(rd());
}

constexpr size_t InsertArraySize = 10000;
constexpr size_t ArraySize = 50000;

TEST(InsertionSort, Unsorted)
{
    std::vector<int> array;
    std::generate_n(std::back_inserter(array), InsertArraySize, std::ref(rng));

    std::vector<int> expected_array = array;
    std::sort(expected_array.begin(), expected_array.end());

    insertion_sort(array);

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(), 
                        expected_array.begin(), expected_array.end(), 
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, Sorted)
{
    std::vector<int> array(InsertArraySize);
    std::iota(array.begin(), array.end(), 100000);
    std::vector<int> expected_array = array;

    insertion_sort(array);

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(), 
                        expected_array.begin(), expected_array.end(), 
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, PartiallySorted)
{
    std::vector<int> array(InsertArraySize);
    std::iota(array.begin(), array.end(), 100000);
    std::vector<int> expected_array = array;

    // std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\n";

    auto from = std::next(std::begin(array), 1000);
    auto to = std::next(from, 200);
    // std::cout << "from = " << *from << "\n";
    // std::cout << "to   = " << *to << "\n";
    std::shuffle(from, to, rng);

    // std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\n";
    
    insertion_sort(array);

    // std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << "\n";

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(), 
                        expected_array.begin(), expected_array.end(), 
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, Reversed)
{
    std::vector<int> array(InsertArraySize);
    std::iota(array.begin(), array.end(), 100000);
    std::vector<int> expected_array = array;
    
    std::reverse(array.begin(), array.end());

    insertion_sort(array);

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(), 
                        expected_array.begin(), expected_array.end(), 
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

size_t knuth_interval(size_t size)
{
    size_t interval = 1;

    /* calculate interval*/
    while (interval < size/3) {
        interval = interval * 3 + 1;
    }
    return interval;
}

TEST(ShellSort, Unsorted)
{
    std::vector<int> array;
    std::generate_n(std::back_inserter(array), ArraySize, std::ref(rng));

    std::vector<int> expected_array = array;
    std::sort(expected_array.begin(), expected_array.end());

    shell_sort(array, knuth_interval(array.size()));

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(),
                        expected_array.begin(), expected_array.end(),
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, Sorted)
{
    std::vector<int> array(ArraySize);
    std::iota(array.begin(), array.end(), 100000);
    std::vector<int> expected_array = array;

    shell_sort(array, knuth_interval(array.size()));

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(),
                        expected_array.begin(), expected_array.end(),
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, PartiallySorted)
{
    std::vector<int> array(ArraySize);
    std::iota(array.begin(), array.end(), 100000);
    std::vector<int> expected_array = array;

    auto from = std::next(std::begin(array), 1000);
    auto to = std::next(from, 200);
    std::shuffle(from, to, rng);

    shell_sort(array, knuth_interval(array.size()));

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(),
                        expected_array.begin(), expected_array.end(),
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, Reversed)
{
    std::vector<int> array(ArraySize);
    std::iota(array.begin(), array.end(), 100000);
    std::vector<int> expected_array = array;

    std::reverse(array.begin(), array.end());

    shell_sort(array, knuth_interval(array.size()));

    std::vector<int> diff;
    std::set_difference(array.begin(), array.end(),
                        expected_array.begin(), expected_array.end(),
                        std::inserter(diff, diff.begin()));
    EXPECT_EQ(0, diff.size());
}

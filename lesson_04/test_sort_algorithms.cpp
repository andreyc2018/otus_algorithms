#include "sort_algorithms.h"
#include "stopwatch.h"
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

void create_random_array(std::vector<int>& array,
                         std::vector<int>& expected_array, size_t size)
{
    std::generate_n(std::back_inserter(array), size, std::ref(rng));
    expected_array = array;
    std::sort(expected_array.begin(), expected_array.end());
}

void create_sorted_array(std::vector<int>& array,
                         std::vector<int>& expected_array, size_t size)
{
    array.resize(size);
    std::iota(array.begin(), array.end(), 100000);
    expected_array = array;
}

void create_partially_sorted_array(std::vector<int>& array,
                                   std::vector<int>& expected_array, size_t size)
{
    create_sorted_array(array, expected_array, size);
    auto from = std::next(std::begin(array), 1000);
    auto to = std::next(from, 500);
    std::shuffle(from, to, rng);
}

void create_reversed_array(std::vector<int>& array,
                           std::vector<int>& expected_array, size_t size)
{
    create_sorted_array(array, expected_array, size);
    std::reverse(array.begin(), array.end());
}

void diff_arrays(std::vector<int>& array,
                 std::vector<int>& expected_array,
                 std::vector<int>& diff)
{
    std::set_difference(array.begin(), array.end(),
                        expected_array.begin(), expected_array.end(),
                        std::inserter(diff, diff.begin()));
}

template <typename F>
void timed_run(F func, std::string msg)
{
    std::cout << "\n";
    stop_watch_t t;
    t.start();
    func();
    auto elapsed = t.stop();
    std::cout << msg << " " << elapsed << " " << t.period() << "\n\n";
}

TEST(InsertionSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_random_array(array, expected_array, InsertArraySize);

    timed_run([&array]() { insertion_sort(array); }, "Insert sort: unsorted");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, InsertArraySize);

    timed_run([&array]() { insertion_sort(array); }, "Insert sort: sorted");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_partially_sorted_array(array, expected_array, InsertArraySize);
    
    timed_run([&array]() { insertion_sort(array); }, "Insert sort: partially sorted");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_reversed_array(array, expected_array, InsertArraySize);

    timed_run([&array]() { insertion_sort(array); }, "Insert sort: reversed");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
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

struct ShellSortInfo
{
    size_t interval;
    std::string msg;
};

void run_unsorted(size_t interval, std::string msg)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_random_array(array, expected_array, ArraySize);

    timed_run([&array, interval]() { shell_sort(array, interval); }, msg);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

static std::vector<ShellSortInfo> info {
    { 2, "Shell sort: unsorted, interval 2" },
    { 100, "Shell sort: unsorted, interval 100" },
    { 1000, "Shell sort: unsorted, interval 1000" },
    { knuth_interval(ArraySize), "Shell sort: unsorted, Knuth interval" }
};

TEST(ShellSort, Unsorted)
{
//    for (const auto& i : info) {
//        run_unsorted(i.interval, i.msg);
//    }
    for (int i = 0; i < 2; ++i) {
        run_unsorted(1000, "Knuth");
    }
}

TEST(ShellSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, ArraySize);

    auto interval = knuth_interval(array.size());
    timed_run([&array, interval]() { shell_sort(array, interval); },
              "Shell sort: sorted, Knuth interval");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_partially_sorted_array(array, expected_array, ArraySize);

    auto interval = knuth_interval(array.size());
    timed_run([&array, interval]() { shell_sort(array, interval); },
              "Shell sort: partially sorted, Knuth interval");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_reversed_array(array, expected_array, ArraySize);

    auto interval = knuth_interval(array.size());
    timed_run([&array, interval]() { shell_sort(array, interval); },
              "Shell sort: reversed, Knuth interval");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

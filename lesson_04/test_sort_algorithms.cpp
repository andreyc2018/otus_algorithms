#include "sort_algorithms.h"
#include "stopwatch.h"
#include "fib_matrix.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <deque>
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

    while (interval < size/3) {
        interval = interval * 3 + 1;
    }
    return interval;
}

struct ShellSortInfo
{
    std::deque<size_t> gaps;
    std::string msg;
};

template <typename G>
void run_unsorted(G& gaps, std::string msg)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_random_array(array, expected_array, ArraySize);

    timed_run([&array, gaps]() { shell_sort(array, gaps); }, msg);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

static std::vector<ShellSortInfo> info {
    { {}, "Shell sort: unsorted, Ciura:" },
    { {}, "Shell sort: unsorted, Simple:" },
    { {}, "Shell sort: unsorted, Hibbard:" },
    { {}, "Shell sort: unsorted, Knuth:" },
    { {}, "Shell sort: unsorted, Fib:" }
};

enum GapIdx { Knuth = 3, Ciura = 0,
              Simple = 1, Hibbard = 2, Fib = 4 };

void create_knuth_gaps()
{
    auto& gaps = info[Knuth].gaps;
    size_t interval = 1;
    while (interval < ArraySize/3) {
        interval = interval * 3 + 1;
    }
    for (; interval > 0; interval = (interval - 1) / 3) {
        gaps.push_back(interval);
    }
}

// https://oeis.org/A102549
void create_ciura_gaps()
{
    auto& gaps = info[Ciura].gaps;
    gaps = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    std::reverse(std::begin(gaps), std::end(gaps));
    for(auto e : gaps) std::cout << e << " ";
    std::cout << "\n";
}

// https://oeis.org/A168604
void create_hibbard_gaps()
{
    auto& gaps = info[Hibbard].gaps;
    gaps = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
    std::reverse(std::begin(gaps), std::end(gaps));
}

void create_simple_gaps()
{
    auto& gaps = info[Simple].gaps;
    gaps = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    std::reverse(std::begin(gaps), std::end(gaps));
}

void create_fib_gaps()
{
    for (size_t i = 2; i < 15; ++i) {
        info[Fib].gaps.push_front(fib(i));
    }
}

TEST(ShellSort, Unsorted)
{
    create_knuth_gaps();
    create_ciura_gaps();
    create_hibbard_gaps();
    create_simple_gaps();
    create_fib_gaps();

    for (const auto& i : info) {
        run_unsorted(i.gaps, i.msg);
    }
}

template <typename G>
void run_sorted(G& gaps, std::string msg)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, ArraySize);

    timed_run([&array, &gaps]() { shell_sort(array, gaps); }, msg);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, Sorted)
{
    for (const auto& i : info) {
        run_sorted();
        run_sorted(i.gaps, i.msg);
    }
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

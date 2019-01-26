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

constexpr size_t InsertArraySize = 50000;
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
    stop_watch_t t;
    t.start();
    func();
    auto elapsed = t.stop();
    std::cout << msg << " " << elapsed << " " << t.period() << "\n";
}

TEST(InsertionSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_random_array(array, expected_array, InsertArraySize);

    timed_run([&array]() { insertion_sort(array); }, "Unsorted:        ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, InsertArraySize);

    timed_run([&array]() { insertion_sort(array); }, "Sorted:          ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_partially_sorted_array(array, expected_array, InsertArraySize);
    
    timed_run([&array]() { insertion_sort(array); }, "Partially sorted:");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(InsertionSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_reversed_array(array, expected_array, InsertArraySize);

    timed_run([&array]() { insertion_sort(array); }, "Reversed:        ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

struct ShellSortInfo
{
    std::vector<size_t> gaps;
    std::string msg;
};

static std::vector<ShellSortInfo> info {
    { {}, "Shell sort: Ciura:       " },
    { {}, "Shell sort: Power of two:" },
    { {}, "Shell sort: Hibbard:     " },
    { {}, "Shell sort: Pratt:       " },
    { {}, "Shell sort: Fib:         " }
};

// https://en.wikipedia.org/wiki/Shellsort
enum GapIdx { Ciura = 0,    // https://oeis.org/A102549
              PowerTwo = 1,
              Hibbard = 2,  // https://oeis.org/A168604
              Pratt = 3,    // https://oeis.org/A003462
              Fib = 4 };

void create_pratt_gaps()
{
    auto& gaps = info[Pratt].gaps;
    size_t interval = 1;
    while (interval < ArraySize/3) {
        interval = interval * 3 + 1;
    }
    for (; interval > 0; interval = (interval - 1) / 3) {
        gaps.push_back(interval);
    }
}

void create_gaps(GapIdx idx, std::vector<size_t>&& seq)
{
    std::reverse(std::begin(seq), std::end(seq));
    info[idx].gaps = seq;
}

void create_fib_gaps()
{
    auto& gaps = info[Fib].gaps;
    for (size_t i = 2; i < 15; ++i) {
        gaps.push_back(fib(i));
    }
    std::reverse(std::begin(gaps), std::end(gaps));
}

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

template <typename G>
void run_partially_sorted(G& gaps, std::string msg)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_partially_sorted_array(array, expected_array, ArraySize);

    timed_run([&array, &gaps]() { shell_sort(array, gaps); }, msg);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

template <typename G>
void run_reversed(G& gaps, std::string msg)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_reversed_array(array, expected_array, ArraySize);

    timed_run([&array, &gaps]() { shell_sort(array, gaps); }, msg);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(ShellSort, Unsorted)
{
    for (const auto& i : info) {
        run_unsorted(i.gaps, i.msg);
    }
}

TEST(ShellSort, Sorted)
{
    for (const auto& i : info) {
        run_sorted(i.gaps, i.msg);
    }
}

TEST(ShellSort, PartiallySorted)
{
    for (const auto& i : info) {
        run_partially_sorted(i.gaps, i.msg);
    }
}

TEST(ShellSort, Reversed)
{
    for (const auto& i : info) {
        run_reversed(i.gaps, i.msg);
    }
}

int main(int argc, char** argv)
{
    create_pratt_gaps();
    create_gaps(Ciura, {1, 4, 10, 23, 57, 132, 301, 701, 1750});
    create_gaps(Hibbard, {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023});
    create_gaps(PowerTwo, {1, 4, 16, 64, 256, 1024, 4096, 16384});
    create_fib_gaps();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

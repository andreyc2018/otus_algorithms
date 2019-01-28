#include "heapsort.h"
#include <stopwatch.h>
#include <random>
#include <algorithm>
#include <gtest/gtest.h>

namespace {
std::random_device rd;
std::mt19937 rng(rd());
}

constexpr size_t ArraySize = 150000;

void create_random_array(std::vector<int>& array,
                         std::vector<int>& expected_array, size_t size)
{
    std::generate_n(std::back_inserter(array), size, std::ref(rng));
    expected_array = array;
    std::sort(expected_array.begin(), expected_array.end());
}

void create_sorted_array(std::vector<int>& array,
                         std::vector<int>& expected_array,
                         size_t size, int initial)
{
    array.resize(size);
    std::iota(array.begin(), array.end(), initial);
    expected_array = array;
}

void create_partially_sorted_array(std::vector<int>& array,
                                   std::vector<int>& expected_array,
                                   size_t size, int initial)
{
    create_sorted_array(array, expected_array, size, initial);
    auto from = std::next(std::begin(array), 1000);
    auto to = std::next(from, 500);
    std::shuffle(from, to, rng);
}

void create_reversed_array(std::vector<int>& array,
                           std::vector<int>& expected_array,
                           size_t size, int initial)
{
    create_sorted_array(array, expected_array, size, initial);
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

TEST(HeapSort, BuildHeap)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, ArraySize, 1);

    std::make_heap(std::begin(expected_array), std::end(expected_array));

    otus::build_heap(array);
    otus::build_heap(array);
    otus::build_heap(array);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_random_array(array, expected_array, ArraySize);

    timed_run([&array]() { otus::heapsort(array); }, "Unsorted:        ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, ArraySize, 3000);

    timed_run([&array]() { otus::heapsort(array); }, "Sorted:          ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_partially_sorted_array(array, expected_array, ArraySize, 2000);

    timed_run([&array]() { otus::heapsort(array); }, "Partially sorted:");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSort, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_reversed_array(array, expected_array, ArraySize, 5050);

    timed_run([&array]() { otus::heapsort(array); }, "Reversed:        ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, BuildHeap)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, ArraySize, 1);

    std::make_heap(std::begin(expected_array), std::end(expected_array));

    otus::build_heap_loop(array);
    otus::build_heap_loop(array);
    otus::build_heap_loop(array);

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, Unsorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_random_array(array, expected_array, ArraySize);

    timed_run([&array]() { otus::heapsort_loop(array); }, "Unsorted:         ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, Sorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_sorted_array(array, expected_array, ArraySize, 3000);

    timed_run([&array]() { otus::heapsort_loop(array); }, "Sorted:           ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, PartiallySorted)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_partially_sorted_array(array, expected_array, ArraySize, 2000);

    timed_run([&array]() { otus::heapsort_loop(array); }, "Partially sorted:");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

TEST(HeapSortLoop, Reversed)
{
    std::vector<int> array;
    std::vector<int> expected_array;
    create_reversed_array(array, expected_array, ArraySize, 5050);

    timed_run([&array]() { otus::heapsort_loop(array); }, "Reversed:        ");

    std::vector<int> diff;
    diff_arrays(array, expected_array, diff);
    EXPECT_EQ(0, diff.size());
}

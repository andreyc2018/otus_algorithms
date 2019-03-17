#pragma once

#include <stopwatch.h>
#include <random>
#include <algorithm>
#include <functional>
#include <ostream>
#include <limits>

namespace test_tools {

namespace {
std::random_device rd;
std::mt19937 rng(rd());
}

constexpr size_t ArraySize = 1500000;

void create_random_array(std::vector<int>& array,
                         std::vector<int>& expected_array, size_t size,
                         size_t max = std::numeric_limits<size_t>::max())
{
    std::generate_n(std::back_inserter(array), size, [&max] () { return rng() % max; });
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
void timed_run(std::ostream& out, F func, std::string msg)
{
    stop_watch_t t;
    t.start();
    func();
    auto elapsed = t.stop();
    out << msg << " " << elapsed << " " << t.period() << "\n";
}

template <typename T>
void debug_print(std::ostream& out, const T& array)
{
    for (const auto& v : array) {
        out << v << " ";
    }
    out << "\n";
}

template <typename T, typename S = typename T::size_type>
void debug_print(std::ostream& out, T& array, S b, S e, const std::string& msg)
{
    out << msg << " " << b << ":" << e << " - ";
    for (auto i = b; i < e; ++i) {
        out << array[i] << " ";
    }
    out << "\n";
}

}

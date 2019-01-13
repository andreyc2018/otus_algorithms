#include "fib_matrix.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <limits>
#include <iostream>

using namespace boost::multiprecision;
using uint2048_t = number<cpp_int_backend<2048, 2048, unsigned_magnitude, unchecked, void>>;

int main(int argc, char** argv)
{
    uint2048_t n = (argc > 1)? std::stoi(argv[1]) : 0;
    auto r = fib(n);
    std::cout << "fib(" << n << ")     = " << r << "\n";
    std::cout << "Max uint64_t = " << std::numeric_limits<uint64_t>::max() << "\n";
    std::cout << "Max int64_t  = " << std::numeric_limits<int64_t>::max() << "\n";
    std::cout << "fib(190)     = 2281217241465037496128651402858212007295" << "\n";
    std::cout << "fib(301)     = 359579325206583560961765665172189099052367214309267232255589801" << "\n";
    return 0;
}

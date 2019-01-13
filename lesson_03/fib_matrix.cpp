#include "fib_matrix.h"
#include <limits>
#include <iostream>

int main(int argc, char** argv)
{
    uint64_t n = (argc > 1)? std::stoi(argv[1]) : 0;
    uint64_t r = fib(n);
    std::cout << "fib(" << n << ")     = " << r << "\n";
    std::cout << "Max uint64_t = " << std::numeric_limits<uint64_t>::max() << "\n";
    std::cout << "Max int64_t  = " << std::numeric_limits<int64_t>::max() << "\n";
    std::cout << "fib(190)     = 2281217241465037496128651402858212007295" << "\n";
    return 0;
}

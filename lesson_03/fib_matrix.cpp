#include "fib_matrix.h"
#include <iostream>

int main(int argc, char** argv)
{
    uint64_t n = (argc > 1)? std::stoi(argv[1]) : 0;
    uint64_t r = fib(n);
    std::cout << "fib(" << n << ") = " << r << "\n";
    return 0;
}
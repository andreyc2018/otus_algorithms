#include "fib_matrix.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace boost::multiprecision;
using uint2048_t = number<cpp_int_backend<2048, 2048, unsigned_magnitude, unchecked, void>>;

int main(int argc, char *argv[])
{
    const char* fname = (argc > 1)? argv[1] : "fib.txt";
    std::ifstream f(fname);
    if (f.good()) {
        std::cout << "reading from " << fname << "\n";
        uint2048_t n;

        std::string expected;
        while (f >> n >> expected) {
            auto r = fib(n);
            std::ostringstream os;
            os << r;
            if (os.str() != expected) {
                std::cout << n
                          << "\n got unexpected result " << r
                          << "\n expected              " << expected << "\n";
            }
        }
    } else {
        std::cout << "unable to open " << fname << "\n";
    }
    return 0;
}


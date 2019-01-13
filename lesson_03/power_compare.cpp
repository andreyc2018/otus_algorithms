#include "power.h"
#include <stopwatch.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <cmath>

using namespace boost::multiprecision;
using uint2048_t = number<cpp_int_backend<2048, 2048, unsigned_magnitude, unchecked, void>>;

auto mul = [](auto a, auto b) { return a * b; };

template<typename I>
I power_1(I a, I b)
{
    I r = 1;
    for (I i = 0; i < b; ++i) {
        r *= a;
    }
    return r;
}

template<typename I>
I power_2(I a, I b)
{
    return power(a, b, mul);
}

int main(int, char**)
{
    stop_watch_t t;

    t.start();
    uint64_t a = 12;
    uint64_t b = 27;
    auto r = std::pow(a, b);
    auto elapsed = t.stop();
    std::cout << "std::pow = " << static_cast<uint2048_t>(r) << " : " << elapsed << " " << t.period() << "\n";

    uint2048_t x = 12;
    uint2048_t y = 27;
    t.start();
    auto ra = power_1(x, y); // 429981696
    elapsed = t.stop();
    std::cout << "power_1  = " << ra << " : " << elapsed << " " << t.period() << "\n";

    t.start();
    ra = power_2(x, y);
    elapsed = t.stop();
    std::cout << "power_2  = " << ra << " : " << elapsed << " " << t.period() << "\n";
    return 0;
}

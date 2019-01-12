#include "power.h"
#include <stopwatch.h>
#include <iostream>
#include <cmath>

auto mul = [](auto a, auto b) { return a * b; };

template<typename I>
I power_1(I a, I b)
{
    I r = 1;
    for (int i = 0; i < b; ++i) {
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
    auto r = std::pow(12, 8);
    auto elapsed = t.stop();
    std::cout << "std::pow = " << static_cast<uint64_t>(r) << " : " << elapsed << " " << t.period() << "\n";

    t.start();
    auto ra = power_1(12, 8); // 429981696
    elapsed = t.stop();
    std::cout << "power_1  = " << ra << " : " << elapsed << " " << t.period() << "\n";

    t.start();
    ra = power_2(12, 8);
    elapsed = t.stop();
    std::cout << "power_2  = " << ra << " : " << elapsed << " " << t.period() << "\n";
    return 0;
}

#include <stopwatch.h>
#include <iostream>
#include <tuple>

// 1234567890 12
std::tuple<uint64_t, uint64_t> gcd_1(uint64_t a, uint64_t b)
{
    while(a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return std::make_tuple(a, b);
}

std::tuple<uint64_t, uint64_t> gcd_2(uint64_t a, uint64_t b)
{
    while(a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return std::make_tuple(a, b);
}

int main(int argc, char const *argv[])
{
    stop_watch_t t;

    t.start();
    auto [ra, rb] = gcd_1(1234567890, 12);
    auto elapsed = t.stop();
    std::cout << "gcd_1 = " << ra << ", " << rb << " : " << elapsed << " " << t.period() << "\n";

    t.start();
    auto [a, b] = gcd_2(1234567890, 12);
    elapsed = t.stop();
    std::cout << "gcd_2 = " << a << ", " << b << " : " << elapsed << " " << t.period() << "\n";
    return 0;
}

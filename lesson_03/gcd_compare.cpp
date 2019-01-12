#include <stopwatch.h>
#include <iostream>
#include <tuple>

// 1234567890 12
uint64_t gcd_1(uint64_t a, uint64_t b)
{
    while(a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

uint64_t gcd_2(uint64_t a, uint64_t b)
{
    while(a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return a;
}

int main(int, char const**)
{
    stop_watch_t t;

    t.start();
    auto a = gcd_1(1234567890, 12);
    auto elapsed = t.stop();
    std::cout << "gcd_1 = " << a << " : " << elapsed << " " << t.period() << "\n";

    t.start();
    a = gcd_2(1234567890, 12);
    elapsed = t.stop();
    std::cout << "gcd_2 = " << a << " : " << elapsed << " " << t.period() << "\n";
    return 0;
}

#include <stopwatch.h
#include <iostream>

int64_t multiply_1(int64_t a, int64_t b)
{
    return a * b;
}

int64_t multiply_2(int64_t a, int64_t b)
{
    return a * b;
}

int main(int argc, char const *argv[])
{
    stop_watch_t t;

    t.start();
    auto ra = multiply_1(10, 12);
    auto elapsed = t.stop();
    std::cout << "gcd_1 = " << ra << " : " << elapsed << " " << t.period() << "\n";

    t.start();
    ra = multiply_2(10, 12);
    elapsed = t.stop();
    std::cout << "gcd_2 = " << ra << " : " << elapsed << " " << t.period() << "\n";
    return 0;
}

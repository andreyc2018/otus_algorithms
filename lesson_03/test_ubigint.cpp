#include "ubigint.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(UBigInt, Init)
{
    UBigInt bi(99);
    std::cout << bi << "\n";
    std::cout << "Max uint16_t = " << std::numeric_limits<uint16_t>::max() << "\n";
    std::cout << "Max int16_t  = " << std::numeric_limits<int16_t>::max() << "\n";

    bi = std::numeric_limits<uint16_t>::max();
    std::cout << bi << "\n";
    UBigInt b2(5);
    bi += b2;
    std::cout << bi << "\n";
}

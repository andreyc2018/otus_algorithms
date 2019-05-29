#include "fen_parser.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Board, Init)
{
    Board b;
    EXPECT_EQ('R', b.get('a', 1));
}
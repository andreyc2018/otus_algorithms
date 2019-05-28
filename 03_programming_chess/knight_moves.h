#pragma once

#include <bitset>

using board_t = std::bitset<64>;

board_t get_knight_moves(const board_t& knight)
{
    board_t noA(0xFEFEFEFEFEFEFEFE);
    board_t noAB(0xFCFCFCFCFCFCFCFC);
    board_t noGH(0x3F3F3F3F3F3F3F3F);
    board_t noH(0x7F7F7F7F7F7F7F7F);

    return (noGH & (knight >> 10 | knight <<  6)) |
           (noH  & (knight >> 17 | knight << 15)) |
           (noA  & (knight >> 15 | knight << 17)) |
           (noAB & (knight >>  6 | knight << 10));
}

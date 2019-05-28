#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include <bitset>

class BitBoard
{
public:
    using bitboard_t = std::bitset<sizeof (uint64_t)>;

    BitBoard() : board_(0) {}
    BitBoard(uint64_t value) : board_(value) {}

    void shift_left(int steps) { ; }

private:
    bitboard_t board_;
};

#endif // BITBOARD_H

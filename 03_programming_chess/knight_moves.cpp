#include <iostream>
#include <bitset>

using namespace std;
using board_t = bitset<64>;

board_t get_knight_moves(board_t& knight)
{
    board_t noA(0xFEFEFEFEFEFEFEFE);
    board_t noAB(0xFCFCFCFCFCFCFCFC);
    board_t noGH(0x3F3F3F3F3F3F3F3F);
    board_t noH(0x7F7F7F7F7F7F7F7F);
    return (noGH & (knight >> 10 | knight <<  6)) |
                  (knight >> 17 | knight << 15) |
                  (knight >> 15 | knight << 17) |
                  (knight >>  6 | knight << 10);
}

int main(int argc, char** argv)
{
    int pos = (argc > 1)? stoi(argv[1]) : 0;
    board_t knight(0);
    knight.set(pos);
    cout << get_knight_moves(knight).to_ulong() << "\n";
    return 0;
}

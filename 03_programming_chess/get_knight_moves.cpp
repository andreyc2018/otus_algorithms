#include <iostream>
#include <bitset>

using namespace std;
using board_t = bitset<64>;

board_t get_knight_moves(const board_t& knight)
{
    board_t noA(0xFEFEFEFEFEFEFEFE);
    board_t noAB(0xFCFCFCFCFCFCFCFC);
    board_t noGH(0x3F3F3F3F3F3F3F3F);
    board_t noH(0x7F7F7F7F7F7F7F7F);

    board_t res = (noGH & (knight >> 10 | knight <<  6)) |
                  (noH  & (knight >> 17 | knight << 15)) |
                  (noA  & (knight >> 15 | knight << 17)) |
                  (noAB & (knight >>  6 | knight << 10));

    return res;
}

void get_print_result(size_t pos)
{
    if (pos > 63) {
        cout << 0 << "\n" << 0 << "\n";
        return;
    }
    board_t knight(0);
    knight.set(pos);
    knight = get_knight_moves(knight);
    cout << knight.count() << "\n" << knight.to_ulong() << "\n";
}

int main(int argc, char** argv)
{
    size_t pos = (argc > 1)? stoul(argv[1]) : 0;
    get_print_result(pos);
    return 0;
}

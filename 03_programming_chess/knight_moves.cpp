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

    // board_t res = 
    return (noGH & (knight >> 10 | knight <<  6));// |
                //   (knight >> 17 | knight << 15) |
                //   (knight >> 15 | knight << 17) |
                //   (knight >>  6 | knight << 10);
}

void print_board(const board_t& board)
{
    // for (ssize_t i = board.size() - 1; i >= 0; --i) {
    //     int row = (i / 8);
    //     int col = (i % 8);
    //     int idx = (row * 8 + (7 - col));
    //     cout << "i = " << i << ", idx = " << idx
    //          << " (" << row << ", " << col << ", " << 7 - col << ") = "
    //          << board[i] << "\n";
    // }

    for (ssize_t i = board.size() - 1; i >= 0; --i) {
        int row = (i / 8);
        int col = 7 - (i % 8);
        int idx = (row * 8 + col);
        cout << board[idx];
        if (col < 7) {
            cout << " ";
        } else {
            cout << "\n";
        }
    } 
}

void moves(int pos)
{
    if (pos < 0 || pos > 63) {
        return;
    }
    cout << "pos: " << pos << "\n";
    board_t knight(0);
    knight.set(pos);
    knight = get_knight_moves(knight); 
    cout << knight.count() << " " << knight.to_ulong() << "\n";
    knight.set(pos);
    print_board(knight);
    cout << "\n";
}
int main(int argc, char** argv)
{
    int pos = (argc > 1)? stoi(argv[1]) : 0;
    for (int i = pos; i < 64; ++i) {
        moves(i);
    }
    return 0;
}

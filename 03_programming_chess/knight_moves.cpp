#include "knight_moves.h"
#include <iostream>

void print_board(const board_t& board)
{
    for (ssize_t i = board.size() - 1; i >= 0; --i) {
        int row = (i / 8);
        int col = 7 - (i % 8);
        int idx = (row * 8 + col);
        std::cout << board[idx];
        if (col < 7) {
            std::cout << " ";
        } else {
            std::cout << "\n";
        }
    } 
}

void moves(int pos)
{
    if (pos < 0 || pos > 63) {
        return;
    }
    std::cout << "pos: " << pos << "\n";
    
    board_t knight(0);
    knight.set(pos);
    knight = get_knight_moves(knight); 
    
    std::cout << knight.count() << " " << knight.to_ulong() << "\n";
    
    knight.set(pos);
    print_board(knight);
    
    std::cout << "\n";
}
int main(int argc, char** argv)
{
    int pos = (argc > 1)? std::stoi(argv[1]) : 0;
    moves(pos);
    return 0;
}

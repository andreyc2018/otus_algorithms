#include "knight_moves.h"
#include <iostream>

void get_print_result(size_t pos)
{
    if (pos > 63) {
        std::cout << 0 << "\n" << 0 << "\n";
        return;
    }
    board_t knight(0);
    knight.set(pos);
    knight = get_knight_moves(knight);
    std::cout << knight.count() << "\n" << knight.to_ulong() << "\n";
}

int main(int argc, char** argv)
{
    size_t pos = (argc > 1)? std::stoul(argv[1]) : 0;
    
    get_print_result(pos);
    
    return 0;
}

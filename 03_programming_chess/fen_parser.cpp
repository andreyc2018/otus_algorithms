#include "fen_parser.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

Board::Board()
  : char_board_()
  , active_color_(White)
  , castling_(0)
  , halfmove_(0)
  , move_counter_(0)
{
    fen_to_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    for (const auto& c : char_board_) {
        if (c == 0)
            std::cout << "0x00 ";
        else
            std::cout << c << ' ';
    }
    std::cout << '\n';
}

void Board::set(Board::piece_t piece, char l, uint8_t n)
{
    auto index = coords_to_index(l, n);
    if (index > -1) {
        char_board_[index] = piece;
    }
}

Board::piece_t Board::get(char l, uint8_t n)
{
    auto index = coords_to_index(l, n);
    if (index > -1) {
        return char_board_[index];
    }
    return ' ';
}

int8_t Board::coords_to_index(char l, int8_t n)
{
    int8_t index = (l - 'a') * 8 + (n - 1);
    if (index > 63) {
        return -1;
    }
    return index;
}

std::tuple<char, int> Board::index_to_coords(int8_t index)
{
    char l = (index / 8) + 'a';
    int  n = (index % 8) + 1;
    return std::make_tuple(l, n);
}

void Board::fen_to_board(const std::string& fen)
{
    std::istringstream       iss(fen);
    std::vector<std::string> parts(std::istream_iterator<std::string>{ iss },
                                   std::istream_iterator<std::string>());
    enum
    {
        PiecePlacement = 0,
        ActiveColor    = 1,
        Castling       = 2,
        EnPassant      = 3,
        HalfmoveClock  = 4,
        FullmoveNumber = 5,
        NumParts       = 6
    };

    if (parts.size() != NumParts) {
        std::cerr << "Incorrect FEN " << fen << "\n";
        return;
    };

    char l = 'h';
    int  n = 1;
    for (size_t i = 0; i < parts[PiecePlacement].size(); ++i) {
        if (fen[i] != '/') {
            set(parts[PiecePlacement][i], l, n);
        } else {
            --l;
            n = 1;
        }
    }

    if (parts[ActiveColor][0] == 'w') {
        active_color_ = White;
    } else {
        active_color_ = Black;
    }
}

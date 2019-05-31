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
  , en_passant_()
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

void Board::set(Board::piece_t piece, col_t l, row_t n)
{
    auto index = coords_to_index(l, n);
    if (index > -1) {
        char_board_[index] = piece;
    }
}

Board::piece_t Board::get(col_t l, row_t n)
{
    auto index = coords_to_index(l, n);
    if (index > -1) {
        return char_board_[index];
    }
    return ' ';
}

Board::index_t Board::coords_to_index(col_t l, row_t n)
{
    index_t index = (l - 'a') * 8 + (n - 1);
    if (index > 63) {
        return -1;
    }
    return index;
}

Board::coords_t Board::index_to_coords(index_t index)
{
    col_t l = (index / 8) + 'a';
    row_t n = (index % 8) + 1;
    return coords_t(l, n);
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

    col_t l = 'h';
    row_t n = 1;
    for (size_t i = 0; i < parts[PiecePlacement].size(); ++i) {
        std::cerr << parts[PiecePlacement][i] << "\n";
        if (parts[PiecePlacement][i] != '/') {
            set(parts[PiecePlacement][i], l, n);
            ++n;
        } else {
            --l;
            n = 1;
        }
    }
    std::cerr << "\n";

    if (parts[ActiveColor][0] == 'w') {
        active_color_ = White;
    } else {
        active_color_ = Black;
    }

    if (parts[Castling][0] != '-') {
        std::for_each(std::begin(parts[Castling]), std::end(parts[Castling]), [this](auto c) {
            if (c == 'K') {
                this->castling_.set(WhiteKing);
            } else if (c == 'Q') {
                this->castling_.set(WhiteQueen);
            } else if (c == 'k') {
                this->castling_.set(BlackKing);
            } else if (c == 'q') {
                this->castling_.set(BlackQueen);
            }
        });
    } else {
        castling_.reset();
    }

    if (parts[EnPassant][0] != '-') {
        en_passant_.set(parts[EnPassant][0], parts[EnPassant][1]);
    } else {
        en_passant_.clear();
    }

    halfmove_     = static_cast<halfmove_clock_t>(parts[HalfmoveClock][0] - '0');
    move_counter_ = static_cast<move_counter_t>(parts[FullmoveNumber][0] - '0');
}

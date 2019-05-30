#pragma once

#include <array>
#include <string>
#include <algorithm>
#include <iostream>

using board_t      = std::array<std::array<char, 8>, 8>;
using char_board_t = std::array<char, 64>;

/**
 * A FEN "record" defines a particular game position, all in one text line and using only the ASCII
character set. A text file with only FEN data records should have the file extension ".fen".[1]

A FEN record contains six fields. The separator between fields is a space. The fields are:

    Piece placement (from White's perspective). Each rank is described, starting with rank 8 and
ending with rank 1; within each rank, the contents of each square are described from file "a"
through file "h". Following the Standard Algebraic Notation (SAN), each piece is identified by a
single letter taken from the standard English names (pawn = "P", knight = "N", bishop = "B", rook =
"R", queen = "Q" and king = "K").[1] White pieces are designated using upper-case letters ("PNBRQK")
while black pieces use lowercase ("pnbrqk"). Empty squares are noted using digits 1 through 8 (the
number of empty squares), and "/" separates ranks.

    Active color. "w" means White moves next, "b" means Black moves next.

    Castling availability. If neither side can castle, this is "-". Otherwise, this has one or more
letters: "K" (White can castle kingside), "Q" (White can castle queenside), "k" (Black can castle
kingside), and/or "q" (Black can castle queenside).

    En passant target square in algebraic notation. If there's no en passant target square, this is
"-". If a pawn has just made a two-square move, this is the position "behind" the pawn. This is
recorded regardless of whether there is a pawn in position to make an en passant capture.[2]

    Halfmove clock: This is the number of halfmoves since the last capture or pawn advance. This is
used to determine if a draw can be claimed under the fifty-move rule.

    Fullmove number: The number of the full move. It starts at 1, and is incremented after Black's
move.

 * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 * r...R - pieces and empty spaces
 * w - next turn in white or
 */
class Board
{
public:
    using piece_t = char_board_t::value_type;

    Board()
      : board_()
      , char_board_()
    {
        fen_to_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        for (const auto& c : char_board_) {
            if (c == 0)
                std::cout << "0x00 ";
            else
                std::cout << c << ' ';
        }
        std::cout << '\n';
        for (size_t l = 0; l < board_.size(); ++l) {
            for (size_t n = 0; n < board_[l].size(); ++n) {
                auto c = board_[l][n];
                if (c == 0)
                    std::cout << "0x00 ";
                else
                    std::cout << c << ' ';
                board_[l][n] = ' ';
            }
            std::cout << '\n';
        }
    }
    Board(const char* fen);

    void set(piece_t piece, char l, uint8_t n)
    {
        auto index = coords_to_index(l, n);
        if (index > -1) {
            char_board_[index] = piece;
        }
    }

    piece_t get(char l, uint8_t n)
    {
        auto index = coords_to_index(l, n);
        if (index > -1) {
            return char_board_[index];
        }
        return ' ';
    }

private:
    board_t      board_;
    char_board_t char_board_;

    int8_t coords_to_index(char l, int8_t n)
    {
        int8_t index = (l - 'a') * 8 + (n - 1);
        if (index > 63) {
            return -1;
        }
        return index;
    }

    std::tuple<char, int> index_to_coords(int8_t index)
    {
        char l = (index / 8) + 'a';
        int  n = (index % 8) + 1;
        return std::make_tuple(l, n);
    }

    void fen_to_board(const std::string& fen)
    {
        char l = 'h';
        int  n = 1;
        for (size_t i = 0; i < fen.size(); ++i) {
            if (fen[i] != '/') {
                set(fen[i], l, n);
            } else {
                --l;
                n = 1;
            }
        }
    }

    // std::string board_to_fen(const board_t& board)
    // {
    //     for (size_t l = 0; l < board.size(); ++l) {
    //         for (size_t n = 0; n < board[l].size(); ++n) {
    //             std::cout << l << ":" << n << " = " << board[l][n] << "\n";
    //         }
    //     }
    // }
};

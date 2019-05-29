#pragma once

#include <array>
#include <string>
#include <algorithm>
#include <iostream>

using board_t      = std::array<std::array<char, 8>, 8>;
using char_board_t = std::array<char, 64>;

/**
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

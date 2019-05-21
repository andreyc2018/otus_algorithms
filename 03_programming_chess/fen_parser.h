#pragma once

#include <array>
#include <string>
#include <algorithm>

using board_t = std::array<std::array<char, 8>, 8>;
using char_board_t = std::array<char, 64>;

/**
 * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 */
class Board
{
    public:
        Board() 
        {
            for (size_t l = 0; l < board_.size(); ++l) {
                for (size_t n = 0; n < board_[l].size(); ++n) {
                    board_[l][n] = ' ';
                }
            }
        }
        Board(const char* fen);

    private:
        board_t board_;
        char_board_t char_board_;

        void set(char figure, char l, int n)
        {
            int index = coords_to_index(l, n);
            if (index > -1) {
                char_board_[index] = figure;
            }
        }

        char get(char l, int n)
        {
            int index = coords_to_index(l, n);
            if (index > -1) {
                return char_board_[index];
            }
            return ' ';
        }

        int coords_to_index(char l, int n)
        {
            int index = (l - 'a') * 8 + (n - 1);
            if (index > 63) {
                return -1;
            }
            return index;
        }

        std::tuple<char, int> index_to_coords(int index)
        {
            char l = (index / 8) + 'a';
            int n = (index % 8) + 1;
            return std::make_tuple(l, n);
        }

        void fen_to_board(const std::string& fen)
        {
            char l = 'h';
            int n = 1;
            for (size_t i = 0; i < fen.size(); ++i) {
                if (fen[i] == '/') {
                    --l;
                    n = 1;
                    continue;
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
#pragma once

#include <array>
#include <string>
#include <tuple>
#include <bitset>

using board_t = std::array<char, 64>;

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
    using piece_t          = board_t::value_type;
    using castling_t       = std::bitset<4>;
    using halfmove_clock_t = uint8_t;
    using move_counter_t   = uint64_t;
    using col_t            = char;
    using row_t            = uint8_t;
    using index_t          = int8_t;

    struct coords_t
    {
        coords_t() = default;
        coords_t(col_t c, row_t r)
          : l(c)
          , n(r)
        {}

        void clear() { set(' ', static_cast<row_t>(0)); }
        void set(char c, char r) { set(c, static_cast<row_t>(r - '0')); }
        void set(col_t c, row_t r)
        {
            l = c;
            n = r;
        }

        operator bool() const { return l != ' ' && n != 0; }

        col_t l = ' ';
        row_t n = 0;
    };

    enum castling_side_t
    {
        WhiteKing  = 0,
        WhiteQueen = 1,
        BlackKing  = 2,
        BlackQueen = 3
    };
    enum color_t
    {
        White = 0,
        Black = 1
    };

    Board();
    Board(const char* fen);

    void        fen_to_board(const std::string& fen);
    std::string board_to_fen() const;

    void    move(const std::string& move);
    void    set(piece_t piece, col_t l, row_t n);
    piece_t get(col_t l, row_t n);

private:
    board_t          char_board_;
    color_t          active_color_;
    castling_t       castling_;
    coords_t         en_passant_;
    halfmove_clock_t halfmove_;
    move_counter_t   move_counter_;

    index_t  coords_to_index(col_t l, row_t n);
    coords_t index_to_coords(index_t index);
};

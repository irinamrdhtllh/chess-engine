#ifndef GAME_H
#define GAME_H

#include <string>
#define BOARD_SIZE 8

enum PieceType {
    PIECE_KING,
    PIECE_QUEEN,
    PIECE_BISHOP,
    PIECE_KNIGHT,
    PIECE_ROOK,
    PIECE_PAWN,
};

enum Color {
    COLOR_DARK,
    COLOR_LIGHT,
};

struct Position {
    char file;
    char rank;

    std::string to_string() {
        std::string s;
        s += file;
        s += rank;
        return s;
    }
};

struct Piece {
    PieceType type;
    Color color;
    Position init_position;
};

struct Square {
    Position position;
    Color color;
    Piece *piece;
};

#define POSITION_ARRAY_APPEND(moves, position, file_offset, rank_offset)       \
    if ((position.file - 'a' + (file_offset)) >= 0 &&                          \
        (position.file - 'a' + (file_offset)) < BOARD_SIZE &&                  \
        (position.rank - '1' + (rank_offset)) >= 0 &&                          \
        (position.rank - '1' + (rank_offset)) < BOARD_SIZE) {                  \
        (moves).push_back((Position){.file = static_cast<char>(position.file + (file_offset)),    \
                                     .rank = static_cast<char>(position.rank + (rank_offset))});  \
    }

#endif // GAME_H
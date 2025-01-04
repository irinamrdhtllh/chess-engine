#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define BOARD_SIZE 8

#define MAX(a, b)                                                              \
    ({                                                                         \
        __typeof__(a) _a = (a);                                                \
        __typeof__(b) _b = (b);                                                \
        _a > _b ? _a : _b;                                                     \
    })

typedef enum {
    PIECE_KING,
    PIECE_QUEEN,
    PIECE_BISHOP,
    PIECE_KNIGHT,
    PIECE_ROOK,
    PIECE_PAWN,
} PieceType;

typedef enum {
    COLOR_DARK,
    COLOR_LIGHT,
} Color;

typedef struct Position {
    char file;
    char rank;
} Position;

typedef struct {
    PieceType type;
    Color color;
    Position init_position;
} Piece;

typedef struct {
    Position position;
    Color color;
    Piece *piece;
} Square;

#define POSITION_ARRAY_APPEND(moves, position, file_offset, rank_offset)       \
    if ((position.file - 'a' + (file_offset)) >= 0 &&                          \
        (position.file - 'a' + (file_offset)) < BOARD_SIZE &&                  \
        (position.rank - '1' + (rank_offset)) >= 0 &&                          \
        (position.rank - '1' + (rank_offset)) < BOARD_SIZE) {                  \
        position_array_append(                                                 \
            moves, (Position){.file = position.file + (file_offset),           \
                              .rank = position.rank + (rank_offset)});         \
    }

typedef struct {
    size_t capacity;
    size_t length;
    Position *array;
} PositionArray;

void position_print(Position position);

PositionArray *position_array_new();
void position_array_free(PositionArray *position_array);
void position_array_append(PositionArray *position_array, Position position);

#endif // GAME_H
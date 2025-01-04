#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 8

typedef int number;

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

typedef struct {
    PieceType type;
    Color color;
} Piece;

typedef struct {
    char file;
    char rank;
    Color color;
    Piece *piece;
} Square;

Square board[BOARD_SIZE][BOARD_SIZE];

char get_piece_char(Piece *piece) {
    switch (piece->type) {
    case PIECE_KING:
        return 'K';
    case PIECE_QUEEN:
        return 'Q';
    case PIECE_BISHOP:
        return 'B';
    case PIECE_KNIGHT:
        return 'N';
    case PIECE_ROOK:
        return 'R';
    case PIECE_PAWN:
        return 'P';
    }

    return '\0';
}

int main(int argc, char const *argv[]) {
    for (char rank = '8'; rank >= '1'; rank--) {
        int row = rank - '1';
        for (char file = 'a'; file <= 'h'; file++) {
            int col = file - 'a';
            board[col][row].file = file;
            board[col][row].rank = rank;
            if ((col + row) % 2 == 0) {
                board[col][row].color = COLOR_DARK;
            } else {
                board[col][row].color = COLOR_LIGHT;
            }
            board[col][row].piece = NULL;
        }
    }

    // Light pieces
    // clang-format off
    board['a' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_LIGHT });
    board['b' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_LIGHT });
    board['c' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_LIGHT });
    board['d' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_QUEEN, .color = COLOR_LIGHT });
    board['e' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_KING, .color = COLOR_LIGHT });
    board['f' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_LIGHT });
    board['g' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_LIGHT });
    board['h' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_LIGHT });
    board['a' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['b' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['c' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['d' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['e' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['f' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['g' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    board['h' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT });
    // clang-format on

    // Dark pieces
    // clang-format off
    board['a' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_DARK });
    board['b' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_DARK });
    board['c' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_DARK });
    board['d' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_QUEEN, .color = COLOR_DARK });
    board['e' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_KING, .color = COLOR_DARK });
    board['f' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_DARK });
    board['g' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_DARK });
    board['h' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_DARK });
    board['a' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['b' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['c' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['d' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['e' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['f' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['g' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    board['h' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK });
    // clang-format on

    for (char rank = '8'; rank >= '1'; rank--) {
        int row = rank - '1';
        for (char file = 'a'; file <= 'h'; file++) {
            int col = file - 'a';
            printf("[%c %c]", board[col][row].color == COLOR_DARK ? 'x' : ' ',
                   board[col][row].piece != NULL
                       ? get_piece_char(board[col][row].piece)
                       : ' ');
        }
        printf("\n");
    }

    return 0;
}

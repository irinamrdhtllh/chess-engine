#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

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

PositionArray *get_knight_moves(Position position) {
    PositionArray *moves = position_array_new();
    POSITION_ARRAY_APPEND(moves, position, 2, 1);
    POSITION_ARRAY_APPEND(moves, position, 2, -1);
    POSITION_ARRAY_APPEND(moves, position, -2, 1);
    POSITION_ARRAY_APPEND(moves, position, -2, -1);
    POSITION_ARRAY_APPEND(moves, position, 1, 2);
    POSITION_ARRAY_APPEND(moves, position, 1, -2);
    POSITION_ARRAY_APPEND(moves, position, -1, 2);
    POSITION_ARRAY_APPEND(moves, position, -1, -2);
    return moves;
}

PositionArray *get_rook_moves(Position position) {
    PositionArray *moves = position_array_new();
    for (int offset = 0; offset < BOARD_SIZE; offset++) {
        if (offset != position.file - 'a') {
            POSITION_ARRAY_APPEND(moves, position, offset, 0);
        }
        if (offset != position.rank - '1') {
            POSITION_ARRAY_APPEND(moves, position, 0, offset);
        }
    }
    return moves;
}

PositionArray *get_bishop_moves(Position position) {
    PositionArray *moves = position_array_new();
    for (int offset = 1; offset < BOARD_SIZE; offset++) {
        POSITION_ARRAY_APPEND(moves, position, offset, offset);
        POSITION_ARRAY_APPEND(moves, position, offset, -offset);
        POSITION_ARRAY_APPEND(moves, position, -offset, offset);
        POSITION_ARRAY_APPEND(moves, position, -offset, -offset);
    }
    return moves;
}

PositionArray *get_queen_moves(Position position) {
    PositionArray *moves = position_array_new();
    PositionArray *knight_moves = get_knight_moves(position);
    for (int i = 0; i < knight_moves->length; i++) {
        position_array_append(moves, knight_moves->array[i]);
    }
    PositionArray *bishop_moves = get_knight_moves(position);
    for (int i = 0; i < bishop_moves->length; i++) {
        position_array_append(moves, bishop_moves->array[i]);
    }
    position_array_free(knight_moves);
    position_array_free(bishop_moves);
    return moves;
}

PositionArray *get_king_moves(Position position) {
    PositionArray *moves = position_array_new();
    POSITION_ARRAY_APPEND(moves, position, 1, 0);
    POSITION_ARRAY_APPEND(moves, position, -1, 0);
    POSITION_ARRAY_APPEND(moves, position, 0, 1);
    POSITION_ARRAY_APPEND(moves, position, 0, -1);
    POSITION_ARRAY_APPEND(moves, position, 1, 1);
    POSITION_ARRAY_APPEND(moves, position, -1, -1);
    POSITION_ARRAY_APPEND(moves, position, 1, -1);
    POSITION_ARRAY_APPEND(moves, position, -1, 1);
    return moves;
}

PositionArray *get_valid_moves(Square square) {
    PositionArray *positions;
    switch (square.piece->type) {
    case PIECE_KING:
        positions = get_king_moves(square.position);
        break;
    case PIECE_QUEEN:
        positions = get_queen_moves(square.position);
        break;
    case PIECE_BISHOP:
        positions = get_bishop_moves(square.position);
        break;
    case PIECE_KNIGHT:
        positions = get_knight_moves(square.position);
        break;
    case PIECE_ROOK:
        positions = get_rook_moves(square.position);
        break;
    case PIECE_PAWN:
        assert(false && "Not implemented");
    }
    return positions;
}

int main(int argc, char const *argv[]) {
    for (char rank = '8'; rank >= '1'; rank--) {
        int row = rank - '1';
        for (char file = 'a'; file <= 'h'; file++) {
            int col = file - 'a';
            board[col][row].position = (Position){.file = file, .rank = rank};
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
    board['a' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_LIGHT , .init_position = {.file =  'a', .rank =  '1'}});
    board['b' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_LIGHT , .init_position = {.file =  'b', .rank =  '1'}});
    board['c' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_LIGHT , .init_position = {.file =  'c', .rank =  '1'}});
    board['d' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_QUEEN, .color = COLOR_LIGHT , .init_position = {.file =  'd', .rank =  '1'}});
    board['e' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_KING, .color = COLOR_LIGHT , .init_position = {.file =  'e', .rank =  '1'}});
    board['f' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_LIGHT , .init_position = {.file =  'f', .rank =  '1'}});
    board['g' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_LIGHT , .init_position = {.file =  'g', .rank =  '1'}});
    board['h' - 'a']['1' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_LIGHT , .init_position = {.file =  'h', .rank =  '1'}});
    board['a' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'a', .rank =  '2'}});
    board['b' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'b', .rank =  '2'}});
    board['c' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'c', .rank =  '2'}});
    board['d' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'd', .rank =  '2'}});
    board['e' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'e', .rank =  '2'}});
    board['f' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'f', .rank =  '2'}});
    board['g' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'g', .rank =  '2'}});
    board['h' - 'a']['2' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_LIGHT , .init_position = {.file =  'h', .rank =  '2'}});
    // clang-format on

    // Dark pieces
    // clang-format off
    board['a' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_DARK , .init_position = {.file =  'a', .rank =  '8'}});
    board['b' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_DARK , .init_position = {.file =  'b', .rank =  '8'}});
    board['c' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_DARK , .init_position = {.file =  'c', .rank =  '8'}});
    board['d' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_QUEEN, .color = COLOR_DARK , .init_position = {.file =  'd', .rank =  '8'}});
    board['e' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_KING, .color = COLOR_DARK , .init_position = {.file =  'e', .rank =  '8'}});
    board['f' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_BISHOP, .color = COLOR_DARK , .init_position = {.file =  'f', .rank =  '8'}});
    board['g' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_KNIGHT, .color = COLOR_DARK , .init_position = {.file =  'g', .rank =  '8'}});
    board['h' - 'a']['8' - '1'].piece = &((Piece) { .type = PIECE_ROOK, .color = COLOR_DARK , .init_position = {.file =  'h', .rank =  '8'}});
    board['a' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'a', .rank =  '7'}});
    board['b' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'b', .rank =  '7'}});
    board['c' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'c', .rank =  '7'}});
    board['d' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'd', .rank =  '7'}});
    board['e' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'e', .rank =  '7'}});
    board['f' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'f', .rank =  '7'}});
    board['g' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'g', .rank =  '7'}});
    board['h' - 'a']['7' - '1'].piece = &((Piece) { .type = PIECE_PAWN, .color = COLOR_DARK , .init_position = {.file =  'h', .rank =  '7'}});
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

    printf("\n");

    board['f' - 'a']['1' - '1'].position = (Position){.file = 'e', .rank = '4'};

    PositionArray *positions = get_valid_moves(board['f' - 'a']['1' - '1']);
    for (int i = 0; i < positions->length; i++) {
        position_print(positions->array[i]);
        printf("\n");
    }

    printf("positions: %zu\n", positions->length);

    return 0;
}

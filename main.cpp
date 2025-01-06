#include <cstddef>
#include <stdexcept>
#include <vector>

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

#define POSITION_ARRAY_APPEND(moves, square, file_offset, rank_offset)         \
    if ((square.position.file - 'a' + (file_offset)) >= 0 &&                   \
        (square.position.file - 'a' + (file_offset)) < BOARD_SIZE &&           \
        (square.position.rank - '1' + (rank_offset)) >= 0 &&                   \
        (square.position.rank - '1' + (rank_offset)) < BOARD_SIZE &&           \
        !is_position_collides(square, file_offset, rank_offset)) {             \
        (moves).push_back((Position){                                          \
            .file = static_cast<char>(square.position.file + (file_offset)),   \
            .rank = static_cast<char>(square.position.rank + (rank_offset))}); \
    }

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

bool is_position_collides(Square square, int file_offset, int rank_offset) {
    Square next_square = board[square.position.file - 'a' + file_offset]
                              [square.position.rank - '1' + rank_offset];
    if (next_square.piece != NULL &&
        next_square.piece->color == square.piece->color) {
        return true;
    }
    return false;
}

std::vector<Position> get_knight_moves(Square square) {
    std::vector<Position> moves;
    POSITION_ARRAY_APPEND(moves, square, 2, 1);
    POSITION_ARRAY_APPEND(moves, square, 2, -1);
    POSITION_ARRAY_APPEND(moves, square, -2, 1);
    POSITION_ARRAY_APPEND(moves, square, -2, -1);
    POSITION_ARRAY_APPEND(moves, square, 1, 2);
    POSITION_ARRAY_APPEND(moves, square, 1, -2);
    POSITION_ARRAY_APPEND(moves, square, -1, 2);
    POSITION_ARRAY_APPEND(moves, square, -1, -2);
    return moves;
}

std::vector<Position> get_rook_moves(Square square) {
    std::vector<Position> moves = {};
    for (int offset = 1; offset < BOARD_SIZE; offset++) {
        POSITION_ARRAY_APPEND(moves, square, -offset, 0);
        POSITION_ARRAY_APPEND(moves, square, offset, 0);
        POSITION_ARRAY_APPEND(moves, square, 0, -offset);
        POSITION_ARRAY_APPEND(moves, square, 0, offset);
    }
    return moves;
}

std::vector<Position> get_bishop_moves(Square square) {
    std::vector<Position> moves = {};
    for (int offset = 1; offset < BOARD_SIZE; offset++) {
        POSITION_ARRAY_APPEND(moves, square, offset, offset);
        POSITION_ARRAY_APPEND(moves, square, offset, -offset);
        POSITION_ARRAY_APPEND(moves, square, -offset, offset);
        POSITION_ARRAY_APPEND(moves, square, -offset, -offset);
    }
    return moves;
}

std::vector<Position> get_queen_moves(Square square) {
    std::vector<Position> moves = {};
    std::vector<Position> knight_moves = get_knight_moves(square);
    for (int i = 0; i < knight_moves.size(); i++) {
        moves.push_back(knight_moves[i]);
    }
    std::vector<Position> bishop_moves = get_knight_moves(square);
    for (int i = 0; i < bishop_moves.size(); i++) {
        moves.push_back(bishop_moves[i]);
    }
    return moves;
}

std::vector<Position> get_king_moves(Square square) {
    std::vector<Position> moves = {};
    POSITION_ARRAY_APPEND(moves, square, 1, 0);
    POSITION_ARRAY_APPEND(moves, square, -1, 0);
    POSITION_ARRAY_APPEND(moves, square, 0, 1);
    POSITION_ARRAY_APPEND(moves, square, 0, -1);
    POSITION_ARRAY_APPEND(moves, square, 1, 1);
    POSITION_ARRAY_APPEND(moves, square, -1, -1);
    POSITION_ARRAY_APPEND(moves, square, 1, -1);
    POSITION_ARRAY_APPEND(moves, square, -1, 1);
    return moves;
}

std::vector<Position> get_valid_moves(Square square) {
    std::vector<Position> positions;
    switch (square.piece->type) {
    case PIECE_KING:
        positions = get_king_moves(square);
        break;
    case PIECE_QUEEN:
        positions = get_queen_moves(square);
        break;
    case PIECE_BISHOP:
        positions = get_bishop_moves(square);
        break;
    case PIECE_KNIGHT:
        positions = get_knight_moves(square);
        break;
    case PIECE_ROOK:
        positions = get_rook_moves(square);
        break;
    case PIECE_PAWN:
        throw std::logic_error("Not implemented");
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
    board['a' - 'a']['1' - '1'].piece = new Piece{PIECE_ROOK, COLOR_LIGHT, {.file = 'a', .rank = '1'}};
    board['b' - 'a']['1' - '1'].piece = new Piece{PIECE_KNIGHT, COLOR_LIGHT, {.file = 'b', .rank = '1'}};
    board['c' - 'a']['1' - '1'].piece = new Piece{PIECE_BISHOP, COLOR_LIGHT, {.file = 'c', .rank = '1'}};
    board['d' - 'a']['1' - '1'].piece = new Piece{PIECE_QUEEN, COLOR_LIGHT, {.file = 'd', .rank = '1'}};
    board['e' - 'a']['1' - '1'].piece = new Piece{PIECE_KING, COLOR_LIGHT, {.file = 'e', .rank = '1'}};
    board['f' - 'a']['1' - '1'].piece = new Piece{PIECE_BISHOP, COLOR_LIGHT, {.file = 'f', .rank = '1'}};
    board['g' - 'a']['1' - '1'].piece = new Piece{PIECE_KNIGHT, COLOR_LIGHT, {.file = 'g', .rank = '1'}};
    board['h' - 'a']['1' - '1'].piece = new Piece{PIECE_ROOK, COLOR_LIGHT, {.file = 'h', .rank = '1'}};
    board['a' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'a', .rank = '2'}};
    board['b' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'b', .rank = '2'}};
    board['c' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'c', .rank = '2'}};
    board['d' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'd', .rank = '2'}};
    board['e' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'e', .rank = '2'}};
    board['f' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'f', .rank = '2'}};
    board['g' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'g', .rank = '2'}};
    board['h' - 'a']['2' - '1'].piece = new Piece{PIECE_PAWN, COLOR_LIGHT, {.file = 'h', .rank = '2'}};
    // clang-format on

    // Dark pieces
    // clang-format off
    board['a' - 'a']['8' - '1'].piece = new Piece{PIECE_ROOK, COLOR_DARK, {.file = 'a', .rank = '8'}};
    board['b' - 'a']['8' - '1'].piece = new Piece{PIECE_KNIGHT, COLOR_DARK, {.file = 'b', .rank = '8'}};
    board['c' - 'a']['8' - '1'].piece = new Piece{PIECE_BISHOP, COLOR_DARK, {.file = 'c', .rank = '8'}};
    board['d' - 'a']['8' - '1'].piece = new Piece{PIECE_QUEEN, COLOR_DARK, {.file = 'd', .rank = '8'}};
    board['e' - 'a']['8' - '1'].piece = new Piece{PIECE_KING, COLOR_DARK, {.file = 'e', .rank = '8'}};
    board['f' - 'a']['8' - '1'].piece = new Piece{PIECE_BISHOP, COLOR_DARK, {.file = 'f', .rank = '8'}};
    board['g' - 'a']['8' - '1'].piece = new Piece{PIECE_KNIGHT, COLOR_DARK, {.file = 'g', .rank = '8'}};
    board['h' - 'a']['8' - '1'].piece = new Piece{PIECE_ROOK, COLOR_DARK, {.file = 'h', .rank = '8'}};
    board['a' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'a', .rank = '7'}};
    board['b' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'b', .rank = '7'}};
    board['c' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'c', .rank = '7'}};
    board['d' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'd', .rank = '7'}};
    board['e' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'e', .rank = '7'}};
    board['f' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'f', .rank = '7'}};
    board['g' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'g', .rank = '7'}};
    board['h' - 'a']['7' - '1'].piece = new Piece{PIECE_PAWN, COLOR_DARK, {.file = 'h', .rank = '7'}};
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

    board['h' - 'a']['1' - '1'].position = (Position){.file = 'e', .rank = '4'};

    std::vector<Position> positions =
        get_valid_moves(board['h' - 'a']['1' - '1']);
    for (int i = 0; i < positions.size(); i++) {
        printf("%s", positions[i].to_string().c_str());
        printf("\n");
    }

    printf("positions: %zu\n", positions.size());

    return 0;
}

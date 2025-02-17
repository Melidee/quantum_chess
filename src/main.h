#include <stdbool.h>

typedef struct {
    int selected_x;
    int selected_y;
} TurnState;

typedef enum {
    pawn = 0,
    rook = 1,
    knight = 2,
    bishop = 3,
    queen = 4,
    king = 5,
    empty = 6,
} PieceKind;

const char* piece_icons[7] = {
    "P",
    "R",
    "N",
    "B",
    "Q",
    "K",
    " ",
};

typedef enum {
    white,
    black,
    no_color,
} qColor;

typedef struct {
    PieceKind kind;
    qColor color;
} Piece;

typedef struct {
    Piece board[8][8];
} Board;

const int square_size = 100;
Board init_board();


typedef struct {
    int x;
    int y;
} Coordinate;

bool is_valid_move(Board board, Coordinate from, Coordinate to);

void draw_board_boxes();
void draw_pieces();
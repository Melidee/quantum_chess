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
    
} Board;

const int square_size = 100;
void init_board();


typedef struct {
    int x;
    int y;
} Coordinate;

bool is_valid_move(Piece board[8][8], Coordinate from, Coordinate to, PieceKind kind);
void clear_possibilities(bool buf[8][8]);
void check_possible_moves(bool buf[8][8], Piece board[8][8], Coordinate from, PieceKind kind);

void draw_board_boxes();
void draw_pieces();
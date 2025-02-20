#include "main.h"

#include <stdio.h>

#include "raylib.h"

int main() {
    InitWindow(800, 800, "Quantum Chess");
    Piece board[8][8];
    init_board(board);
    bool possible_moves[8][8] = {0};
    clear_possibilities(possible_moves);
    qColor turn = white;
    Coordinate selected = {-1, -1};

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        Coordinate hover_space = {(int)mouse_pos.x / square_size,
                                  (int)mouse_pos.y / square_size};
        Piece hover_piece = board[hover_space.x][hover_space.y];

        BeginDrawing();
        ClearBackground(BLACK);
        draw_board_boxes(possible_moves);
        DrawRectangle(hover_space.x * square_size, hover_space.y * square_size,
                      square_size, square_size, DARKBROWN);
        draw_pieces(board);
        EndDrawing();

        bool can_select =
            hover_piece.kind != empty && hover_piece.color == turn;
        if (can_select && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selected = hover_space;

            check_possible_moves(possible_moves, board, selected,
                                 hover_piece.kind);
            continue;
        } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
            possible_moves[hover_space.x][hover_space.y]) {
            board[hover_space.x][hover_space.y].kind =
                board[selected.x][selected.y].kind;
            board[hover_space.x][hover_space.y].color =
                board[selected.x][selected.y].color;
            board[selected.x][selected.y].kind = empty;
            board[selected.x][selected.y].color = no_color;
            selected.x = -1;
            clear_possibilities(possible_moves);
            turn = turn == white ? black : white;
        }
    }
    CloseWindow();
}

void draw_board_boxes(bool possibilities[8][8]) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Color color = x % 2 == y % 2 ? BEIGE : BROWN;
            DrawRectangle(x * square_size, y * square_size, square_size,
                          square_size, color);
            if (possibilities[x][y]) {
                DrawCircle(x * square_size + square_size / 2,
                           y * square_size + square_size / 2, square_size / 4,
                           DARKBROWN);
            }
        }
    }
}

void draw_pieces(Piece board[8][8]) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece piece = board[x][y];
            if (piece.kind == empty) {
                continue;
            }
            DrawText(piece_icons[piece.kind], x * square_size + square_size / 3,
                     y * square_size + square_size / 3, square_size / 2,
                     piece.color == white ? WHITE : BLACK);
        }
    }
}

void check_possible_moves(bool possibilities[8][8], Piece board[8][8],
                          Coordinate from, PieceKind kind) {
    switch (kind) {
        case pawn:
            break;
        case rook:
            for (int i = 1; i < 8; i++) {
                if (from.x + i < 8) {
                    possibilities[from.x + i][from.y] = true;
                }
                if (from.x - i >= 0) {
                    possibilities[from.x - i][from.y] = true;
                }
                if (from.y + i < 8) {
                    possibilities[from.x][from.y + i] = true;
                }
                if (from.y - i >= 0) {
                    possibilities[from.x][from.y - i] = true;
                }
            }
            break;
        case knight:  // WORKING!!!
            int checks[8][2] = {
                {from.x + 2, from.y + 1}, {from.x + 2, from.y - 1},
                {from.x - 2, from.y + 1}, {from.x - 2, from.y - 1},
                {from.x + 1, from.y + 2}, {from.x + 1, from.y - 2},
                {from.x - 1, from.y + 2}, {from.x - 1, from.y - 2},
            };
            for (int i = 0; i < 8; i++) {
                if (checks[i][0] >= 0 && checks[i][0] < 8 &&
                    checks[i][1] >= 0 && checks[i][1] < 8) {
                    possibilities[checks[i][0]][checks[i][1]] = true;
                }
            }
            break;
        case bishop:
            for (int i = 1; i < 8; i++) {
                if (from.x + i < 8 && from.y + i < 8) {
                    possibilities[from.x + i][from.y + i] = true;
                }
                if (from.x - i >= 0 && from.y - i >= 0) {
                    possibilities[from.x - i][from.y - i] = true;
                }
                if (from.x - i >= 0 && from.y + i < 8) {
                    possibilities[from.x - i][from.y + i] = true;
                }
                if (from.x + i < 8 && from.y - i >= 0) {
                    possibilities[from.x + i][from.y - i] = true;
                }
            }
            break;
        case queen:
            check_possible_moves(possibilities, board, from, rook);
            check_possible_moves(possibilities, board, from, bishop);
            break;
        case king:  // WORKING!!!
            int k_checks[8][2] = {
                {from.x + 1, from.y},     {from.x - 1, from.y},
                {from.x, from.y + 1},     {from.x, from.y - 1},
                {from.x + 1, from.y + 1}, {from.x - 1, from.y - 1},
                {from.x + 1, from.y - 1}, {from.x - 1, from.y + 1},
            };
            for (int i = 0; i < 8; i++) {
                if (k_checks[i][0] >= 0 && k_checks[i][0] < 8 &&
                    k_checks[i][1] >= 0 && k_checks[i][1] < 8) {
                    possibilities[k_checks[i][0]][k_checks[i][1]] = true;
                }
            }
            break;
        case empty:
            break;
    }
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            bool is_friendly_space =
                board[x][y].color == board[from.x][from.y].color;
            if (possibilities[x][y] && is_friendly_space) {
                possibilities[x][y] = false;
            }
        }
    }
}

void clear_possibilities(bool possibilities[8][8]) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            possibilities[x][y] = false;
        }
    }
}

void init_board(Piece board[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].kind = empty;
            board[i][j].color = no_color;
        }
    }
    for (int i = 0; i < 8; i++) {
        board[i][0].color = black;
        board[i][1].color = black;
        board[i][1].kind = pawn;
    }
    for (int i = 0; i < 8; i++) {
        board[i][7].color = white;
        board[i][6].color = white;
        board[i][6].kind = pawn;
    }
    board[0][0].kind = rook;
    board[1][0].kind = knight;
    board[2][0].kind = bishop;
    board[3][0].kind = queen;
    board[4][0].kind = king;
    board[5][0].kind = bishop;
    board[6][0].kind = knight;
    board[7][0].kind = rook;

    board[0][7].kind = rook;
    board[1][7].kind = knight;
    board[2][7].kind = bishop;
    board[3][7].kind = queen;
    board[4][7].kind = king;
    board[5][7].kind = bishop;
    board[6][7].kind = knight;
    board[7][7].kind = rook;
}
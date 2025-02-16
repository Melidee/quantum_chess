#include "main.h"

#include <stdio.h>

#include "raylib.h"

qColor turn = white;
TurnState turn_state = {0, 0, 0, 0, 0, 0};
Board board;

int main() {
    InitWindow(800, 800, "Quantum Chess");

    board = init_board();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_board_boxes();
        Vector2 mouse_pos = GetMousePosition();
        DrawRectangle(((int)mouse_pos.x / 100) * square_size,
                      ((int)mouse_pos.y / 100) * square_size, square_size,
                      square_size, GRAY);
        draw_pieces();

        EndDrawing();
    }

    CloseWindow();
}

void draw_board_boxes() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Color color = x % 2 == y % 2 ? BEIGE : BROWN;
            DrawRectangle(x * square_size, y * square_size, square_size,
                          square_size, color);
        }
    }
}

void draw_pieces() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece piece = board.board[x][y];
            if (piece.kind == empty) {
                continue;
            }
            DrawText(piece_icons[piece.kind], x * square_size + square_size / 2,
                     y * square_size + square_size / 2, 40,
                     piece.color == white ? WHITE : BLACK);
        }
    }
}

Board init_board() {
    Board board;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board.board[i][j].kind = empty;
            board.board[i][j].color = no_color;
        }
    }
    for (int i = 0; i < 8; i++) {
        board.board[i][0].color = black;
        board.board[i][1].color = black;
        board.board[i][1].kind = pawn;
    }
    for (int i = 0; i < 8; i++) {
        board.board[i][7].color = white;
        board.board[i][6].color = white;
        board.board[i][6].kind = pawn;
    }
    board.board[0][0].kind = rook;
    board.board[1][0].kind = knight;
    board.board[2][0].kind = bishop;
    board.board[3][0].kind = queen;
    board.board[4][0].kind = king;
    board.board[5][0].kind = bishop;
    board.board[6][0].kind = knight;
    board.board[7][0].kind = rook;

    board.board[0][7].kind = rook;
    board.board[1][7].kind = knight;
    board.board[2][7].kind = bishop;
    board.board[3][7].kind = queen;
    board.board[4][7].kind = king;
    board.board[5][7].kind = bishop;
    board.board[6][7].kind = knight;
    board.board[7][7].kind = rook;

    return board;
}
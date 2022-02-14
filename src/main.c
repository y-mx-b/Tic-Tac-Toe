#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Point;

void draw_grid(int screen_width, int screen_height) {
    // vertical lines
    DrawRectangleRounded((Rectangle){ screen_width/3 - 3, screen_height/40, 6, screen_height - (screen_height/20) }, 1.0f, 10, BLACK);
    DrawRectangleRounded((Rectangle){ 2*screen_width/3 - 3, screen_height/40, 6, screen_height - (screen_height/20) }, 1.0f, 10, BLACK);
    // horizontal lines
    DrawRectangleRounded((Rectangle){ screen_width/40, screen_height/3 - 3, screen_width - (screen_width/20), 6 }, 1.0f, 10, BLACK);
    DrawRectangleRounded((Rectangle){ screen_width/40, 2*screen_height/3 - 3, screen_width - (screen_width/20), 6 }, 1.0f, 10, BLACK);
}

Rectangle get_cell(int screen_width, int screen_height, Vector2 coord) {
    Rectangle cell;
    cell.height = (screen_height/3) - (screen_height/20);
    cell.width = (screen_width/3) - (screen_width/20);
    cell.x = coord.x * (screen_width/3) + (screen_width/40);
    cell.y = coord.y * (screen_height/3) + (screen_width/40);

    return cell;
}

void resize_image(Image *img, int screen_width, int screen_height) {
    ImageResize(img, screen_width/3 - (screen_width / 20), screen_height/3 - (screen_height / 20));
}

Point get_coord(int screen_width, int screen_height) {
    Point coord;
    Vector2 mouse_position = GetMousePosition();

    if (0 < mouse_position.x && mouse_position.x < screen_width/3) {
        coord.x = 0;
    } else if (screen_width/3 < mouse_position.x && mouse_position.x < 2*screen_width/3) {
        coord.x = 1;
    } else if (2*screen_width/3 < mouse_position.x && mouse_position.x < screen_width) {
        coord.x = 2;
    }

    if (0 < mouse_position.y && mouse_position.y < screen_width/3) {
        coord.y = 0;
    } else if (screen_width/3 < mouse_position.y && mouse_position.y < 2*screen_width/3) {
        coord.y = 1;
    } else if (2*screen_width/3 < mouse_position.y && mouse_position.y < screen_width) {
        coord.y = 2;
    }

    return coord;
}

int **new_board() {
    int **board = (int**)malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++ ) {
        board[i] = (int*)malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
    return board;
}

void clear_board(int **board) {
    for (int i = 0; i < 3; i++) {
        free(board[i]);
    }
    free(board);
}

int check_victory(int **board) {
    int row = 0;
    int col = 0;
    int dia1 = 0;
    int dia2 = 0;
    int empty_tiles = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0) { empty_tiles--; }

            row += board[i][j];
            col += board[j][i];
            if (row == 3 || col == 3 || row == -3 || row == -3) {
                return 1;
            }
        }
        row = col = 0;
        dia1 += board[i][i];
        dia2 += board[2 - i][i];
    }
    if (dia1 == 3 || dia2 == 3 || dia1 == -3 || dia2 == -3) { return 1; }
    if (empty_tiles == 0) { return -1; }
    return 0;
}

int main(void) {
    int screen_width = 500;
    int screen_height = 500;

    int **board = new_board();
    bool is_x = true;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "TicTacToe");
    SetWindowMinSize(80, 80);

    // Load X/O assets
    char *x_path = realpath("./assets/x.png", NULL);
    char *o_path = realpath("./assets/o.png", NULL);
    Image x_img = LoadImage(x_path);
    Image o_img = LoadImage(o_path);

    // Resize assets, prepare textures
    resize_image(&x_img, screen_width, screen_height);
    resize_image(&o_img, screen_width, screen_height);
    Texture2D x_texture = LoadTextureFromImage(x_img);
    Texture2D o_texture = LoadTextureFromImage(o_img);

    SetTargetFPS(60);

    int victory = false;
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            screen_width = GetScreenWidth() < GetScreenHeight() ? GetScreenWidth() : GetScreenHeight();
            screen_height = screen_width;
            SetWindowSize(screen_width, screen_height);

            x_img = LoadImage(x_path);
            o_img = LoadImage(o_path);
            resize_image(&x_img, screen_width, screen_height);
            resize_image(&o_img, screen_width, screen_height);
            x_texture = LoadTextureFromImage(x_img);
            o_texture = LoadTextureFromImage(o_img);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!victory) {
                Point coord = get_coord(screen_width, screen_height);
                if (board[coord.y][coord.x] == 0) {
                    board[coord.y][coord.x] = is_x ? 1 : -1;
                    is_x = !is_x;
                    printf("(%d, %d): %d\n", coord.x, coord.y, board[coord.y][coord.x]);
                }
            }
        }
        if (IsKeyPressed(KEY_R)) {
            clear_board(board);
            board = new_board();
            victory = false;
            is_x = true;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            if (victory) { // game ended
                clear_board(board);
                board = new_board();
                char *victory_text = "Tie.";
                if (victory == 1) {
                    victory_text = is_x ? "Player Two Victory!" : "Player One Victory!";
                }
                DrawText(victory_text,
                        (screen_width - MeasureTextEx(GetFontDefault(), victory_text, 42, 4).x) / 2,
                        (screen_height - MeasureTextEx(GetFontDefault(), victory_text, 42, 4).y) / 2,
                        42,
                        BLACK);
            } else { // game not ended
                victory = check_victory(board);
                draw_grid(screen_width, screen_height);
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board[i][j] == 1) {
                            Rectangle cell = get_cell(screen_width, screen_height, (Vector2){ j, i });
                            DrawTexture(x_texture, cell.x, cell.y, WHITE);
                        } else if (board[i][j] == -1) {
                            Rectangle cell = get_cell(screen_width, screen_height, (Vector2){ j, i });
                            DrawTexture(o_texture, cell.x, cell.y, WHITE);
                        }
                    }
                }
            }
        EndDrawing();
    }
    free(x_path);
    free(o_path);
    UnloadImage(x_img);
    UnloadImage(o_img);
    UnloadTexture(x_texture);
    UnloadTexture(o_texture);

    CloseWindow();

    return 0;
}

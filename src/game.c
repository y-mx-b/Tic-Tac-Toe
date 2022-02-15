#include "../include/raylib.h"
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

Rectangle get_cell(int screen_width, int screen_height, Vector2 coord) {
    Rectangle cell;
    cell.height = (screen_height/3) - (screen_height/20);
    cell.width = (screen_width/3) - (screen_width/20);
    cell.x = coord.x * (screen_width/3) + (screen_width/40);
    cell.y = coord.y * (screen_height/3) + (screen_width/40);

    return cell;
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

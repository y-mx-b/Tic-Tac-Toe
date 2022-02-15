#include "../include/raylib.h"

typedef struct {
	int x;
	int y;
} Point;

Rectangle get_cell(int screen_width, int screen_height, Vector2 coord);

Point get_coord(int screen_width, int screen_height);

// void clear_board(int **board);

void new_board(int (*board)[3][3]);

int check_victory(int (*board)[3][3]);

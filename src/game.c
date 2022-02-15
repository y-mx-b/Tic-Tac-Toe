#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Rectangle get_cell(int screen_width, int screen_height, Vector2 coord) {
  Rectangle cell;
  cell.height = (screen_height/3) - (screen_height/20);
  cell.width = (screen_width/3) - (screen_width/20);
  cell.x = coord.x * (screen_width/3) + (screen_width/40);
  cell.y = coord.y * (screen_height/3) + (screen_width/40);

  return cell;
}

IntPoint get_coord(int screen_width, int screen_height) {
  IntPoint coord;
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

void new_board(int (*board)[3][3]) {
  for (int i = 0; i < 3; i++ ) {
    for (int j = 0; j < 3; j++) {
      (*board)[i][j] = 0;
    }
  }
}

int check_victory(int (*board)[3][3]) {
  int row = 0;
  int col = 0;
  int dia1 = 0;
  int dia2 = 0;
  int empty_tiles = 9;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if ((*board)[i][j] != 0) { empty_tiles--; }

      row += (*board)[i][j];
      col += (*board)[j][i];
      if (row == 3 || col == 3) {
        return 1; // player 1 victory
      }
      if (row == -3 || col == -3) {
        return 2; // player 2 victory
      }
    }
    row = col = 0;
    dia1 += (*board)[i][i];
    dia2 += (*board)[2 - i][i];
  }
  if (dia1 == 3 || dia2 == 3) { return 1; }
  if (dia1 == -3 || dia2 == -3) { return 2; }
  if (empty_tiles == 0) { return 3; } // tie
  return 0;
}

#include "../src/draw.h"
#include "../include/raylib.h"

int main(void) {
  int screen_width = 800;
  int screen_height = 800;

  ConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screen_width, screen_height, "Test X");

  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(WHITE);
      draw_x(screen_width, screen_height);
    EndDrawing();
  }
}

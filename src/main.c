#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "game.h"
#include "draw.h"

#ifdef MACOS_APP
#include <CoreFoundation/CFBundle.h>
#endif

int main(void) {
  int screen_width = 500;
  int screen_height = 500;

  int board[3][3];
  new_board(&board);

  bool is_x = true;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screen_width, screen_height, "TicTacToe");
  SetWindowMinSize(80, 80);

#ifdef MACOS_APP
  // Load X/O assets
  CFBundleRef main_bundle = CFBundleGetMainBundle();
  CFURLRef x_url = CFBundleCopyResourceURL(main_bundle, CFSTR("x"), CFSTR("png"), NULL);
  CFURLRef o_url = CFBundleCopyResourceURL(main_bundle, CFSTR("o"), CFSTR("png"), NULL);
  CFStringRef x_path_ref = CFURLCopyFileSystemPath(x_url, kCFURLPOSIXPathStyle);
  CFStringRef o_path_ref = CFURLCopyFileSystemPath(o_url, kCFURLPOSIXPathStyle);
  CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
  const char *x_path = CFStringGetCStringPtr(x_path_ref, encodingMethod);
  const char *o_path = CFStringGetCStringPtr(o_path_ref, encodingMethod);
#else
  // Load X/O assets
  char *x_path = realpath("./assets/x.png", NULL);
  char *o_path = realpath("./assets/o.png", NULL);
#endif
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
      screen_width = GetScreenWidth() < GetScreenHeight() ?
          GetScreenWidth() : GetScreenHeight();
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
        IntPoint coord = get_coord(screen_width, screen_height);
        if (board[coord.y][coord.x] == 0) {
          board[coord.y][coord.x] = is_x ? 1 : -1;
          is_x = !is_x;
          // printf("(%d, %d): %d\n", coord.x, coord.y, board[coord.y][coord.x]);
        }
      }
    }
    if (IsKeyPressed(KEY_R)) {
      new_board(&board);
      victory = false;
      is_x = true;
    }

    BeginDrawing();
      ClearBackground(WHITE);
      if (victory) { // game ended
        new_board(&board);
        char *victory_text;
        switch (victory) {
        case 1:
          victory_text = "Player One Victory!";
          break;
        case 2:
          victory_text = "Player Two Victory!";
          break;
        case 3:
          victory_text = "Tie.";
          break;
        default:
          victory_text = "What";
          break;
        }
        DrawText(victory_text,
            (screen_width - MeasureTextEx(GetFontDefault(), victory_text, 42, 4).x) / 2,
            (screen_height - MeasureTextEx(GetFontDefault(), victory_text, 42, 4).y) / 2,
            42,
            BLACK);
      } else { // game not ended
        victory = check_victory(&board);
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
#if !defined MACOS_APP
  free(x_path);
  free(o_path);
#endif
  UnloadImage(x_img);
  UnloadImage(o_img);
  UnloadTexture(x_texture);
  UnloadTexture(o_texture);

  CloseWindow();

  return 0;
}

#include "../include/raylib.h"

void draw_grid(int screen_width, int screen_height) {
    // vertical lines
    DrawRectangleRounded((Rectangle){ screen_width/3 - 3, screen_height/40, 6, screen_height - (screen_height/20) }, 1.0f, 10, BLACK);
    DrawRectangleRounded((Rectangle){ 2*screen_width/3 - 3, screen_height/40, 6, screen_height - (screen_height/20) }, 1.0f, 10, BLACK);
    // horizontal lines
    DrawRectangleRounded((Rectangle){ screen_width/40, screen_height/3 - 3, screen_width - (screen_width/20), 6 }, 1.0f, 10, BLACK);
    DrawRectangleRounded((Rectangle){ screen_width/40, 2*screen_height/3 - 3, screen_width - (screen_width/20), 6 }, 1.0f, 10, BLACK);
}

void resize_image(Image *img, int screen_width, int screen_height) {
    ImageResize(img, screen_width/3 - (screen_width / 20), screen_height/3 - (screen_height / 20));
}

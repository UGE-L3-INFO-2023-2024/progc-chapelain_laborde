#include "Graphic.h"

void init_window(int width, int height, const char* title) {
    MLV_create_window(title, title, width, height);
}

void refresh_window() {
    MLV_actualise_window();
}

void clear_window() {
    MLV_clear_window(MLV_COLOR_BLACK);
}

void close_window() {
    MLV_free_window();
}

Image* load_image(const char* path) {
    return MLV_load_image(path);
}

void draw_rectangle(int x, int y, int width, int height, int thickness) {
    for (int i = 0; i < thickness; i++) {
        MLV_draw_rectangle(x + i, y + i, width - 2 * i, height - 2 * i,
                           MLV_COLOR_BLACK);
    }
}
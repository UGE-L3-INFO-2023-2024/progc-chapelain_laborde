/**
 * @file Graphic.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Graphic.h"

#include <stdarg.h>

#include "Map.h"

void refresh_window() {
    MLV_actualise_window();
}

/* Convert a RGB color to a MLV_Color */
MLV_Color RGB_to_MLV_Color(RGB_Color rgb, int alpha) {
    return MLV_rgba(rgb.r, rgb.g, rgb.b, alpha);
}

/* Resize an image to fit with cell size */
void resize_image_with_cell_size(MLV_Image* img, SubWindow window) {
    MLV_resize_image_with_proportions(img, window.width / MAP_WIDTH,
                                      window.height / MAP_HEIGHT);
}

void draw_rectangle(unsigned int x, unsigned int y, int width, int height,
                    unsigned int thickness, MLV_Color color) {
    MLV_draw_filled_rectangle(x, y, width, thickness, color);
    MLV_draw_filled_rectangle(x, y, thickness, height, color);
    MLV_draw_filled_rectangle(x + width - thickness, y, thickness, height,
                              color);
    MLV_draw_filled_rectangle(x, y + height - thickness, width, thickness,
                              color);
}

void draw_bar(unsigned int x, unsigned int y, int width, int height,
              unsigned int thickness, MLV_Color color, float filled_ratio,
              MLV_Color filled_color) {
    draw_rectangle(x, y, width, height, thickness, color);
    MLV_draw_filled_rectangle(x + thickness, y + thickness,
                              (width - 2 * thickness) * filled_ratio,
                              height - 2 * thickness, filled_color);
}

/* Draw a text centered on the given position */
void draw_centered_text(unsigned int x, unsigned int y, const char* text,
                        Font font, MLV_Color color, ...) {
    int text_width, text_height;
    va_list args;
    va_list args_copy;
    va_start(args, color);
    va_copy(args_copy, args);  // Copy args to use it twice
    MLV_get_size_of_text_with_font_va(text, &text_width, &text_height, font,
                                      args);
    MLV_draw_text_with_font_va(x - text_width / 2, y - text_height / 2, text,
                               font, color, args_copy);
    va_end(args_copy);
    va_end(args);
}

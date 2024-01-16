/**
 * @file Graphic.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief This file contains all the functions to draw on the screen.
 * @date 14-11-2023
 *
 */

#include "Graphic.h"

#include <stdarg.h>

#include "Map.h"
#include "Utils.h"

/* Update lMLV window */
void refresh_window() {
    MLV_update_window();
}

/* Convert a RGB color to a MLV_Color */
MLV_Color RGB_to_MLV_Color(RGB_Color rgb, Uint8 alpha) {
    return MLV_rgba(rgb.r, rgb.g, rgb.b, alpha);
}

/* Resize an image to fit with cell size */
void resize_image_with_cell_size(MLV_Image* img, SubWindow window) {
    MLV_resize_image_with_proportions(img, window.width / MAP_WIDTH,
                                      window.height / MAP_HEIGHT);
}

/* Draw a line with thickness */
void draw_line(int x1, int y1, int x2, int y2, unsigned int thickness,
               MLV_Color color) {
    for (int i = 0; i < thickness; i++) {
        MLV_draw_line(x1, y1 + i, x2, y2 + i, color);
    }
}

/* Draw a rectangle with thickness */
void draw_rectangle(unsigned int x, unsigned int y, int width, int height,
                    unsigned int thickness, MLV_Color color) {
    MLV_draw_filled_rectangle(x, y, width, thickness, color);
    MLV_draw_filled_rectangle(x, y, thickness, height, color);
    MLV_draw_filled_rectangle(x + width - thickness, y, thickness, height,
                              color);
    MLV_draw_filled_rectangle(x, y + height - thickness, width, thickness,
                              color);
}

/* Draw a bar with thickness and filled ratio */
void draw_bar(Coord_i position, int width, int height, unsigned int thickness,
              MLV_Color color, double filled_ratio, MLV_Color filled_color) {
    int x = position.x;
    int y = position.y;
    draw_rectangle(x, y, width, height, thickness, color);
    MLV_draw_filled_rectangle(x + thickness, y + thickness,
                              (int)((width - 2 * thickness) * filled_ratio),
                              height - 2 * thickness, filled_color);
}

/* Draw a text centered on the given position with a given font */
void draw_centered_text_with_font(unsigned int x, unsigned int y,
                                  const char* text, const Font* font,
                                  MLV_Color color, ...) {
    int text_width;
    int text_height;
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

/* Draw a text centered on the given position */
void draw_centered_text(unsigned int x, unsigned int y, const char* text,
                        MLV_Color color, ...) {
    int text_width;
    int text_height;
    va_list args;
    va_list args_copy;
    va_start(args, color);
    va_copy(args_copy, args);  // Copy args to use it twice
    MLV_get_size_of_text_va(text, &text_width, &text_height, args);
    MLV_draw_text_va(x - text_width / 2, y - text_height / 2, text, color,
                     args_copy);
    va_end(args_copy);
    va_end(args);
}

/* Draw empty polygon */
void draw_polygon(Polygon polygon, MLV_Color color) {
    if (polygon.nb_points < 3)
        return;
    int* vx = malloc(sizeof(int) * polygon.nb_points);
    int* vy = malloc(sizeof(int) * polygon.nb_points);
    for (int i = 0; i < polygon.nb_points; i++) {
        vx[i] = polygon.points[i].x;
        vy[i] = polygon.points[i].y;
    }
    MLV_draw_polygon(vx, vy, polygon.nb_points, color);
    free(vx);
    free(vy);
}

/* Draw filled polygon */
void draw_filled_polygon(Polygon polygon, MLV_Color color) {
    if (polygon.nb_points < 3)
        return;
    int* vx = malloc(sizeof(int) * polygon.nb_points);
    int* vy = malloc(sizeof(int) * polygon.nb_points);
    for (int i = 0; i < polygon.nb_points; i++) {
        vx[i] = polygon.points[i].x;
        vy[i] = polygon.points[i].y;
    }
    MLV_draw_filled_polygon(vx, vy, polygon.nb_points, color);
    free(vx);
    free(vy);
}

/* Clear lMLV window */
void clear_window(Window window) {
    MLV_draw_filled_rectangle((int)window.coord.x, (int)window.coord.y,
                              window.width, window.height, CLEAR_COLOR);
}

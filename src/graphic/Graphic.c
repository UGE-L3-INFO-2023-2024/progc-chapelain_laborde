/**
 * @file Graphic.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Graphic.h"

#include "Map.h"

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

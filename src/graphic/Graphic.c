/**
 * @file Graphic.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-14
 *
 */

#include "Graphic.h"

#include "Map.h"

/* Convert a RGB color to a MLV_Color */
MLV_Color RGB_to_MLV_Color(RGB rgb, int alpha) {
    return MLV_rgba(rgb.r, rgb.g, rgb.b, alpha);
}

/* Resize an image to fit with cell size */
void resize_image_with_cell_size(MLV_Image* img, SubWindow window) {
    MLV_resize_image_with_proportions(img, window.width / MAP_WIDTH,
                                      window.height / MAP_HEIGHT);
}
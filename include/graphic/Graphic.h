/**
 * @file Graphic.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Utils.h"
#include "Window.h"

/**
 * @brief Convert a RGB color to a MLV_Color.
 *
 * @param rgb RGB color to convert.
 * @return MLV_Color Converted color.
 */
MLV_Color RGB_to_MLV_Color(RGB_Color rgb, int alpha);

/**
 * @brief Resize the given image to fit the given cell size.
 *
 * @param img Image to resize.
 * @param window Window to get the cell size from.
 */
void resize_image_with_cell_size(MLV_Image* img, SubWindow window);

/**
 * @brief Draw a rectangle with the given parameters.
 *
 * @param x X position of the rectangle.
 * @param y Y position of the rectangle.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param thickness Thickness of the rectangle.
 * @param color Color of the rectangle.
 */
void draw_rectangle(unsigned int x, unsigned int y, int width, int height,
                    unsigned int thickness, MLV_Color color);

#endif  // __GRAPHIC_H__
/**
 * @file Graphic.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-14
 *
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Utils.h"

typedef struct {
    Window* window;  // The encapsulating window
    int width;       // The width of the window
    int height;      // The height of the window
    Coord_f coord;   // The north-west corner of the window
} Window, SubWindow;

/**
 * @brief Convert a RGB color to a MLV_Color.
 *
 * @param rgb RGB color to convert.
 * @return MLV_Color Converted color.
 */
MLV_Color RGB_to_MLV_Color(RGB rgb, int alpha);

/**
 * @brief Resize the given image to fit the given cell size.
 *
 * @param img Image to resize.
 * @param window Window to get the cell size from.
 */
void resize_image_with_cell_size(MLV_Image* img, SubWindow window);

#endif  // __GRAPHIC_H__
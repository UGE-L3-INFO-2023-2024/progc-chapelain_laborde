/**
 * @file Graphic.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief This file contains all the functions to draw on the screen.
 * @date 07-01-2024
 *
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Utils.h"
#include "Window.h"

#define CLEAR_COLOR MLV_COLOR_WHITE

/**************/
/* Structures */
/**************/

typedef struct {
    Point* points;
    int nb_points;
} Polygon;

/*************/
/* Functions */
/*************/

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
 * @brief Draw a line with the given parameters.
 *
 * @param x1 X position of the first point.
 * @param y1 Y position of the first point.
 * @param x2 X position of the second point.
 * @param y2 Y position of the second point.
 * @param thickness Thickness of the line.
 * @param color Color of the line.
 */
void draw_line(int x1, int y1, int x2, int y2, unsigned int thickness,
               MLV_Color color);

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

/**
 * @brief Draw a bar with the given parameters.
 *
 * @param x X position of the bar.
 * @param y Y position of the bar.
 * @param width Width of the bar.
 * @param height Height of the bar.
 * @param thickness Thickness of the bar.
 * @param color Color of the bar.
 * @param filled_ratio Ratio of the bar to fill.
 * @param filled_color Color of the filled part of the bar.
 */
void draw_bar(unsigned int x, unsigned int y, int width, int height,
              unsigned int thickness, MLV_Color color, float filled_ratio,
              MLV_Color filled_color);

/**
 * @brief Draw a text centered on the given position.
 * The text is centered on the given position with the given font and color.
 * This function is variadic, so you can pass arguments to the text.
 *
 * This function use the stdarg.h library.
 *
 * @see draw_centered_text to use the default font.
 *
 * @param x X position of the text (center).
 * @param y Y position of the text (center).
 * @param text Text to draw.
 * @param font Font to use.
 * @param color Color of the text.
 * @param ... Arguments to pass to the text.
 */
void draw_centered_text_with_font(unsigned int x, unsigned int y,
                                  const char* text, Font font, MLV_Color color,
                                  ...);

/**
 * @brief Draw a text centered on the given position.
 * The text is centered on the given position with the color.
 * This function is variadic, so you can pass arguments to the text.
 *
 * This function use the stdarg.h library.
 *
 * @param x X position of the text (center).
 * @param y Y position of the text (center).
 * @param text Text to draw.
 * @param font Font to use.
 * @param color Color of the text.
 * @param ... Arguments to pass to the text.
 */
void draw_centered_text(unsigned int x, unsigned int y, const char* text,
                        MLV_Color color, ...);

/**
 * @brief Draw a polygon with the given parameters.
 * The polygon is drawn with the given color.
 * At the difference of the draw_filled_polygon function, this function
 * doesn't fill the polygon with the given color. It only draw the outline.
 * The function accept only polygons with more than 2 points. (nb_points > 2)
 *
 * @param polygon Polygon to draw.
 * @param color Color of the outlined polygon.
 */
void draw_polygon(Polygon polygon, MLV_Color color);

/**
 * @brief Draw a polygon with the given parameters.
 * The polygon is filled with the given color.
 * The function accept only polygons with more than 2 points. (nb_points > 2)
 *
 * @param polygon Polygon to draw.
 * @param color Color of the polygon.
 */
void draw_filled_polygon(Polygon polygon, MLV_Color color);

/**
 * @brief This function clear the given window with the CLEAR_COLOR.
 *
 * @param window Window to clear.
 */
void clear_window(Window window);

/**
 * @brief This function refresh the window of a change.
 * For more information, see the MLV_actualise_window function.
 *
 */
void refresh_window();

#endif  // __GRAPHIC_H__
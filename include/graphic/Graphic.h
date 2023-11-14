#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Color.h"

typedef MLV_Image Image;

/**
 * @brief Initialize the window
 *
 * @param width The width of the window
 * @param height The height of the window
 * @param title The title of the window
 */
void init_window(int width, int height, const char* title);

/**
 * @brief Refresh the window with the current state
 *
 */
void refresh_window();

/**
 * @brief Clear the window
 *
 */
void clear_window();

/**
 * @brief Close the window
 *
 */
void close_window();

/**
 * @brief Load an image from a path
 *
 * @param path The path of the image
 * @return Image* The image loaded
 */
Image* load_image(const char* path);

/**
 * @brief Draw a rectangle with black border
 *
 * @param x The x position of the rectangle
 * @param y The y position of the rectangle
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 */
void draw_rectangle(int x, int y, int width, int height, int thickness);

#endif  // __GRAPHIC_H__
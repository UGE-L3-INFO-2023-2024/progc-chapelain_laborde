#ifndef __GRAPHIC_INVENTORY_H__
#define __GRAPHIC_INVENTORY_H__

#include "Color.h"
#include "Inventory.h"
#include "Utils.h"
#include "Window.h"

/**
 * @brief Draw a gem on the screen at the given position.
 * This function use the given color to fill the gem.
 * The outline of the gem is always black.
 *
 * @param coord The position of the gem.
 * @param w The width of the gem.
 * @param h The height of the gem.
 * @param color The color of the gem in RGB.
 */
void draw_gem(Coord_i coord, int w, int h, RGB_Color color);

/**
 * @brief Draw all the gems of the inventory on the screen.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory containing the gems to draw.
 * @param page The page of the inventory gems to draw.
 * Page start at 0 not 1.
 */
void draw_all_gems(SubWindow window, Inventory inventory, unsigned int page);

/**
 * @brief Draw the inventory of gem + the pagination in the bottom.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory to draw.
 * @param page The page of the inventory to draw starting to 0. (cf
 * draw_all_gems)
 */
void draw_gems_and_pagination(SubWindow window, Inventory inventory,
                              unsigned int page);

/**
 * @brief Clear the gems and pagination area of the inventory.
 * This function is used to actualize the inventory.
 *
 * @param window The subwindow to clear.
 */
void clear_gems_and_pagination_area(SubWindow window);

/**
 * @brief Draw the whole inventory on the screen.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory to draw.
 */
void draw_inventory(SubWindow window, Inventory inventory);

#endif  // __GRAPHIC_INVENTORY_H__
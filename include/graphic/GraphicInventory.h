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
 * @param actual_pourcent The actual pourcent of the window.
 * @param page The page of the inventory gems to draw.
 * Page start at 0 not 1.
 */
void draw_all_gems(SubWindow window, Inventory inventory,
                   double* actual_pourcent, unsigned int page);

/**
 * @brief Draw the whole inventory on the screen.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory to draw.
 */
void draw_inventory(SubWindow window, Inventory inventory);

#endif  // __GRAPHIC_INVENTORY_H__
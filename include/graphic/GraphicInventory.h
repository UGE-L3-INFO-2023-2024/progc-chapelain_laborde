/**
 * @file GraphicInventory.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Functions to draw inventory menu.
 * @date 07-01-2024
 *
 */

#ifndef __GRAPHIC_MAIN_MENU_H__
#define __GRAPHIC_MAIN_MENU_H__

#include "Button.h"
#include "Inventory.h"
#include "Window.h"

/**
 * @brief Create the buttons of the inventory.
 *
 * @param window The subwindow to draw on.
 * @param buttons The array of buttons to initialize.
 */
void create_inventory_buttons(SubWindow window, ButtonTab* buttons);

/**
 * @brief Draw the main menu.
 *
 * @param window The subwindow to draw on.
 * @param inventory The inventory to draw.
 * @param buttons The buttons of the inventory.
 * @param gem_level The actual level of the gem
 * @param page The actual page of the inventory.
 */
void draw_inventory_menu(SubWindow window, Inventory inventory,
                         ButtonTab buttons, int gem_level, int page);

/**
 * @brief Draw a gem on the screen.
 *
 * @param coord The coord of the gem.
 * @param w The width of the gem.
 * @param h The height of the gem.
 * @param gem The gem to draw.
 */
void draw_gem(Coord_i coord, int w, int h, Gem gem);

#endif  // __GRAPHIC_MAIN_MENU_H__
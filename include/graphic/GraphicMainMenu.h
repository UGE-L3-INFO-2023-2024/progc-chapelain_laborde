#ifndef __GRAPHIC_MAIN_MENU_H__
#define __GRAPHIC_MAIN_MENU_H__

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
 */
void draw_main_menu(SubWindow window, Inventory inventory, ButtonTab buttons);

#endif  // __GRAPHIC_MAIN_MENU_H__
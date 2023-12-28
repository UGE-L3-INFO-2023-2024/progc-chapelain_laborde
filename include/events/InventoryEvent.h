#ifndef __INVENTORY_EVENT_H__
#define __INVENTORY_EVENT_H__

#include <stdbool.h>

#include "Event.h"
#include "Inventory.h"
#include "Window.h"

/**
 * @brief Check if the coordinates are in the rectangle area.
 *
 * @param x X coordinate of the rectangle (top left corner)
 * @param y Y coordinate of the rectangle (top left corner)
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param cible_x X coordinate of the point to check
 * @param cible_y Y coordinate of the point to check
 * @return true if the point is in the rectangle,
 * @return false otherwise
 */
bool is_in_rect_area(int x, int y, int width, int height, int cible_x,
                     int cible_y);

/**
 * @brief Check if the event is a click in the inventory.
 *
 * @param event Event to check
 * @param inventory_window Inventory window
 * @return true if the event is a click in the inventory
 * @return false otherwise
 */
bool click_in_inventory(Event event, SubWindow inventory_window);

/**
 * @brief Check if the event is a click on the left arrow of the pagination.
 *
 * @param inventory_window Inventory window
 * @param event Event to check
 * @return true if the event is a click on the left arrow of the pagination
 * @return false otherwise
 */
bool click_left_arrow(SubWindow inventory_window, Event event);

/**
 * @brief Check if the event is a click on the right arrow of the pagination.
 *
 * @param inventory_window Inventory window
 * @param event Event to check
 * @return true if the event is a click on the right arrow of the pagination
 * @return false otherwise
 */
bool click_right_arrow(SubWindow inventory_window, Event event);

#endif  // __INVENTORY_EVENT_H__
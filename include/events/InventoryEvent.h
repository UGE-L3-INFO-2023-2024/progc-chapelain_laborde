#ifndef __INVENTORY_EVENT_H__
#define __INVENTORY_EVENT_H__

#include <stdbool.h>

#include "Button.h"
#include "Event.h"
#include "Inventory.h"
#include "Window.h"

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

bool click_on_button(SubWindow window, Event event, Button button);

#endif  // __INVENTORY_EVENT_H__
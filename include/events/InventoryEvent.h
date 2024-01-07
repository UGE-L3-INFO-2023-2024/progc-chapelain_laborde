/**
 * @file InventoryEvent.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Event functions for the inventory.
 * @date 07-01-2024
 *
 */

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

/**
 * @brief Check if the event is a click on the given button.
 *
 * @param window The subwindow where the button is displayed.
 * @param event The event to check.
 * @param button The button to check.
 * @return true if the event is a click on the button
 * @return false otherwise.
 */
bool click_on_button(SubWindow window, Event event, Button button);

/**
 * @brief This function return the gemstone on which the user clicked on.
 * If the user didn't click on a gemstone, it returns NULL.
 *
 * @param window The subwindow where the gems are displayed.
 * @param event The event to check.
 * @param inventory The inventory to retrieve the gemstones from.
 * @param page The current page of the inventory
 * @return Gemstone* The gemstone clicked on.
 */
Gemstone* click_on_gemstone(SubWindow window, Event event, Inventory inventory,
                            unsigned int page);

#endif  // __INVENTORY_EVENT_H__
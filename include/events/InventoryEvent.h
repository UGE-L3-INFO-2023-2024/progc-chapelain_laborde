/**
 * @file InventoryEvent.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Event functions for the inventory.
 * @date 28-12-2023
 *
 */

#ifndef __INVENTORY_EVENT_H__
#define __INVENTORY_EVENT_H__

#include <stdbool.h>

#include "Button.h"
#include "Event.h"
#include "Inventory.h"
#include "Window.h"

/*************/
/* Functions */
/*************/

/**
 * @brief Check if the mouse is over the inventory.
 *
 * @param event MLV event (mouse)
 * @param inventory_window Window to mouseover.
 * @return if the window is under the cursor of the mouse
 */
bool hovered_inventory(Event event, SubWindow inventory_window);

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
 * @param event The event to check.
 * @param button The button to check.
 * @return true if the event is a click on the button
 */
bool click_on_button(Event event, Button button);

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

/**
 * @brief This function is used to check if the user hover a fusion slot with
 * the mouse.
 * If the user didn't hover a fusion slot, it return false.
 * Otherwise, it returns true and set the slot to the slot hovered.
 *
 * @param slot The slot hovered
 * @param window The subwindow where the fusion slots are displayed.
 * @param event The event to check.
 * @return true if the user hover a fusion slot
 */
bool hover_fusion_slot(int* slot, SubWindow window, Event event);

/**
 * @brief This function tells which slot is clicked or -1.
 *
 * @param window The subwindow where the fusion slots are displayed.
 * @param event The event to check.
 * @return -1 or slot clicked
 */
int click_on_fusion_slot(SubWindow window, Event event);

/**
 * @brief Get the hovered fusion slot object
 *
 * @param window The subwindow where the fusion slots are displayed.
 * @param event The event to check.
 * @return -1 or slot who is mouve over
 */
int get_hovered_fusion_slot(SubWindow window, Event event);

#endif  // __INVENTORY_EVENT_H__
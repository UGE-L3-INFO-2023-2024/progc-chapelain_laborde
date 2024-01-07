/**
 * @file ButtonAction.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Do the action of the button clicked on.
 * @date 07-01-2024
 *
 */

#ifndef __BUTTONACTION_H__
#define __BUTTONACTION_H__

#include "Button.h"
#include "Event.h"
#include "Inventory.h"
#include "Map.h"
#include "Window.h"

/**
 * @brief Done the action of the button clicked on.
 *
 * @param buttons Buttons of the inventory
 * @param inventory_window Inventory window
 * @param map_window Map window
 * @param map Map
 * @param inventory Inventory
 * @param event Event
 * @param gem_level Gem level
 * @param actual_page Actual page
 */
void doing_button_actions(ButtonTab buttons, SubWindow inventory_window,
                          SubWindow map_window, Map* map, Inventory* inventory,
                          Event event, int* gem_level, int* actual_page);

#endif  // __BUTTONACTION_H__
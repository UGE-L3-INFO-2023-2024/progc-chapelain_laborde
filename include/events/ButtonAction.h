/**
 * @file ButtonAction.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Do the action of the button clicked on.
 * @date 31-12-2023
 *
 */

#ifndef __BUTTONACTION_H__
#define __BUTTONACTION_H__

#include "Button.h"
#include "Event.h"
#include "Game.h"
#include "Inventory.h"
#include "Window.h"

/*************/
/* Functions */
/*************/

/**
 * @brief Function who handle click user interaction
 * (buy gem or tower, change inventory pages or gem level, upgrade manapool)
 *
 * @param buttons The buttons of the inventory.
 * @param map_window Map graphic window
 * @param game Game to modify
 * @param event Event to check
 */
void doing_button_actions(ButtonTab buttons, SubWindow map_window, Game* game,
                          Event event);

#endif  // __BUTTONACTION_H__
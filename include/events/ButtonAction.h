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
#include "Game.h"
#include "Inventory.h"
#include "Window.h"

void doing_button_actions(ButtonTab buttons, SubWindow inventory_window,
                          SubWindow map_window, Game* game, Event event);

#endif  // __BUTTONACTION_H__
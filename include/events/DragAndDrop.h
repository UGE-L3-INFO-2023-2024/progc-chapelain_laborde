/**
 * @file DragAndDrop.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to handle drag and drop events on gemstones
 * @date 10-01-2024
 *
 */

#ifndef __DRAG_AND_DROP_H__
#define __DRAG_AND_DROP_H__

#include <stdbool.h>

#include "Event.h"
#include "Game.h"
#include "Gemstone.h"
#include "Utils.h"

/**
 * @brief Drag and drop a gemstone from everywhere to everywhere
 *
 * @details
 * If the user pressed a gem from everywhere, we select the gemstone and we
 * drag it to everywhere on the screen.
 * If the user release the gemstone there is three possibilities :
 * - The gemstone is on a tower, we put the gemstone on the tower
 * - The gemstone is on the fusion zone, we put it in the right slot
 * - The gemstone is on the screen, we put it back to the inventory
 *
 * @bug If the user click on a gemstone and move the mouse too fast, the
 * gemstone will keep moving even if the user release the mouse button.
 * (This bug is due to the frame rate at which we get events)
 * To release the gemstone, the user need to click on his mouse button again.
 * (This bug is not really important, it's just a little bit annoying
 * for the user)
 *
 * @param game The game structure containing all the data about the game.
 * @param event related to the user input (mouse, keyboard, etc.) (here we only
 * check for mouse events).
 * @param clicked_gem The gemstone that the user clicked on.
 * @param new_gem_pos The new position of the gemstone, don't change if the
 * gemstone doesn't move (if the user didn't move the mouse).
 * @return true if the user realease the gemstone and we need to draw the
 * gemstone at the new position, false otherwise.
 */
bool drag_and_drop_gemstone(Game* game, Event event, Gem** clicked_gem,
                            Point* new_gem_pos);

#endif  // __DRAG_AND_DROP_H__
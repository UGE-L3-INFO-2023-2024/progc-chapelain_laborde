/**
 * @file FieldEvent.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Get the event on the field of the game
 * @date 29-12-2023
 *
 */

#ifndef __FIELDEVENT_H__
#define __FIELDEVENT_H__

#include "Event.h"
#include "Map.h"
#include "Utils.h"
#include "Window.h"

/*************/
/* Functions */
/*************/

/**
 * @brief Get the coordinate relative to the map
 * You give the coordinate relative to the window and it returns the coordinate
 * relative to the map
 * @param window The window
 * @param coord The coordinate relative to the window
 * @return Coord_i The coordinate relative to the map
 */
Coord_i get_coord_on_map(SubWindow window, Coord_i coord);

/**
 * @brief Get the tower on the map mouse coordinates
 * If there is no tower at the given coordinate, it returns NULL
 *
 * @param window The window
 * @param event The event
 * @param map The map
 * @return Tower* The tower hovered
 */
Tower* get_hovered_tower(SubWindow window, Event event, Map map);

/**
 * @brief Get the tower on the map at click coordinates
 * If there is no tower at the given coordinate, it returns NULL
 *
 * @param window The window
 * @param event The event
 * @param map The map
 * @return Tower* The tower ckicked
 */
Tower* click_on_tower(SubWindow window, Event event, Map map);

#endif  // __FIELDEVENT_H__
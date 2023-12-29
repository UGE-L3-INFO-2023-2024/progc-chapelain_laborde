#ifndef __FIELDEVENT_H__
#define __FIELDEVENT_H__

#include "Map.h"
#include "Utils.h"
#include "Window.h"

/**
 * @brief Get the coordinate relative to the map
 * You give the coordinate relative to the window and it returns the coordinate
 * relative to the map
 * @param map The map
 * @param window The window
 * @param coord The coordinate relative to the window
 * @return Coord_i The coordinate relative to the map
 */
Coord_i get_coord_on_map(Map map, SubWindow window, Coord_i coord);

#endif  // __FIELDEVENT_H__
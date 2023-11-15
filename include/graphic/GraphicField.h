/**
 * @file GraphicField.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#ifndef __GRAPHICFIELD_H__
#define __GRAPHICFIELD_H__

#include <MLV/MLV_all.h>

#include "Graphic.h"
#include "Map.h"

/**
 * @brief Draw the map on the given window.
 *
 * @param map Map to draw.
 * @param map_window Window to draw on.
 */
void draw_map(Map map, SubWindow map_window);

#endif  // __GRAPHICFIELD_H__
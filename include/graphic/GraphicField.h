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

/**
 * @brief Draw the give mob on the given window.
 *
 * @param mob Mob to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 */
void draw_mob(Mob mob, SubWindow window, MLV_Image* img);

void draw_path_cells(Cell cells[MAP_HEIGHT][MAP_WIDTH], SubWindow window,
                     MLV_Image* img);

void clear_path_cells(Cell cells[MAP_HEIGHT][MAP_WIDTH], SubWindow window);

#endif  // __GRAPHICFIELD_H__
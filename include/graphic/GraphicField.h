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

#include "DynamicArray.h"
#include "Graphic.h"
#include "Map.h"
#include "Wave.h"

/**
 * @brief Draw the map on the given window.
 *
 * @param map Map to draw.
 * @param map_window Window to draw on.
 */
void draw_map(Map map, SubWindow map_window, DynamicArray* turns);

/**
 * @brief Draw the give mob on the given window.
 *
 * @param wave Wave to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 */
void draw_mobs(Wave* wave, SubWindow window, MLV_Image* img);

/**
 * @brief Draw the given tower on the given window.
 * If img is NULL, draw a circle with tower color instead.
 *
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 * @param x X position of the tower.
 * @param y Y position of the tower.
 * @param width Width of the tower.
 * @param height Height of the tower.
 */
void draw_tower(SubWindow window, MLV_Image* img, int x, int y, int width,
                int height);

void draw_path_cells(Cell cells[MAP_HEIGHT][MAP_WIDTH], SubWindow window,
                     MLV_Image* img);

void clear_path_cells(Cell cells[MAP_HEIGHT][MAP_WIDTH], SubWindow window);

void draw_turn(DynamicArray* da, SubWindow window);
#endif  // __GRAPHICFIELD_H__
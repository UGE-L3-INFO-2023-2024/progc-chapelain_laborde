/**
 * @file GraphicField.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief This file contains functions to draw the field.
 * @date 30-10-2023
 *
 */

#ifndef __GRAPHICFIELD_H__
#define __GRAPHICFIELD_H__

#include <MLV/MLV_all.h>

#include "Map.h"
#include "Wave.h"
#include "Window.h"

/*************/
/* Functions */
/*************/

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
 * @param wave Wave to draw.
 * @param window Window to draw on.
 * @param img Image to draw instead of a circle.
 */
void draw_mobs(Wave wave, SubWindow window, const MLV_Image* img);

#endif  // __GRAPHICFIELD_H__
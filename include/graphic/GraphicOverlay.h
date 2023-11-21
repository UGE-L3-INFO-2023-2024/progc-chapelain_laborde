/**
 * @file GraphicOverlay.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Header for GraphicOverlay module
 * @date 2023-11-20
 *
 */

#ifndef __GRAPHIC_OVERLAY_H__
#define __GRAPHIC_OVERLAY_H__

#include "Gemstone.h"
#include "Mana.h"

/**
 * @brief Show the Mana bar
 *
 * @param pool ManaPool to show
 * @param x Coordinate x of the North West corner of the bar
 * @param y Coordinate y of the North West corner of the bar
 * @param w Width of the bar
 * @param h Height of the bar
 * @param thickness Thickness of the bar
 */
void show_mana_bar(ManaPool pool, int x, int y, int w, int h,
                   unsigned int thickness);

/**
 * @brief Show inventory of gems
 *
 * @param x Coordinate x of the North West corner of the inventory
 * @param y Coordinate y of the North West corner of the inventory
 * @param width Width of the inventory
 * @param gems Array of gems
 * @param gemsCount Number of gems
 */
void show_inventory(int x, int y, int width, Gem* gems, int gemsCount);

#endif  // __GRAPHIC_OVERLAY_H__
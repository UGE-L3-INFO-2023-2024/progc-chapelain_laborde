/**
 * @file GraphicOverlay.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Overlay graphic functions (mana bar)
 * @date 07-01-2024
 *
 */

#ifndef __GRAPHIC_OVERLAY_H__
#define __GRAPHIC_OVERLAY_H__

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

#endif  // __GRAPHIC_OVERLAY_H__
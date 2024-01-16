/**
 * @file GraphicOverlay.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Overlay graphic functions (mana bar)
 * @date 30-10-2023
 *
 */

#ifndef __GRAPHIC_OVERLAY_H__
#define __GRAPHIC_OVERLAY_H__

#include <MLV/MLV_color.h>

#include "Font.h"
#include "Mana.h"
#include "Stats.h"
#include "Window.h"

/*************/
/* Functions */
/*************/

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
void draw_mana_bar(ManaPool pool, int x, int y, int w, int h,
                   unsigned int thickness);

/**
 * @brief Show an error message when the player doesn't have enough mana.
 * The message is shown at the center of the given rectangle.
 * Of course, the rectangle is not shown, it's just used to center the text.
 *
 * @param x Coordinate x of the North West corner of the rectangle
 * @param y Coordinate y of the North West corner of the rectangle
 * @param w Width of the rectangle
 * @param h Height of the rectangle
 * @param mana_needed Mana needed to cast the spell
 * @param font Font to use
 * @param color Color of the text
 */
void draw_mana_error(int x, int y, int w, int h, int mana_needed, Font* font,
                     MLV_Color color);

/**
 * @brief Show the game over screen with the stats of the player
 *
 * @param map_window Window of the map
 * @param stats Stats of the player
 */
void draw_game_over_screen(SubWindow map_window, Stats stats);

#endif  // __GRAPHIC_OVERLAY_H__
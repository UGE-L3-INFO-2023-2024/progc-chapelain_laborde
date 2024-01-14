/**
 * @file Font.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Font management.
 * @date 07-01-2024
 *
 */

#ifndef __FONT_H__
#define __FONT_H__

#include <MLV/MLV_all.h>

typedef MLV_Font* Font;

/*************/
/* Functions */
/*************/

/**
 * @brief Load a font from a file.
 *
 * @param path Path to the font file.
 * @param size Size of the font.
 * @return Font loaded.
 */
Font Font_load(const char* path, int size);

/**
 * @brief Free a font.
 *
 * @param font Font to free.
 */
void Font_free(Font font);

#endif  // __FONT_H__
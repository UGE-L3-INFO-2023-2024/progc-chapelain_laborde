/**
 * @file Color.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#ifndef __COLOR_H__
#define __COLOR_H__

typedef unsigned short HSV_Color;  // 0 - 359 HSV color

/**
 * @brief Define a RGB color.
 *
 */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB_Color;

/**
 * @brief Convert a HSV color to a RGB color.
 *
 * @param color HSV color to convert.
 * @return RGB_Color color.
 */
RGB_Color Color_HSV_to_RGB(HSV_Color color);

/**
 * @brief Generate a random HSV color.
 *
 * @return HSV_Color color.
 */
HSV_Color Color_rand(void);

#endif  // __COLOR_H__
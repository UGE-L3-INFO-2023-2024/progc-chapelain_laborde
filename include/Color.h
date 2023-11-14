/**
 * @file Color.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __COLOR_H__
#define __COLOR_H__

typedef unsigned short Color;  // 0 - 359 HSV color

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

/**
 * @brief Convert a HSV color to a RGB color.
 *
 * @param color HSV color to convert.
 * @return RGB color.
 */
RGB HSV_to_RGB(Color color);

#endif  // __COLOR_H__
/**
 * @file Color.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Manage Generation of color HSV + conversion to RGB.
 * @date 14-11-2023
 *
 */

#include "Color.h"

#include <math.h>
#include <stdlib.h>

/* Convert HSV color to RGB color */
RGB_Color Color_HSV_to_RGB(HSV_Color color) {
    double v = 1;    // Brightness
    double s = 0.5;  // Saturation
    double c = v * s;
    double h = color / 60.0;
    double x = c * (1 - fabs(fmod(h, 2) - 1));
    double m = v - c;
    double rgb[3] = {0, 0, 0};

    int color_ranges[6] = {60, 120, 180, 240, 300, 360};
    double color_values[6][3] = {{c, x, 0}, {x, c, 0}, {0, c, x},
                                 {0, x, c}, {x, 0, c}, {c, 0, x}};

    for (int i = 0; i < 6; i++) {
        if (color <= color_ranges[i]) {
            rgb[0] = color_values[i][0];
            rgb[1] = color_values[i][1];
            rgb[2] = color_values[i][2];
            break;
        }
    }
    // We use unsigned char to store RGB values (0-255)
    return (RGB_Color){(unsigned char)((rgb[0] + m) * 255.0),
                       (unsigned char)((rgb[1] + m) * 255.0),
                       (unsigned char)((rgb[2] + m) * 255.0)};
}

/* Random Color generation */
HSV_Color Color_rand(void) {
    return rand() % 360;
}
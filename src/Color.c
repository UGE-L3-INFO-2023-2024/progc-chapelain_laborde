/**
 * @file Color.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Color.h"

#include <math.h>
#include <stdlib.h>

RGB_Color Color_HSV_to_RGB(HSV_Color color) {
    double v = 1;    // Brightness
    double s = 0.5;  // Saturation
    double c = v * s;
    int h = color / 60.0;
    double x = c * (1 - abs(h % 2 - 1));
    double m = v - c;
    double r, g, b;
    if (0 <= color && color <= 60) {
        r = c;
        g = x;
        b = 0;
    } else if (60 <= color && color <= 120) {
        r = x;
        g = c;
        b = 0;
    } else if (120 <= color && color <= 180) {
        r = 0;
        g = c;
        b = x;
    } else if (180 <= color && color <= 240) {
        r = 0;
        g = x;
        b = c;
    } else if (240 <= color && color <= 300) {
        r = x;
        g = 0;
        b = c;
    } else if (300 <= color && color <= 360) {
        r = c;
        g = 0;
        b = x;
    } else {
        r = 0;
        g = 0;
        b = 0;
    }
    return (RGB_Color){(r + m) * 255, (g + m) * 255, (b + m) * 255};
}

HSV_Color Color_rand(void) {
    return rand() % 360;
}
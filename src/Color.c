#include "Color.h"

#include <stdlib.h>

RGB HSV_to_RGB(Color color) {
    RGB rgb;
    int Hprime = color / 60;
    int X = 1 - abs(Hprime % 2 - 1);
    if (0 <= Hprime && Hprime < 1) {
        rgb = (RGB){1, X, 0};
    } else if (1 <= Hprime && Hprime < 2) {
        rgb = (RGB){X, 1, 0};
    } else if (2 <= Hprime && Hprime < 3) {
        rgb = (RGB){0, 1, X};
    } else if (3 <= Hprime && Hprime < 4) {
        rgb = (RGB){0, X, 1};
    } else if (4 <= Hprime && Hprime < 5) {
        rgb = (RGB){X, 0, 1};
    } else if (5 <= Hprime && Hprime < 6) {
        rgb = (RGB){1, 0, X};
    } else {
        rgb = (RGB){0, 0, 0};
    }
    return rgb;
}
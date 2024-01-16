/**
 * @file Gemstone.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage gemstone.
 * @date 14-11-2023
 *
 */

#include "Gemstone.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Utils.h"

/* Convert a gemstone to an element */
Element_Type Gemstone_get_element(Gemstone gemstone) {
    Element_Type element;
    int color = gemstone.color;
    if ((color >= 0 && color <= 30) || (color >= 330 && color < 360)) {
        element = PYRO;
    } else if (color >= 90 && color <= 150) {
        element = DENDRO;
    } else if (color >= 210 && color <= 270) {
        element = HYDRO;
    } else {
        element = NONE;
    }
    return element;
}

/* Generate a pure gemstone */
Gemstone Gemstone_init(int level) {
    Gemstone gemstone;
    do {
        gemstone.color = rand() % 360;
    } while (Gemstone_get_element(gemstone) == NONE);
    gemstone.level = level;
    gemstone.type = PURE;
    return gemstone;
}

/**
 * @brief Calculates the average of two angles.
 *
 * @details
 * This function takes two angles in degrees, converts them to Cartesian
 * coordinates, calculates the average of the coordinates, then converts the
 * average back to an angle. The result is in the range [0, 360).
 *
 * @param a The first angle in degrees.
 * @param b The second angle in degrees.
 * @return The average of the two angles, in the range [0, 360).
 */
static short _average_angle(int a, int b) {
    // Converts the angles to radians
    double a_rad = Utils_deg_to_rad(a);
    double b_rad = Utils_deg_to_rad(b);
    double a_x = cos(a_rad);
    double a_y = sin(a_rad);
    double b_x = cos(b_rad);
    double b_y = sin(b_rad);
    double avg_x = (a_x + b_x) / 2.0;
    double avg_y = (a_y + b_y) / 2.0;

    // Converts the average back to an angle
    double avg_rad = atan2(avg_y, avg_x);
    if (avg_rad < 0) {
        avg_rad += 2 * HOME_PI;
    }

    return (short)(avg_rad * 180.0 / HOME_PI);
}

/* Merge two gemstone */
bool Gemstone_merge(Gemstone *gem, const Gemstone *other) {
    if (gem->level != other->level) {
        return false;
    }
    gem->level += 1;
    gem->color = _average_angle(gem->color, other->color);
    // not same color = MIXED
    if (Gemstone_get_element(*gem) != Gemstone_get_element(*other)) {
        gem->type = MIXED;
    }
    return true;
}

/* Copy a gemstone */
Gemstone Gemstone_copy(const Gem *gemO) {
    return (Gemstone){
        .type = gemO->type,
        .color = gemO->color,
        .level = gemO->level,
    };
}

/* Copy a gemstone pointer */
Gemstone *Gemstone_copy_ptr(const Gem *gemO) {
    Gemstone *gem = malloc(sizeof(Gemstone));
    if (gem == NULL) {
        return NULL;
    }
    *gem = Gemstone_copy(gemO);
    return gem;
}

/* Compare two gemstone */
bool Gemstone_equal(Gemstone gemstone, Gemstone other) {
    return gemstone.type == other.type && gemstone.color == other.color &&
           gemstone.level == other.level;
}

/**
 * @file Gemstone.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage gemstone.
 * @date 14-11-2023
 *
 */

#include "Gemstone.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

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

/* Merge two gemstone */
bool Gemstone_merge(Gemstone *gem, Gemstone *other) {
    if (gem->level != other->level) {
        return false;
    }
    gem->level += 1;
    gem->color = (gem->color + other->color) / 2;
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

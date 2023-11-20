/**
 * @file Gemstone.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#include "Gemstone.h"

#include <assert.h>
#include <stdlib.h>

/* Convert a gemstone to an element */
Element Gemstone_get_element(Gemstone gemstone) {
    Element element;
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

/* Get the type of a gemstone */
GemType Gemstone_get_type(Gemstone gemstone) {
    if (Gemstone_get_element(gemstone) != NONE)
        return PURE;
    return MIXED;
}

/* Generate a pure gemstone */
Gemstone Gemstone_init() {
    Gemstone gemstone;
    do {
        gemstone.color = rand() % 360;
    } while (Gemstone_get_element(gemstone) == NONE);
    gemstone.level = 1;
    gemstone.multiplier = 1;
    return gemstone;
}

/* Merge two gemstone */
void Gemstone_merge(Gemstone *gemstone, Gemstone *other) {
    assert(gemstone->level != other->level);
    gemstone->level += 1;
    gemstone->color = (gemstone->color + other->color) / 2;
    if (Gemstone_get_type(*gemstone) == MIXED) {
        int nb = rand() % 10;
        if (nb == 9) {
            gemstone->multiplier *= 4;
        } else {
            gemstone->multiplier *= 2;
        }
    }
    free(other);
}
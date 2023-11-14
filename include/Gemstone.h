/**
 * @file Gemstone.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __GEMSTONE_H__
#define __GEMSTONE_H__

#include "Color.h"
#include "Element.h"

typedef enum {
    PURE,
    MIXED,
} GemType;

typedef struct {
    Color color;
    unsigned int level;
    Element *element;
    GemType type;
} Gem, Gemstone;

/**
 * @brief Gemstone color to type
 *
 * @param color Color of the gemstone
 * @return GemType Type of the gemstone
 */
GemType color_to_gemtype(int color);

/**
 * @brief Create a pure Gemstone object
 *
 * @return Gemstone Gemstone created
 */
Gemstone gemstone_create();

/**
 * @brief Merge two gemstone
 *
 * @param gemstone Gemstone to merge and to be modified
 * @param other Gemstone to merge
 */
void gemstone_merge(Gemstone *gemstone, Gemstone *other);

#endif  // __GEMSTONE_H__

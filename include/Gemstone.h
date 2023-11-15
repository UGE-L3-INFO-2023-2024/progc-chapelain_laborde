/**
 * @file Gemstone.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#ifndef __GEMSTONE_H__
#define __GEMSTONE_H__

#include "Color.h"
#include "Element.h"

/**
 * @brief Type of gemstone
 *
 */
typedef enum {
    PURE,
    MIXED,
} GemType;

/**
 * @brief Define a gemstone.
 *
 */
typedef struct {
    HSV_Color color;
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
GemType Gemstone_from_color(int color);

/**
 * @brief Create a pure Gemstone object
 *
 * @return Gemstone Gemstone created
 */
Gemstone Gemstone_init();

/**
 * @brief Merge two gemstone
 *
 * @param gemstone Gemstone to merge and to be modified
 * @param other Gemstone to merge
 */
void Gemstone_merge(Gemstone *gemstone, Gemstone *other);

#endif  // __GEMSTONE_H__

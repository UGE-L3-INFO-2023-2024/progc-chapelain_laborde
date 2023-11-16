/**
 * @file Gemstone.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
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
    unsigned short multiplier;
} Gem, Gemstone;

/**
 * @brief Convert a gemstone to an element
 *
 * @param gemstone Gemstone to convert
 * @return Element of the gemstone
 */
Element Gemstone_get_element(Gemstone gemstone);

/**
 * @brief Get the type of a gemstone
 *
 * @param gemstone Gemstone to get the type
 * @return GemType of the gemstone
 */
GemType Gemstone_get_type(Gemstone gemstone);

/**
 * @brief Create a pure Gemstone object with random color.
 *
 * @return Gemstone Pure gemstone created.
 */
Gemstone Gemstone_init();

/**
 * @brief Merge two gemstone
 *
 * @param gemstone Gemstone to merge and to be modified
 * @param other Gemstone to merge
 *
 * @return int 1 if merge is done, 0 otherwise
 */
void Gemstone_merge(Gemstone *gemstone, Gemstone *other);

#endif  // __GEMSTONE_H__

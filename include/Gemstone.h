/**
 * @file Gemstone.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage gemstone.
 * @date 30-10-2023
 *
 */

#ifndef __GEMSTONE_H__
#define __GEMSTONE_H__

#include <stdbool.h>

#include "Color.h"
#include "Element.h"

/**************/
/* Structures */
/**************/

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
    GemType type;
    HSV_Color color;
    unsigned int level;
} Gem, Gemstone;

/*************/
/* Functions */
/*************/

/**
 * @brief Convert a gemstone to an element
 *
 * @param gemstone Gemstone to convert
 * @return Element of the gemstone
 */
Element_Type Gemstone_get_element(Gemstone gemstone);

/**
 * @brief Create a pure Gemstone object with random color.
 *
 * @param level Level of the gemstone.
 * @return Pure gemstone created.
 */
Gemstone Gemstone_init(int level);

/**
 * @brief Merge two gemstone
 *
 * @param gemstone Gemstone to merge and to be modified
 * @param other Gemstone to merge
 *
 * @return true if the merge is possible
 */
bool Gemstone_merge(Gemstone *gemstone, const Gemstone *other);

/**
 * @brief Copy a gem.
 *
 * @param projO gem to copy.
 * @return Deep Copied gem.
 */
Gemstone Gemstone_copy(const Gem *gemO);

/**
 * @brief Copy a gem and malloc a new one.
 * If malloc fail, return NULL.
 *
 * @param gemO gem to copy.
 * @return Gemstone* Deep Copied gem (new malloc gem).
 */
Gemstone *Gemstone_copy_ptr(const Gem *gemO);

/**
 * @brief Compare two gemstone and return true if they are equals.
 * Two gemstone are equals if they have the same color, same type
 * and the same level.
 *
 * @param gemstone 1st gemstone to compare.
 * @param other second one.
 * @return true if the two gemstone are equals.
 */
bool Gemstone_equal(Gemstone gemstone, Gemstone other);

#endif  // __GEMSTONE_H__

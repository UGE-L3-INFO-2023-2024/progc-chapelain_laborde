/**
 * @file Gemstone.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 16-11-2023
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
Element Gemstone_get_element(Gemstone gemstone);

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
bool Gemstone_merge(Gemstone *gemstone, Gemstone *other);

#endif  // __GEMSTONE_H__

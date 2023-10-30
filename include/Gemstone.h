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

typedef enum {
    PURE,
    MIXED,
} GemType;

typedef struct {
    Color color;
    unsigned int level;
    GemType type;
} Gem, Gemstone;

#endif  // __GEMSTONE_H__
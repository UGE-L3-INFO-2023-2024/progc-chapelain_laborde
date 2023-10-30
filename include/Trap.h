/**
 * @file Trap.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __TRAP_H__
#define __TRAP_H__

#include "Gemstone.h"
#include "./tools/Utils.h"

typedef struct {
    Coord_i coord;
    Gem* gem;
} Trap;

#endif  // __TRAP_H__
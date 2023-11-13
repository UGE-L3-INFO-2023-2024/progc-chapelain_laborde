/**
 * @file Tower.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __TOWER_H__
#define __TOWER_H__

#include <sys/time.h>

#include "Gemstone.h"
#include "Utils.h"

typedef struct {
    Gem* gem;
    // timeval install_gem;
    Coord_i coord;
} Tower;

#endif  // __TOWER_H__
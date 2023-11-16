/**
 * @file Tower.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-16
 *
 */

#ifndef __TOWER_H__
#define __TOWER_H__

#include <time.h>

#include "Gemstone.h"
#include "Utils.h"

typedef struct {
    Gem* gem;
    // time install_gem;
    Coord_i coord;
} Tower;

/**
 * @brief Create a tower object
 *
 * @param gem Gemstone to install in the tower
 * @param coord Coord of the tower
 * @return Tower Tower created
 */
Tower Tower_init(Gem* gem, Coord_i coord);

#endif  // __TOWER_H__
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
    struct timespec available_at;
    Coord_i coord;
} Tower;

/**
 * @brief Create a tower object
 *
 * @param coord Coord of the tower
 * @return Tower Tower created
 */
Tower Tower_init(Coord_i coord);

/**
 * @brief Add gem to a tower
 *
 * @param tower The tower will receive the gem
 * @param gem The gem to add
 * @return int 1 if success, 0 if tower, gem or both are NULL
 */
int Tower_add_gem(Tower* tower, Gem* gem);

/**
 * @brief Extract gem from a tower
 *
 * @param tower The tower will give the gem
 * @return Gem* The gem extracted
 */
Gem* Tower_extract_gem(Tower* tower);

#endif  // __TOWER_H__
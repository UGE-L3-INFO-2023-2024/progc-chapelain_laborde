/**
 * @file Tower.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage tower. (creation, gems)
 * @date 30-10-2023
 *
 */

#ifndef __TOWER_H__
#define __TOWER_H__

#include <stdbool.h>
#include <time.h>

#include "Gemstone.h"
#include "Utils.h"

#define TOWER_SHOT_COOLDOWN_MS 500
#define TOWER_GEM_COOLDOWN_MS 2000
#define TOWER_RANGE 3

/**************/
/* Structures */
/**************/

typedef struct {
    bool has_gem;
    Gem gem;
    struct timespec available_at;
    Coord_i coord;
} Tower;

/*************/
/* Functions */
/*************/

/**
 * @brief Create a tower object at the given coordinates.
 * The tower is initialized with no gem and available to shoot.
 *
 * @param coord Coord of the tower
 * @return Tower created
 */
Tower Tower_init(Coord_i coord);

/**
 * @brief Add gemstone to a tower and set the cooldown.
 * The gemstone is copied. The gemstone is added only if the tower has no gem.
 * The cooldown is set to TOWER_GEM_COOLDOWN_MS.
 *
 * @param tower The tower will receive the gem (if it has no gem)
 * @param gem The gem to add to the tower
 * @return if the gem has been added to the tower
 */
bool Tower_add_gem(Tower* tower, const Gem* gem);

/**
 * @brief Extract gem from a tower.
 * The gemstone is copied. The gemstone is extracted only if the tower has a
 * gem, otherwise nothing is done and false is returned.
 *
 * @param tower The tower from which the gem will be extracted
 * @param gem pointer to store the gem extracted
 * @return if the gem has been extracted
 */
bool Tower_extract_gem(Tower* tower, Gem* gem);

#endif  // __TOWER_H__
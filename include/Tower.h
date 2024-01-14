/**
 * @file Tower.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage tower. (creation, gems)
 * @date 16-11-2023
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
 * @return if the gem has been added
 */
bool Tower_add_gem(Tower* tower, Gem* gem);

/**
 * @brief Extract gem from a tower
 *
 * @param tower The tower will give the gem
 * @param gem pointer to store the gem.
 * @return if the gem has been extracted
 */
bool Tower_extract_gem(Tower* tower, Gem* gem);

#endif  // __TOWER_H__
/**
 * @file Path.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 11-11-2023
 *
 */

#ifndef __PATH_H__
#define __PATH_H__

#define MIN_TURN 7
#define MIN_LEN 75

#include <stdbool.h>

#include "DynamicArray.h"
#include "Map.h"

/*************/
/* Functions */
/*************/

/**
 * @brief Generate a path for the map.
 *
 * @param map Map to generate the path.
 * @param da DynamicArray to store the turns.
 * @return if the path is generated.
 *  (can be too short or too few turns)
 */
bool Path_gen(Map* map, DynamicArray* da);

#endif

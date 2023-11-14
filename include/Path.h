/**
 * @file Path.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 11/11/2023
 *
 */

#ifndef __PATH_H__
#define __PATH_H__

#define MIN_TURN 7
#define MIN_LEN 75

#include <stdbool.h>

#include "Map.h"
#include "Utils.h"

bool Path_gen(Map* map);

#endif
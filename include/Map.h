/**
 * @file Map.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>

#include "./tools/Utils.h"
#include "Mana.h"
#include "Mob.h"
#include "Tower.h"
#include "Trap.h"

#define MAP_WIDTH 28
#define MAP_HEIGHT 22

typedef struct {
    Coord_i coord;
    bool is_path;
    union {
        Tower* tower;
        Trap* trap;
    };
} Cell;

typedef struct {
    Cell cells[MAP_HEIGHT][MAP_WIDTH];
    List mobs;
    Tower* towers;
    Trap* traps;
    ManaPool mana;
} Map;

#endif  // __MAP_H__
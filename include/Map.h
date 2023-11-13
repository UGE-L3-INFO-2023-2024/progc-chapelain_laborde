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

#include "Mana.h"
#include "Mob.h"
#include "Tower.h"
#include "Trap.h"
#include "Utils.h"

#define MAP_WIDTH 28
#define MAP_HEIGHT 22

typedef struct {
    bool is_path;
    Coord_i coord;
    union {
        Tower* tower;
        Trap* trap;
    };
} Cell;

typedef struct {
    Cell board[MAP_HEIGHT][MAP_WIDTH];
    // List mobs; coms to avoid warning
    Tower* towers;
    Trap* traps;
    ManaPool mana;
} Map;

Map Map_init(void);
void Map_init_board(Map* map);
Cell Map_init_cell(Coord_i coord);
void Map_print(Map* map);

#endif  // __MAP_H__
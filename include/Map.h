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
    Coord_i nest;
    Coord_i castle;
    Mob mobs;
    Tower* towers;
    Trap* traps;
} Map;

/**
 * @brief Initialize a Map.
 *
 * @return Map map.
 */
Map Map_init(void);

/**
 * @brief Initialize the board of a Map.
 *
 * @param map Map to initialize.
 */
void Map_init_board(Map* map);

/**
 * @brief Initialize a Cell.
 *
 * @param coord Coord of the Cell.
 * @return Cell cell.
 */
Cell Map_init_cell(Coord_i coord);

/**
 * @brief Print a Map.
 *
 * @param map Map to print.
 */
void Map_print(Map* map);

/**
 * @brief Check thre is a path in the neighbour of the given cell.
 *
 * @param map Map to check.
 * @param pos Position of the cell.
 * @param ignore Direction to ignore. (in case of a turn)
 */
Direction Map_got_next_path(Map* map, Coord_i pos, Direction ignore);

#endif  // __MAP_H__
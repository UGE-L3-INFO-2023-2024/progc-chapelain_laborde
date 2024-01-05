/**
 * @file Map.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30-10-2023
 *
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>

#include "DynamicArray.h"
#include "Error.h"
#include "Tower.h"
#include "Trap.h"
#include "Utils.h"
#include "Wave.h"

#define MAP_WIDTH 28
#define MAP_HEIGHT 22

/**************/
/* Structures */
/**************/

typedef struct {
    bool is_path;
    bool have_tower;
} Cell;

typedef struct {
    Cell board[MAP_HEIGHT][MAP_WIDTH];
    Coord_i nest;
    Coord_i castle;
    Wave mobs;
    DynamicArray towers;
    DynamicArray traps;
    DynamicArray projs;
} Map;

/*************/
/* Functions */
/*************/

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
 * @brief Initialize the towers of a Map.
 *
 * @param map Map to initialize.
 * @return Error if there is a allocation error.
 */
Error Map_init_towers(Map* map);

/**
 * @brief Initialize the projs of a Map.
 *
 * @param map Map to initialize.
 * @return Error if there is a allocation error.
 */
Error Map_init_projs(Map* map);

/**
 * @brief Add a tower to a Map.
 *
 * @param map Map to modifiy.
 * @param tower Tower to add.
 * @return Error of allocation. (realloc of towers)
 */
Error Map_add_tower(Map* map, Tower tower);

/**
 * @brief Get the tower at a coord.
 *
 * @param map Map to look in.
 * @param coord Coord of the tower.
 * @return Tower* pointer to the tower. NULL if not found.
 * (can be change after realloc do not store)
 *
 */
Tower* Map_get_tower(Map* map, Coord_i coord);

/**
 * @brief Make all towers shoot if possible.
 *
 * @param map Map to modifiy. (tower, projs, mobs)
 */
void Map_towers_shoot(Map* map);

/**
 * @brief Make all projs move.
 *
 * @param map Map to modifiy. (projs, mobs)
 */
void Map_actualise_proj(Map* map);

/**
 * @brief Print a Map. (debug function)
 *
 * @param map Map to print.
 */
void Map_print(Map* map);

#endif  // __MAP_H__
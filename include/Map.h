/**
 * @file Map.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the map.
 * (init, towers shooting, projs moving & damage, free)
 * @date 30-10-2023
 *
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>

#include "DynamicArray.h"
#include "Error.h"
#include "Stats.h"
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

/**
 * @brief Map of the game.
 *
 */
typedef struct {
    Cell board[MAP_HEIGHT][MAP_WIDTH];  // The board is a matrix of Cell
    Coord_i nest;                       // The nest is the start of the path
    Coord_i castle;                     // The castle is the end of the path
    Wave mobs;                          // The mobs are the enemies of the game
    DynamicArray map_turns;  // This DA represents the turns of the path
    DynamicArray towers;     // This DA represents the towers on the map
    DynamicArray traps;      // This DA represents the traps on the map
    DynamicArray projs;      // This DA represents the projectiles on the map
} Map;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a Map.
 *
 * @details
 * The board is initialized with fields of cell at false.
 * The towers are initialized with _init_towers.
 * The projs are initialized with _init_projs.
 * The mobs are initialized with Wave_init.
 * The nest and castle are set to (-1, -1).
 * The towers and projs are initialized with DA_init.
 *
 * @param map Map to initialize.
 * @return Error of allocation. (towers, projs, waves)
 */
Error Map_init(Map* map);

/**
 * @brief Initialize the board of a Map.
 *
 * @details
 * The board is initialized with fields of cell at false.
 *
 * @param map Map to initialize.
 */
void Map_init_board(Map* map);

/**
 * @brief Add a tower to a Map.
 *
 * @details
 * The tower is added to the towers DA and the cell is set to posses a tower.
 *
 * @param map Map to modifiy.
 * @param tower Tower to add.
 * @return Error of allocation. (realloc of towers)
 */
Error Map_add_tower(Map* map, Tower tower);

/**
 * @brief Get the tower at a given coordinate.
 *
 * @param map Map to look in.
 * @param coord Coord of the tower.
 * @return Tower* pointer to the tower. NULL if not found.
 * @warning Can be change after realloc do not store
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
 * @details
 * The projs are moved with their speed in their direction.
 * If the proj is on a mob, the mob take damage.
 * If the proj is out of the map, it is removed.
 *
 * @param map Map to modifiy. (projs, mobs)
 * @param stats Stats modifiy by the projs.
 */
void Map_actualise_proj(Map* map, Stats* stats);

/**
 * @brief Print a Map in terminal.
 *
 * @details
 * The board is printed with '#' for path and '*' for field.
 * This function print only the path of the map.
 * It's print in the standard output.
 *
 * @warning This function is only for debug.
 *
 * @param map Map to print.
 */
void Map_print(Map* map);

/**
 * @brief Free a Map and all its fields.
 * (towers, projs, mobs)
 *
 * @param map Map to free.
 */
void Map_free(Map* map);

#endif  // __MAP_H__
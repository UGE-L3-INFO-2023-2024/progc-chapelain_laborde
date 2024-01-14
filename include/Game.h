/**
 * @file Game.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief This file contains the Game structure and its functions. It's the
 * main module to run the game.
 * @date 09-01-2024
 *
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "Button.h"
#include "Error.h"
#include "Event.h"
#include "Inventory.h"
#include "Map.h"
#include "Stats.h"
#include "Window.h"

/**************/
/* Structures */
/**************/

/**
 * @brief Structure representing the game.
 * It contains the map, the inventory, the mana pool, the windows and the
 * buttons.
 *
 */
typedef struct {
    bool has_started;     // Tells if the 1st wave can go;
    Map map;              // The map is where the game is played
    Inventory inventory;  // The inventory contains mainly the gems
    ManaPool mana_pool;   // The mana pool is the mana available to the player
    struct {              // The windows are the different parts of the window
        Window main;
        SubWindow map;
        SubWindow inventory;
    } window;
    ButtonTab buttons;  // The buttons of the game (inventory and map)
    Stats stats;        // The stats of the game
} Game;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize the game.
 *
 * @param game Game to initialize.
 * @return Error due to allocation of the game.
 */
Error Game_Init(Game* game);

/**
 * @brief Draw the game.
 *
 * @param game Game to draw.
 */
void Game_draw(Game* game);

/**
 * @brief Manange keyboard events.
 *
 * @param game Game to manage.
 * @param event Event to manage.
 */
void Game_action(Game* game, Event event);

/**
 * @brief Update Towers, Projectiles, Wave.
 *
 * @param game Game to update.
 * @return defeat
 */
bool Game_update_all(Game* game);

/**
 * @brief Run the game. It's the main loop of the game.
 *
 * @param game Game to run.
 * @return Error due to the game.
 */
Error Game_run(Game* game);

/**
 * @brief Free the game.
 *
 * @param game Game to free. The game pointer is set to NULL.
 */
void Game_free(Game* game);

#endif  // __GAME_H__
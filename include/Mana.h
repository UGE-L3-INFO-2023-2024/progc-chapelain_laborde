/**
 * @file Mana.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the Manapool (Init, bying, cost, upgrade).
 * @date 30-10-2023
 *
 */

#ifndef __MANA_H__
#define __MANA_H__

#include <stdbool.h>

#define MANA_START 150
#define MANA_ON_KILL_PERCENT 0.1
#define MANA_ON_TP_PERCENT 0.15

/**************/
/* Structures */
/**************/

typedef struct {
    unsigned int level;
    unsigned int mana_real;
    unsigned int mana_max;
} ManaPool;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a ManaPool.
 *
 * @return ManaPool mana.
 */
ManaPool Mana_pool_init(void);

/**
 * @brief Calculate the max mana of a level.
 *
 * @param level Level of the ManaPool.
 * @return int max mana.
 */
int Mana_max(int level);

/**
 * @brief Check if a ManaPool can be upgraded.
 *
 * @param pool ManaPool to check.
 * @return true if can be upgraded.
 * @return false otherwise.
 */
bool Mana_pool_can_be_upgrade(ManaPool pool);

/**
 * @brief Upgrade a ManaPool.
 *
 * @param pool ManaPool to upgrade.
 * @return true if success.
 * @return false otherwise.
 */
bool Mana_pool_upgrade(ManaPool* pool);

/**
 * @brief Check if a ManaPool can buy something and buy it.
 * The price is substracted from the mana_real.
 *
 * @param pool ManaPool to check.
 * @param price Price of the item.
 * @return true if can buy,
 * @return false otherwise.
 */
bool Mana_buy(ManaPool* pool, int price);

/**
 * @brief Add mana to a ManaPool.
 *
 * @param pool ManaPool to add mana.
 * @param price gain of mana.
 */
void Mana_gain(ManaPool* pool, int price);

/**
 * @brief Calculate the mana gain on mob death.
 *
 * @param mob_max_hp Max hp of the mob.
 * @param level_mana Level of the mana pool.
 * @return gain of mana.
 */
int Mana_gain_mob_death(int mob_max_hp, int level_mana);

/**
 * @brief Calculate the mana cost of a tp mob.
 *
 * @param mob_max_hp Max hp of the mob.
 * @param level_mana Level of the mana pool.
 * @return cost of mana.
 */
int Mana_cost_mob_tp(int mob_max_hp, int level_mana);

/**
 * @brief Calculate the cost of a tower.
 * The cost is calculated with the number of towers already placed.
 * The number of towers start at 0.
 * If the number of towers is < 0, return -1
 *
 * @param nb_towers Number of towers already placed.
 * @return int cost.
 */
int Mana_tower_cost(int nb_towers);

/**
 * @brief Calculate the mana gain when skiping to the next wave.
 *
 * @param max_mana Max mana of the mana pool.
 * @param sec Seconds of the wave gain.
 * @return gain of mana.
 */
int Mana_gain_skip_wave(int max_mana, int sec);

/**
 * @brief Calculate the cost of a gem.
 * The cost is calculated with the level of the gem.
 * The level start at 1.
 * If the level is <= 0, return -1.
 *
 * @param gem_level Level of the gem.
 * @return int cost.
 */
int Mana_gem_cost(int gem_level);

#endif  // __MANA_H__
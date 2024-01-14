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

/**
 * @brief Define a ManaPool.
 *
 * @details A ManaPool is defined by his level, his real mana and his max mana.
 * The real mana is the mana that can be used to buy something.
 * The max mana is the maximum mana that the ManaPool can have.
 * The level is the level of the ManaPool and it's used to calculate the max
 * mana and to not depass it.
 *
 */
typedef struct {
    unsigned int level;
    unsigned int mana_real;
    unsigned int mana_max;
} ManaPool;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a ManaPool with the MANA_START constant.
 * The level is set to 0.
 * The max mana is calculated with the level.
 * @see Mana_max for the calculation.
 *
 * @return ManaPool mana.
 */
ManaPool Mana_pool_init(void);

/**
 * @brief Calculate the max mana of a level. The level start at 0.
 *
 * @param level Level of the ManaPool.
 * @return int max mana.
 * @warning Don't use this function with a level < 0.
 */
int Mana_max(int level);

/**
 * @brief Check if a ManaPool can be upgraded.
 *
 * @details A ManaPool can be upgraded if the real mana is >= to the price of
 * the upgrade. The price is calculated with the level of the ManaPool.
 *
 * @param pool ManaPool to check.
 * @return true if can be upgraded.
 */
bool Mana_pool_can_be_upgrade(ManaPool pool);

/**
 * @brief Upgrade a ManaPool if possible.
 *
 * @see Mana_pool_can_be_upgrade for the condition.
 *
 * @param pool ManaPool to upgrade.
 * @return true if success.
 */
bool Mana_pool_upgrade(ManaPool* pool);

/**
 * @brief Check if a ManaPool can buy something and buy it.
 * The price is substracted from the mana_real.
 *
 * @param pool ManaPool to check.
 * @param price Price of the item.
 * @return true if can buy.
 */
bool Mana_buy(ManaPool* pool, int price);

/**
 * @brief Add mana to a ManaPool.
 *
 * @details The mana is added to the real mana.
 * If the real mana is > to the max mana, the real mana is set to the max mana.
 *
 * @param pool ManaPool to add mana.
 * @param gain gain of mana.
 */
void Mana_gain(ManaPool* pool, int gain);

/**
 * @brief Calculate the mana gain on mob death.
 *
 * @details
 * The gain is calculated with the max hp of the mob and the level of the mana
 * pool. The gain is a percentage of the max hp.
 *
 * @param mob_max_hp Max hp of the mob.
 * @param level_mana Level of the mana pool.
 * @return gain of mana.
 */
int Mana_gain_mob_death(int mob_max_hp, int level_mana);

/**
 * @brief Calculate the mana cost of a mob banish.
 *
 * @details
 * The cost is calculated with the max hp of the mob and the level of the mana
 * pool. The cost is a percentage of the max hp.
 *
 * @param mob_max_hp Max hp of the mob.
 * @param level_mana Level of the mana pool.
 * @return cost of mana.
 */
int Mana_cost_mob_banish(int mob_max_hp, int level_mana);

/**
 * @brief Calculate the cost of a tower.
 * The cost is calculated with the number of towers already placed.
 *
 * @details
 * The number of towers start at 0.
 *
 * @param nb_towers Number of towers already placed.
 * @return int cost.
 * @warning If the number of towers is < 0, return -1
 */
int Mana_tower_cost(int nb_towers);

/**
 * @brief Calculate the mana gain when skiping to the next wave.
 *
 * @details
 * The gain is calculated with the max mana of the mana pool and the seconds
 * before the next wave.
 *
 * @param max_mana Max mana of the mana pool.
 * @param sec Seconds of the wave gain.
 * @return gain of mana.
 */
int Mana_gain_skip_wave(int max_mana, int sec);

/**
 * @brief Calculate the cost of a gem.
 * The cost is calculated with the level of the gem.
 *
 * @param gem_level Level of the gem.
 * @return int cost.
 *
 * @warning The level start at 1.
 * If the level is <= 0, return -1.
 */
int Mana_gem_cost(int gem_level);

#endif  // __MANA_H__
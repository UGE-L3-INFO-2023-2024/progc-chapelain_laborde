/**
 * @file Mana.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __MANA_H__
#define __MANA_H__

#include <stdbool.h>

typedef struct {
    unsigned int level;
    unsigned int mana_real;
    unsigned int mana_max;
} ManaPool;

#define MANA_START 150

/**
 * @brief Initialize a ManaPool.
 *
 * @return ManaPool mana.
 */
ManaPool Mana_init(void);

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

#endif  // __MANA_H__
/**
 * @file Mana.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#ifndef __MANA_H__
#define __MANA_H__

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

#endif  // __MANA_H__
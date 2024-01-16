/**
 * @file Stats.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the stats.
 * @date 30-10-2023
 *
 */

#ifndef __STATS_H__
#define __STATS_H__

#include <stdint.h>

/**************/
/* Structures */
/**************/

typedef struct {
    uint64_t score;
    uint64_t total_damage;
    uint64_t mana_lost;
    uint64_t last_wave;
    uint64_t mobs_killed;
    uint64_t timeplayed;
} Stats;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize the stats.
 *
 * @return Stats stats.
 */
Stats Stats_init(void);

#endif  // __STATS_H__
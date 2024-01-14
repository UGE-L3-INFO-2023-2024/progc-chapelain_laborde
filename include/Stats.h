/**
 * @file Stats.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the stats.
 * @date 30/10/2023
 *
 */

#ifndef __STATS_H__
#define __STATS_H__

/**************/
/* Structures */
/**************/

typedef struct {
    unsigned int score;
    unsigned int total_damage;
    unsigned int last_wave;
    unsigned int mobs_killed;
    unsigned int timeplayed;
} Stats;

#endif  // __STATS_H__
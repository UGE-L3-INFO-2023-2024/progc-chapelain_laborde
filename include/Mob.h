/**
 * @file Mob.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#ifndef __MOB_H__
#define __MOB_H__

#include <stdbool.h>

#include "Color.h"
#include "Element.h"
#include "Utils.h"

#define MOB_CONST_HP 1

typedef struct {
    unsigned int current_hp;
    unsigned int max_hp;
    double speed;
    Coord_f pos;
    HSV_Color color;
    Element apply_elem;
    Coord_f going;
} Mob;

/**
 * @brief Initialize a mob.
 *
 * @param wave Number of the wave.
 * @return Mob Mob.
 */
Mob Mob_init_basic(int wave, Coord_f start);

/**
 * @brief Initialize a mob with the double of speed.
 *
 * @param wave Number of the wave.
 * @return Mob Mob.
 */
Mob Mob_init_fast(int wave, Coord_f start);

/**
 * @brief Initialize a boss.
 *
 * @param wave Number of the wave.
 * @return Mob Mob.
 */
Mob Mob_init_boss(int wave, Coord_f start);

/**
 * @brief Calculate the max hp of a mob.
 *
 * @param wave Number of the wave.
 * @param boss If the mob is a boss.
 * @return int max hp.
 */
int Mob_max(int wave, bool boss);

/**
 * @brief Move the mob in the given direction.
 *
 * @param mob Mob to move.
 * @param dir Direction to move the mob.
 */
void Mob_next_step(Mob *mob, Direction dir);

#endif  // __MOB_H__
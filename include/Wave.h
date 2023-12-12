/**
 * @file Wave.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 12-12-2023
 *
 */

#ifndef _WAVE_H_
#define _WAVE_H_

#include "DynamicArray.h"
#include "Mob.h"

/**
 * @brief Make the move move even in the corner.
 *
 * @param mob Mob to move
 * @param da DynamicArray of the map.
 */
void Wave_next_step_unit(Mob *mob, DynamicArray *da);

/**
 * @brief Tells the mob were to go next.
 *
 * @param mob Mob to move.
 * @param da DynamicArray of the map.
 */
void Wave_next_going_unit(Mob *mob, DynamicArray *da);

#endif  // _WAVE_H_
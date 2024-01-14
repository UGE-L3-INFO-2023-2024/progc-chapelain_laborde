/**
 * @file Wave.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to handle wave of mob.
 * @date 30-10-2023
 *
 */

#ifndef _WAVE_H_
#define _WAVE_H_

#include <time.h>

#include "DynamicArray.h"
#include "Error.h"
#include "Mob.h"

#define TIME_NEXT_WAVE 35000

/**************/
/* Structures */
/**************/

typedef enum {
    BASIC,
    MASS,
    FAST,
    BOSS,
    UNKNOW,
} Type_wave;

typedef struct {
    DynamicArray mob_list;
    struct timespec next_mob;
    struct timespec next_wave;
    Type_wave type_mob;
    int nb_mob_wave;
    int nb_wave;
} Wave;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a Wave.
 *
 * @param wave Wave to initialize.
 * @return Error
 */
Error Wave_init(Wave *wave);

/**
 * @brief Spawn the next mob of the wave according to time.
 *
 * @param wave Wave to spawn.
 * @param start Start of the path.
 * @return Error
 */
Error Wave_spawn_next(Wave *wave, Coord_f start);

/**
 * @brief Skip to the next wave if all the mob of acutal wave are spawned.
 *
 * @param wave Wave to update
 * @return second gain compare to next wave.
 */
int Wave_skip_to_next(Wave *wave);

/**
 * @brief Move the mob to the next step. And aplly dendro damage.
 *
 * @param mob Pointer to the mob.
 * @param da DynamicArray of the path.
 * @param dmg Pointer to fill with the damage to apply to the mob.
 * @return if the mob is tp in the spawn.
 *
 */
bool Wave_next_step_unit(Mob *mob, DynamicArray *da, int *dmg);

#endif  // _WAVE_H_
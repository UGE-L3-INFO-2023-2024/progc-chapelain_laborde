/**
 * @file Wave.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 12-12-2023
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
 * @brief Spawn the next mob of the wave.
 *
 * @param wave Wave to spawn.
 * @param start Start of the path.
 * @return Error
 */
Error Wave_spawn_next(Wave *wave, Coord_f start);

/**
 * @brief Move the wave to the next step.
 *
 * @param wave Wave to move.
 * @param turns Turns of the path.
 */
void Wave_next_step(Wave *wave, DynamicArray *turns);

#endif  // _WAVE_H_
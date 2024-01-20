/**
 * @file Mob.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage mobs.
 * (init, move, element application and dendro tick damage)
 * @date 30-10-2023
 *
 */

#ifndef __MOB_H__
#define __MOB_H__

#include <stdbool.h>

#include "Color.h"
#include "Element.h"
#include "Utils.h"

#define MOB_CONST_HP 70

/**************/
/* Structures */
/**************/

/**
 * @brief Define a mob with his current hp, max hp, speed, position, color,
 * element and going.
 *
 */
typedef struct {
    int current_hp;
    int max_hp;
    double speed;
    Coord_f pos;
    HSV_Color color;
    Element elem;
    Coord_f going;
} Mob;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a mob. The mob is initialized with the wave number, the
 * position and the speed.
 *
 * @details Color is initialized with Color_rand. Element is initialized with
 * Elem_init. Going is initialized with (-1, -1). This going value are used to
 * know if the mob is initialized or not.
 * The speed is initialized with 1/FRAMERATE.
 *
 * @param wave Number of the wave to initialize the mob.
 * @return Mob initialized.
 */
Mob Mob_init_basic(int wave, Coord_f start);

/**
 * @brief Initialize a mob with the double of speed.
 *
 * @see Mob_init_basic for more details.
 *
 * @param wave Number of the wave.
 * @return Mob Mob.
 */
Mob Mob_init_fast(int wave, Coord_f start);

/**
 * @brief Initialize a boss. The mob is initialized with the wave number, the
 * position and the speed.
 *
 * @see Mob_init_basic for more details.
 *
 * @details The mob is initialized with twelve times the hp of a basic mob.
 *
 * @param wave Number of the wave.
 * @return Mob Mob.
 */
Mob Mob_init_boss(int wave, Coord_f start);

/**
 * @brief Calculate the max hp of a mob.
 *
 * @details The max hp is calculated with the wave number and if the mob is a
 * boss. The boss are twelve times stronger than a basic mob.
 *
 * @param wave Number of the wave.
 * @param boss If the mob is a boss.
 * @return int max hp.
 */
int Mob_max(int wave, bool boss);

/**
 * @brief Move the mob in the given direction and apply dendro tick damage.
 *
 * @details The mob is moved with his speed in the given direction. If the mob
 * is on a dendro tile, the mob take damage. The damage is calculated with the
 * level of the dendro tile.
 *
 * @param mob Mob to move.
 * @param dir Direction to move the mob.
 * @param dmg Pointer to fill with the damage to apply to the mob.
 */
void Mob_next_step(Mob* mob, Direction dir, int* dmg);

/**
 * @brief Apply the element type to the mob.
 *
 * @param mob Mob to apply the element.
 * @param type Type of the element.
 */
void Mob_apply_element(Mob* mob, Element_Type type);

#endif  // __MOB_H__
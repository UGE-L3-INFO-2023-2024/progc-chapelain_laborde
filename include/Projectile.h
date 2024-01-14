/**
 * @file Projectile.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage projectile (init, move, damage).
 * @date 30-10-2023
 *
 */

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Color.h"
#include "Gemstone.h"
#include "Mob.h"

#define PROJ_SPEED 3
#define PROJ_CONST_DMG 5

/**************/
/* Structures */
/**************/

/**
 * @brief Define a projectile with his gemstone, level, speed, position and
 * target.
 * @details The projectile is a gemstone with a level, a speed, a position and
 * a target. The speed is the number of pixel the projectile will move at each
 * step. The position is the position of the projectile. The target is the mob
 * the projectile is targeting. The gemstone is the gemstone of the projectile.
 * The level is the level of the gemstone where the projectile is from.
 *
 */
typedef struct {
    Gemstone gem;
    unsigned int level;
    double speed;
    Coord_f pos;
    Mob* target;
} Projectile;

/*************/
/* Functions */
/*************/

/**
 * @brief Initialize a projectile.
 * @details The projectile is initialized with the spawn position, the gemstone
 * and the target. The spawn position is the position where the projectile will
 * spawn. The gemstone is the gemstone where is from the projectile. The target
 * is the mob the projectile is targeting. The level is the level of the
 * gemstone where the projectile is from.
 *
 * @pre The gemstone must be initialized.
 * @pre The target must be initialized.
 *
 * @param spawn Spawn position of the projectile.
 * @param gem Gemstone of the projectile.
 * @param target Target of the projectile.
 * @return Projectile Projectile.
 */
Projectile Proj_init(Coord_f spawn, Gem* gem, Mob* target);

/**
 * @brief Move the projectile to the next step. If the projectile is too close
 * to the target it will return false. Otherwise it will return true.
 *
 * @param proj Projectile to move.
 * @return if the projectile too close to the target.
 */
bool Proj_next_step(Projectile* proj);

/**
 * @brief Calculate the damage of the projectile.
 * @details The damage is calculated with the PROJ_CONST_DMG and a multiplier
 * depending of the level of the gemstone.
 *
 * @param proj Projectile to calculate the damage.
 * @return Damage done by the projectile.
 */
int Proj_damage(Projectile* proj);

#endif  // _PROJECTILE_H_
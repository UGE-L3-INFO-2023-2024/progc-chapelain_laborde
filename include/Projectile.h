/**
 * @file Projectile.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage projectile (init, move, damage).
 * @date 19-11-2023
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
 *
 * @param spawn Spawn position of the projectile.
 * @param gem Gemstone of the projectile.
 * @param target Target of the projectile.
 * @return Projectile Projectile.
 */
Projectile Proj_init(Coord_f spawn, Gem* gem, Mob* target);

/**
 * @brief Move the projectile to the next step.
 *
 * @param proj Projectile to move.
 * @return if the projectile too close to the target.
 */
bool Proj_next_step(Projectile* proj);

/**
 * @brief Calculate the damage of the projectile.
 *
 * @param proj Projectile to calculate the damage.
 * @return Damage done
 *
 */
int Proj_damage(Projectile* proj);

#endif  // _PROJECTILE_H_
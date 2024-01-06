/**
 * @file Projectile.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19-11-2023
 *
 */

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Color.h"
#include "Gemstone.h"
#include "Mob.h"

#define PROJ_SPEED 3
#define PROJ_CONST_DMG 1

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
Projectile Proj_init(Coord_f spawn, const Gem* gem, Mob* target);

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
 * @return Damage of the projectile.
 */
double Proj_damage(Projectile* proj);

/**
 * @brief Copy a projectile.
 *
 * @param projO Projectile to copy.
 * @return Deep Copied projectile.
 */
Gemstone Gemstone_copy(Gem* gemO);

#endif  // _PROJECTILE_H_
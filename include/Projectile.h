/**
 * @file Projectile.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 19/11/2023
 *
 */

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Color.h"
#include "Mob.h"

#define PROJ_SPEED 3
#define PROJ_CONST_DMG 1

typedef struct {
    HSV_Color color;
    unsigned int level;
    double speed;
    Coord_f pos;
    Mob* target;
} Projectile;

Projectile Proj_init(Coord_f spawn, const Gem* gem, Mob* target);
bool Proj_next_step(Projectile* proj);
double Proj_damage(Projectile* proj);

#endif  // _PROJECTILE_H_
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

typedef struct {
    HSV_Color color;
    double speed;
    Mob* target;
    Coord_f pos;
} Projectile;

Projectile Proj_init(Coord_f spawn, Mob* target);
bool Proj_next_step(Projectile* proj);

#endif  // _PROJECTILE_H_
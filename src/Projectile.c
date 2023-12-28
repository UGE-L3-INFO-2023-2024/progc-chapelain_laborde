/**
 * @file Projectile.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 26/12/2023
 *
 */

#include "Projectile.h"

#include <stdbool.h>

#include "Color.h"
#include "Mob.h"
#include "Utils.h"

Projectile Proj_init(Coord_f spawn, Mob* target) {
    return (Projectile){
        .color = Color_rand(),
        .speed = PROJ_SPEED / (double)FRAMERATE,
        .target = target,
        .pos = spawn,
    };
}

bool Proj_next_step(Projectile* proj) {
    double dist = Utils_coord_f_distance(proj->pos, proj->target->pos);
    if (dist < proj->speed) {
        return false;
    }
    Coord_f vect = {
        .x = (proj->target->pos.x - proj->pos.x) / dist,
        .y = (proj->target->pos.y - proj->pos.y) / dist};
    proj->pos.x += vect.x;
    proj->pos.y += vect.y;
    return true;
}
/**
 * @file Projectile.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 26/12/2023
 *
 */

#include "Projectile.h"

#include <math.h>
#include <stdbool.h>

#include "Color.h"
#include "Gemstone.h"
#include "Mob.h"
#include "Utils.h"

Projectile Proj_init(Coord_f spawn, const Gem* gem, Mob* target) {
    return (Projectile){
        .color = gem->color,
        .speed = PROJ_SPEED / (double)FRAMERATE,
        .target = target,
        .pos = spawn,
        .level = gem->level,
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

double damage(Projectile* proj) {
    return PROJ_CONST_DMG *
           pow(2, proj->level) *
           (1 - cos(Utils_deg_to_rad(proj->color - proj->target->color)) / 2);
}
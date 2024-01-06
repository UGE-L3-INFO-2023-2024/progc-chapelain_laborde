/**
 * @file Projectile.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 26-12-2023
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
        .gem = Gemstone_copy(gem),
        .speed = PROJ_SPEED / (double)FRAMERATE,
        .target = target,
        .pos = spawn,
        .level = gem->level,
    };
}

bool Proj_next_step(Projectile* proj) {
    double dist = Utils_coord_f_distance(proj->pos, proj->target->pos);
    // to close to the target
    if (dist <= proj->speed) {
        return false;
    }
    Coord_f vect = {
        .x = (proj->target->pos.x - proj->pos.x) / dist,
        .y = (proj->target->pos.y - proj->pos.y) / dist};

    // cross product with the speed (vect * speed / 1)
    proj->pos.x += vect.x * proj->speed;
    proj->pos.y += vect.y * proj->speed;
    return true;
}

double Proj_damage(Projectile* proj) {
    return PROJ_CONST_DMG *
           pow(2, proj->level) *
           (1 - cos(Utils_deg_to_rad(proj->gem.color - proj->target->color)) / 2);
}
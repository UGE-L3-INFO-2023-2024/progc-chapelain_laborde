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

Projectile Proj_init(Coord_f spawn, Gem* gem, Mob* target) {
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

int _damage_element(Projectile* proj, int dmg) {
    Mob_apply_element(proj->target, Gemstone_get_element(proj->gem));
    switch (proj->target->elem.main) {
        case BURNING:
            dmg *= 3;
            proj->target->elem.main = NONE;
            break;
        case SPRAYING:
            dmg += (dmg * SPRAYING_DMG_PERCENT);
        case PYRO:
            dmg += (dmg * PYRO_DMG_PERCENT);
            break;
        default:
            break;
    }
    return dmg;
}

int Proj_damage_raw(Projectile* proj) {
    int dmg = PROJ_CONST_DMG *
              pow(2, proj->level) *
              (1 - cos(Utils_deg_to_rad(proj->gem.color - proj->target->color)) / 2);
    if (proj->gem.type == MIXED) {
        dmg *= 2;
        if (!(rand() % 10)) {  // 10% chance
            dmg *= 2;
        }
    } else {
        dmg = _damage_element(proj, dmg);
    }

    proj->target->current_hp < dmg ? proj->target->current_hp = 0
                                   : (proj->target->current_hp -= dmg);
    return dmg;
}
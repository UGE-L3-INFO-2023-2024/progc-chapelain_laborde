/**
 * @file Mob.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 15-11-2023
 *
 */

#include "Mob.h"

#include <math.h>
#include <stdbool.h>

#include "Color.h"
#include "Element.h"
#include "Utils.h"

Mob Mob_init_basic(int wave, Coord_f start) {
    return (Mob){
        .max_hp = Mob_max(wave, false),
        .current_hp = Mob_max(wave, false),
        .speed = 1. / (double)FRAMERATE,
        .pos = start,
        .color = Color_rand(),
        .apply_elem = NONE,
        .going = {.x = -1, .y = -1},  // temp value to initialize
    };
}

Mob Mob_init_fast(int wave, Coord_f start) {
    return (Mob){
        .max_hp = Mob_max(wave, false),
        .current_hp = Mob_max(wave, false),
        .speed = 2. / (double)FRAMERATE,
        .pos = start,
        .color = Color_rand(),
        .apply_elem = NONE,
        .going = {.x = -1, .y = -1},  // temp value to initialize
    };
}

Mob Mob_init_boss(int wave, Coord_f start) {
    return (Mob){
        .max_hp = Mob_max(wave, true),
        .current_hp = Mob_max(wave, true),
        .speed = 1. / (double)FRAMERATE,
        .pos = start,
        .color = Color_rand(),
        .apply_elem = NONE,
        .going = {.x = -1, .y = -1},  // temp value to initialize
    };
}

int Mob_max(int wave, bool boss) {
    int hp = MOB_CONST_HP * pow(1.2, wave);
    return (boss) ? (hp * 12) : (hp);
}

void Mob_next_step(Mob *mob, Direction dir) {
    switch (dir) {
        case NORTH:
            mob->pos.y -= mob->speed;
            break;
        case EAST:
            mob->pos.x += mob->speed;
            break;
        case SOUTH:
            mob->pos.y += mob->speed;
            break;
        case WEST:
            mob->pos.x -= mob->speed;
            break;
        default:
            break;
    }
}

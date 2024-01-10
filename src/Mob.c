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
#include "TimeManager.h"
#include "Utils.h"

Mob Mob_init_basic(int wave, Coord_f start) {
    return (Mob){
        .max_hp = Mob_max(wave, false),
        .current_hp = Mob_max(wave, false),
        .speed = 1. / (double)FRAMERATE,
        .pos = start,
        .color = Color_rand(),
        .elem = Elem_init(),
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
        .elem = Elem_init(),
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
        .elem = Elem_init(),
        .going = {.x = -1, .y = -1},  // temp value to initialize
    };
}

int Mob_max(int wave, bool boss) {
    int hp = MOB_CONST_HP * pow(1.2, wave);
    return (boss) ? (hp * 12) : (hp);
}

void _clear_elem_time(Mob* mob) {
    if (Time_is_after(mob->elem.end_apply_main, Time_get())) {
        mob->elem.main = NONE;
    }
    if (Time_is_after(mob->elem.end_apply_second, Time_get()) &&
        mob->elem.second == SPRAYING) {
        mob->elem.second = NONE;
    }
}

double _compute_elem_speed(Mob* mob) {
    double base_speed = mob->speed;
    switch (mob->elem.main) {
        case ROOTING:
            base_speed = 0;
            break;
        case HYDRO:
            base_speed /= 1.5;
            break;
        case SPRAYING:
            base_speed /= 1.25;
            break;
        default:
            break;
    }
    if (mob->elem.second == SPRAYING) {
        base_speed /= 1.25;
    }
    return base_speed;
}

void Mob_next_step(Mob* mob, Direction dir) {
    _clear_elem_time(mob);

    // rand between 0.9 and 1.1
    double rand_speed = _compute_elem_speed(mob) *
                        Utils_random_uniform(0.9, 1.1);
    switch (dir) {
        case NORTH:
            mob->pos.y -= rand_speed;
            break;
        case EAST:
            mob->pos.x += rand_speed;
            break;
        case SOUTH:
            mob->pos.y += rand_speed;
            break;
        case WEST:
            mob->pos.x -= rand_speed;
            break;
        default:
            break;
    }
    if (mob->elem.main == DENDRO &&
        Time_is_after(mob->elem.next_hit_main, Time_get())) {
        mob->current_hp -= (mob->elem.origin_dmg * DENDRO_DMG_PERCENT);
        Time_add_ms(Time_get(), DENDRO_NEXT_HIT_MS);
    }
}

static void _apply_pyro(Mob* mob) {
    if (mob->elem.main == NONE) {
        mob->elem.main = PYRO;
    } else if (mob->elem.main == DENDRO) {
        mob->elem.main = BURNING;
    } else if (mob->elem.main == HYDRO) {
        mob->elem.main = SPRAYING;
        mob->elem.end_apply_main = Time_add_ms(Time_get(), SPRAYING_DURATION_MS);
    }
}

static void _apply_dendro(Mob* mob) {
    if (mob->elem.main == NONE) {
        mob->elem.main = DENDRO;
        mob->elem.end_apply_main = Time_add_ms(Time_get(), DENDRO_DURATION_MS);
        mob->elem.next_hit_main = Time_add_ms(Time_get(), DENDRO_NEXT_HIT_MS);
    } else if (mob->elem.main == PYRO) {
        mob->elem.main = BURNING;
    } else if (mob->elem.main == DENDRO) {
        mob->elem.end_apply_main = Time_add_ms(Time_get(), DENDRO_DURATION_MS);
    } else if (mob->elem.main == HYDRO) {
        mob->elem.main = ROOTING;
        mob->elem.end_apply_main = Time_add_ms(Time_get(), ROOTING_DURATION_MS);
    }
}

static void _apply_hydro(Mob* mob) {
    if (mob->elem.main == NONE) {
        mob->elem.main = HYDRO;
        mob->elem.end_apply_main = Time_add_ms(Time_get(), HYDRO_DURATION_MS);
    } else if (mob->elem.main == PYRO) {
        mob->elem.main = SPRAYING;
        mob->elem.end_apply_main = Time_add_ms(Time_get(), SPRAYING_DURATION_MS);
    } else if (mob->elem.main == DENDRO) {
        mob->elem.main = ROOTING;
        mob->elem.end_apply_main = Time_add_ms(Time_get(), ROOTING_DURATION_MS);
    } else if (mob->elem.main == HYDRO) {
        mob->elem.end_apply_main = Time_add_ms(Time_get(), HYDRO_DURATION_MS);
    }
}

void Mob_apply_element(Mob* mob, Element_Type type) {
    switch (type) {
        case PYRO:
            _apply_pyro(mob);
            break;
        case DENDRO:
            _apply_dendro(mob);
            break;
        case HYDRO:
            _apply_hydro(mob);
            break;
        default:
            break;
    }
}
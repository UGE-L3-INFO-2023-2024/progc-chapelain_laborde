/**
 * @file Wave.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 12-12-2023
 *
 */

#include "Wave.h"

#include <stdlib.h>
#include <time.h>

#include "DynamicArray.h"
#include "Mob.h"
#include "TimeManager.h"
#include "Utils.h"
#include "Wave.h"

Error Wave_init(Wave *wave) {
    wave->nb_wave = 0;
    wave->nb_mob_wave = 0;
    wave->next_mob = Time_get();
    wave->next_wave = wave->next_mob;
    Error err = DA_init(&wave->mob_list, 24, MOB);
    wave->type_mob = UNKNOW;
    err.func = __func__;
    return err;
}

/**
 * @brief Randomly choose the type of the next wave.
 *
 * @param wave Wave to spawn.
 */
static void _random_type_wave(Wave *wave) {
    int rand_nb = rand() % 10;
    // in case of boss in the 5 first waves
    while (rand_nb == 9 && wave->nb_wave < 5) {
        rand_nb = rand() % 10;
    }
    if (rand_nb < 5) {
        wave->nb_mob_wave = 12;
        wave->type_mob = BASIC;
    } else if (rand_nb < 7) {
        wave->nb_mob_wave = 24;
        wave->type_mob = MASS;
    } else if (rand_nb < 9) {
        wave->nb_mob_wave = 12;
        wave->type_mob = FAST;
    } else {
        wave->nb_mob_wave = 2;
        wave->type_mob = BOSS;
    }
}

/**
 * @brief Add the time for the next mob.
 *
 * @param wave Wave to spawn.
 * @param last_spawn Last time a mob was spawn.
 *
 */
static void _add_time_mob(Wave *wave, struct timespec last_spawn) {
    switch (wave->type_mob) {
        case UNKNOW:
            /* Do nothing */
            break;
        case FAST:
        case MASS:
            wave->next_mob = Time_add_ms(last_spawn, 500);
            break;
        default:
            wave->next_mob = Time_add_ms(last_spawn, 1000);
            break;
    }
}

/**
 * @brief Add the time for the last mob.
 *
 * @param wave Wave to spawn.
 *
 */
static void _add_time_last_mob(Wave *wave) {
    wave->next_mob = wave->next_wave;
}

/**
 * @brief Add a type mob to the wave.
 *  general function -> _add_mob
 *
 * @param wave Wave to spawn.
 * @param start Start of the path.
 * @param Mob_func Function to initialize the mob.
 * @return Error (realloc DynamicArray mob or alloc mob)
 */
static Error _add_mob_type(Wave *wave, Coord_f start,
                           Mob (*Mob_func)(int, Coord_f)) {
    Error error = NO_ERROR;
    Mob *mob = malloc(sizeof(Mob));
    if (!mob) {
        error.type = MALLOC_ERR;
        return error;
    }
    *mob = Mob_func(wave->nb_wave, start);

    error.type =
        DA_add(&wave->mob_list, (DynamicArray_Union){.mob = mob}, MOB).type;
    return error;
}

/**
 * @brief Add a mob to the wave.
 *
 * @param wave Wave to spawn.
 * @param start Start of the path.
 * @param type Type of the mob.
 * @return Error (realloc DynamicArray mob or alloc mob)
 */
static Error _add_mob(Wave *wave, Coord_f start, Type_wave type) {
    Error err = NO_ERROR;
    switch (type) {
        case BOSS:
            err.type = _add_mob_type(wave, start, &Mob_init_boss).type;
            return err;
        case FAST:
            err.type = _add_mob_type(wave, start, &Mob_init_fast).type;
            return err;
        case MASS:
        default:
            err.type = _add_mob_type(wave, start, &Mob_init_basic).type;
            return err;
    }
    // useless
    return NO_ERROR;
}

Error Wave_spawn_next(Wave *wave, Coord_f start) {
    Error err = NO_ERROR;
    struct timespec time = Time_get();

    if (Time_is_after(wave->next_wave, time) && wave->type_mob == UNKNOW) {
        wave->nb_wave++;
        wave->next_wave = Time_add_ms(time, TIME_NEXT_WAVE);
        _random_type_wave(wave);
    }

    if (Time_is_after(wave->next_mob, time) && wave->nb_mob_wave) {
        err.type = _add_mob(wave, start, wave->type_mob).type;
        if (err.type) {
            return err;
        }
        _add_time_mob(wave, time);
        wave->nb_mob_wave--;
        if (!wave->nb_mob_wave) {
            _add_time_last_mob(wave);
            wave->type_mob = UNKNOW;
        }
    }
    return NO_ERROR;
}

int Wave_skip_to_next(Wave *wave) {
    struct timespec time = Time_get();
    long sec_diff = 0;
    if (Time_is_equal(wave->next_mob, wave->next_wave)) {
        sec_diff = wave->next_wave.tv_sec - time.tv_sec;
        wave->next_wave = time;
        wave->next_mob = time;
    }
    return sec_diff;
}

/**
 * @brief Get the next going of the mob.
 *
 * @param mob Pointer to the mob.
 * @param da DynamicArray of the path.
 * @return if the mob is tp in the spawn.
 *
 */
static bool _next_going_unit(Mob *mob, DynamicArray *da) {
    // first time
    if (mob->going.x == -1 && mob->going.y == -1) {
        mob->going = Utils_coord_i_to_f_center(
            da->arr[1].path);  // 1 beacause 0 is the start
        return false;
    }

    Coord_i mob_going = Utils_coord_f_to_i(mob->going);
    for (int i = 0; i < da->max_len; i++) {
        // in the corner
        if (mob_going.x == da->arr[i].path.x &&
            mob_going.y == da->arr[i].path.y) {
            if (i != da->real_len - 1) {
                mob->going = Utils_coord_i_to_f_center(da->arr[i + 1].path);
            } else {
                // 1 beacause 0 is the start
                mob->going = Utils_coord_i_to_f_center(da->arr[1].path);
                // start
                mob->pos = Utils_coord_i_to_f_center(da->arr[0].path);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Move the mob to the next step.
 *
 * @param mob Pointer to the mob.
 * @param da DynamicArray of the path.
 * @return if the mob is tp in the spawn.
 *
 */
bool Wave_next_step_unit(Mob *mob, DynamicArray *da) {
    bool got_tp = false;
    if ((mob->going.x == -1 && mob->going.y == -1) ||
        Utils_is_in_middle(mob->going, mob->pos, 0.05)) {
        got_tp = _next_going_unit(mob, da);
    }

    Direction dir = Utils_get_dir(mob->going, mob->pos, 0.05);
    Mob_next_step(mob, dir);
    return got_tp;
}
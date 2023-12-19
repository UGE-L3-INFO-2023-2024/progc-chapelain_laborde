/**
 * @file Wave.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 12-12-2023
 *
 */

#include "Wave.h"

#include <stdio.h>
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
    timespec_get(&(wave->next_mob), TIME_UTC);
    wave->next_wave = wave->next_mob;
    // timespec_get(&(wave->next_wave), TIME_UTC);
    // wave->next_mob = (struct timespec){.tv_sec = -1, .tv_nsec = -1};
    // wave->next_wave = (struct timespec){.tv_sec = -1, .tv_nsec = -1};
    Error err = DA_init(&wave->mob_list, 24, MOB);
    wave->type_mob = UNKNOW;
    return err;
}

static void _random_type_wave(Wave *wave) {
    int rand_nb = rand() % 10;
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

static void _add_time_last_mob(Wave *wave) {
    wave->next_mob = wave->next_wave;
}

static void _add_mob_type(Wave *wave, Coord_f start, Mob (*Mob_func)(int, Coord_f)) {
    DA_add(&wave->mob_list,
           (DynamicArray_Union){.mob = Mob_func(wave->nb_wave, start)}, MOB);
}

static void _add_mob(Wave *wave, Coord_f start, Type_wave type) {
    switch (type) {
        case BOSS:
            _add_mob_type(wave, start, &Mob_init_boss);
            return;
        case FAST:
            _add_mob_type(wave, start, &Mob_init_fast);
            return;
        case MASS:
            _add_mob_type(wave, start, &Mob_init_basic);
            return;
        default:
            _add_mob_type(wave, start, &Mob_init_basic);
            return;
    }
}

void Wave_spawn_next(Wave *wave, Coord_f start) {
    struct timespec time;
    timespec_get(&time, TIME_UTC);

    if (Time_is_after(wave->next_wave, time) && wave->type_mob == UNKNOW) {
        wave->nb_wave++;
        wave->next_wave = Time_add_ms(time, TIME_NEXT_WAVE);
        _random_type_wave(wave);
    }

    if (Time_is_after(wave->next_mob, time) && wave->nb_mob_wave) {
        _add_mob(wave, start, wave->type_mob);
        _add_time_mob(wave, time);
        wave->nb_mob_wave--;
        if (!wave->nb_mob_wave) {
            _add_time_last_mob(wave);
            wave->type_mob = UNKNOW;
        }
    }
}

static void _next_going_unit(Mob *mob, DynamicArray *da) {
    if (mob->going.x == -1 && mob->going.y == -1) {
        mob->going = Utils_coord_i_to_f_center(da->arr[0].path);
        return;
    }
    Coord_i mob_going = Utils_coord_f_to_i(mob->going);
    for (int i = 0; i < da->max_len; i++) {
        if (mob_going.x == da->arr[i].path.x &&
            mob_going.y == da->arr[i].path.y &&
            i != da->max_len - 1) {
            mob->going = Utils_coord_i_to_f_center(da->arr[i + 1].path);
            return;
        }
    }
}

static void _next_step_unit(Mob *mob, DynamicArray *da) {
    if ((mob->going.x == -1 && mob->going.y == -1) ||
        Utils_is_in_middle(mob->going, mob->pos, 0.05)) {
        _next_going_unit(mob, da);
    }

    Direction dir = Utils_get_dir(mob->going, mob->pos, 0.05);
    Mob_next_step(mob, dir);
}

void Wave_next_step(Wave *wave, DynamicArray *turns) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        _next_step_unit(&(wave->mob_list.arr[i].mob), turns);
    }
}

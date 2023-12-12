/**
 * @file Wave.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 12-12-2023
 *
 */

#include "Wave.h"

#include <stdio.h>

#include "DynamicArray.h"
#include "Mob.h"
#include "Utils.h"
#include "Wave.h"

void Wave_next_step_unit(Mob *mob, DynamicArray *da) {
    if ((mob->going.x == -1 && mob->going.y == -1) ||
        Utils_is_in_middle(mob->going, mob->pos, 0.05)) {
        Wave_next_going_unit(mob, da);
    }

    Direction dir = Utils_get_dir(mob->going, mob->pos, 0.05);
    Mob_next_step(mob, dir);
}

void Wave_next_going_unit(Mob *mob, DynamicArray *da) {
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
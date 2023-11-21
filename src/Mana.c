/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Mana.h"

#include <math.h>
#include <stdbool.h>

ManaPool Mana_init(void) {
    return (ManaPool){
        .level = 0,
        .mana_real = MANA_START,
        .mana_max = Mana_max(0),
    };
}

int Mana_max(int level) {
    return 2000 * pow(1.4, level);
}

bool Mana_pool_can_be_upgrade(ManaPool pool) {
    return 500 * pow(1.4, pool.level) <= pool.mana_real;
}

bool Mana_pool_upgrade(ManaPool* pool) {
    if (!pool || !Mana_pool_can_be_upgrade(*pool)) {
        return true;
    }
    pool->level++;
    pool->mana_real -= 500 * pow(1.4, pool->level);
    pool->mana_max = Mana_max(pool->level);
    return false;
}

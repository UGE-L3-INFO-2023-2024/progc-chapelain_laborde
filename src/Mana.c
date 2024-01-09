/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 15-11-2023
 *
 */

#include "Mana.h"

#include <math.h>
#include <stdbool.h>

ManaPool Mana_pool_init(void) {
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
    // 25% of max mana for an upgrade
    return pool.mana_max / 4 <= pool.mana_real;
}

bool Mana_pool_upgrade(ManaPool* pool) {
    if (!pool || !Mana_pool_can_be_upgrade(*pool)) {
        return false;
    }
    pool->level++;
    pool->mana_real -= pool->mana_max / 4;
    pool->mana_max = Mana_max(pool->level);
    return true;
}

static bool Mana_can_be_buy(ManaPool pool, int price) {
    return pool.mana_real >= price;
}

bool Mana_buy(ManaPool* pool, int price) {
    if (!pool || !Mana_can_be_buy(*pool, price)) {
        return false;
    }
    pool->mana_real -= price;
    return true;
}

int Mana_tower_cost(int nb_towers) {
    if (nb_towers < 0) {
        return -1;
    }
    nb_towers++;
    return nb_towers < 4 ? 0 : 100 * pow(2, nb_towers - 4);
}

int Mana_gem_cost(int gem_level) {
    if (gem_level < 0) {
        return -1;
    }
    return 100 * pow(2, gem_level);
}

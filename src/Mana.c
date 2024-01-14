/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the Manapool (Init, bying, cost, upgrade).
 * @date 15-11-2023
 *
 */

#include "Mana.h"

#include <math.h>
#include <stdbool.h>

/* Initialise ManaPool */
ManaPool Mana_pool_init(void) {
    return (ManaPool){
        .level = 0,
        .mana_real = MANA_START,
        .mana_max = Mana_max(0),
    };
}

/* Compute max mana storage for a level */
int Mana_max(int level) {
    return 2000 * pow(1.4, level);
}

/* Check if the upgrade of the manapool is possible */
bool Mana_pool_can_be_upgrade(ManaPool pool) {
    return 500 * pow(1.4, pool.level) <= pool.mana_real;
}

/* Upgrade the manaPool if possible */
bool Mana_pool_upgrade(ManaPool* pool) {
    if (!pool || !Mana_pool_can_be_upgrade(*pool)) {
        return false;
    }
    pool->mana_real -= 500 * pow(1.4, pool->level++);
    pool->mana_max = Mana_max(pool->level);
    return true;
}

/* Check if there are enough mana in the pool */
static bool Mana_can_be_buy(ManaPool pool, int price) {
    return pool.mana_real >= price;
}

/* Modify manaPool quantity loss if possible */
bool Mana_buy(ManaPool* pool, int price) {
    if (!pool || !Mana_can_be_buy(*pool, price)) {
        return false;
    }
    pool->mana_real -= price;
    return true;
}

/* Modify manaPool quantity gain */
void Mana_gain(ManaPool* pool, int price) {
    pool->mana_real = (price + pool->mana_real <= pool->mana_max)
                          ? price + pool->mana_real
                          : pool->mana_max;
}

/* Mana tower cost */
int Mana_tower_cost(int nb_towers) {
    if (nb_towers < 0) {
        return -1;
    }
    nb_towers++;
    return nb_towers < 4 ? 0 : 100 * pow(2, nb_towers - 4);
}

/* Mana gain when a mob as been killed */
int Mana_gain_mob_death(int mob_max_hp, int level_mana) {
    return MANA_ON_KILL_PERCENT * mob_max_hp * pow(1.3, level_mana);
}

/* Mob tp back to spawn cost */
int Mana_cost_mob_tp(int mob_max_hp, int level_mana) {
    return MANA_ON_TP_PERCENT * mob_max_hp * pow(1.3, level_mana);
}

/* Mana gain when skip wave */
int Mana_gain_skip_wave(int max_mana, int sec) {
    return max_mana * (sec / (double)100);
}

/* Mana gem buying cost */
int Mana_gem_cost(int gem_level) {
    if (gem_level < 0) {
        return -1;
    }
    return 100 * pow(2, gem_level);
}

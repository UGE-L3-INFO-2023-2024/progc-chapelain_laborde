/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the Manapool (Init, buying, cost, upgrade).
 * @date 02-11-2023
 *
 */

#include "Mana.h"

#include <limits.h>
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
    long mana = (long)(2000 * pow(1.4, level));
    return mana > INT_MAX ? INT_MAX : (int)mana;
}

/* Check if the upgrade of the manapool is possible */
bool Mana_pool_can_be_upgrade(ManaPool pool) {
    if (Mana_max(pool.level + 1) == INT_MAX) {
        return false;
    }
    return Mana_pool_upgrade_cost(pool) <= pool.mana_real;
}

/* Get the cost to upgrade mana pool */
int Mana_pool_upgrade_cost(ManaPool pool) {
    long cost = (long)(500 * pow(1.4, pool.level));
    return cost > INT_MAX ? INT_MAX : (int)cost;
}

/* Upgrade the manaPool if possible */
bool Mana_pool_upgrade(ManaPool* pool) {
    if (!pool || !Mana_pool_can_be_upgrade(*pool)) {
        return false;
    }
    pool->mana_real -= Mana_pool_upgrade_cost(*pool);
    pool->level++;
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
void Mana_gain(ManaPool* pool, int gain) {
    pool->mana_real = (gain + pool->mana_real <= pool->mana_max)
                          ? gain + pool->mana_real
                          : pool->mana_max;
}

/* Mana tower cost */
int Mana_tower_cost(int nb_towers) {
    if (nb_towers < 0) {
        return -1;
    }
    nb_towers++;
    long cost = nb_towers < 4 ? 0 : (long)(100 * pow(2, nb_towers - 4));
    return cost > INT_MAX ? INT_MAX : (int)cost;
}

/* Mana gain when a mob as been killed */
int Mana_gain_mob_death(int mob_max_hp, int level_mana) {
    return (int)(MANA_ON_KILL_PERCENT * mob_max_hp * pow(1.3, level_mana));
}

/* Mob tp back to spawn cost */
int Mana_cost_mob_banish(int mob_max_hp, int level_mana) {
    return (int)(MANA_ON_TP_PERCENT * mob_max_hp * pow(1.3, level_mana));
}

/* Mana gain when skip wave */
int Mana_gain_skip_wave(int max_mana, long sec) {
    return (int)(max_mana * ((double)sec / 100.0));
}

/* Mana gem buying cost */
int Mana_gem_cost(int gem_level) {
    if (gem_level < 0) {
        return -1;
    }
    return (int)(100 * pow(2, gem_level));
}

/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Module to manage the map.
 * (init, towers shooting, projs moving & damage, free)
 * @date 02-11-2023
 *
 */

#include "Map.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"
#include "Element.h"
#include "Error.h"
#include "Projectile.h"
#include "Stats.h"
#include "TimeManager.h"
#include "Utils.h"
#include "Wave.h"

/**
 * @brief Initialize a Cell.
 *
 * @return Cell cell.
 */
static Cell _init_cell() {
    return (Cell){
        .is_path = false,
        .have_tower = false,
    };
}

/* Initialize the board of the map. */
void Map_init_board(Map* map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->board[y][x] = _init_cell();
        }
    }
}

/**
 * @brief Initialize the towers of a Map.
 *
 * @param map Map to initialize.
 * @return Error if there is a allocation error.
 */
static Error _init_towers(Map* map) {
    Error err = DA_init(&map->towers, 10, TOWER);
    err.func = __func__;
    return err;
}

/**
 * @brief Initialize the projs of a Map.
 *
 * @param map Map to initialize.
 * @return Error if there is a allocation error.
 */
static Error _init_projs(Map* map) {
    Error err = DA_init(&map->projs, 40, PROJECTILE);
    err.func = __func__;
    return err;
}

/* Initialize the Map and all its fields (towers, projs, mobs, ..) */
Error Map_init(Map* map) {
    Error err = NO_ERROR;
    Map_init_board(map);
    map->nest = (Coord_i){-1, -1};
    map->castle = (Coord_i){-1, -1};
    err.type = _init_towers(map).type;
    if (err.type)
        return err;
    err.type = _init_projs(map).type;
    if (err.type)
        return err;
    err.type = Wave_init(&(map->mobs)).type;
    if (err.type)
        return err;
    err.type = DA_init(&map->map_turns, 10, PATH).type;
    if (err.type)
        return err;
    return NO_ERROR;
}

/* Map add tower (error possible if realloc )*/
Error Map_add_tower(Map* map, Tower tower) {
    map->board[tower.coord.y][tower.coord.x].have_tower = true;
    Error err = DA_add(&map->towers, (DA_Union){.tower = tower}, TOWER);
    err.func = __func__;
    return err;
}

/* Get tower from coord or NULL */
Tower* Map_get_tower(Map* map, Coord_i coord) {
    for (int i = 0; i < map->towers.real_len; i++) {
        if (map->towers.arr[i].tower.coord.x == coord.x &&
            map->towers.arr[i].tower.coord.y == coord.y) {
            return &map->towers.arr[i].tower;
        }
    }
    return NULL;
}

/**
 * @brief Make a tower shoot if possible. (no change of tower.available_at)
 *
 * @param tower Tower to shoot.
 * @param mobs Mobs to shoot.
 * @param projs Projs to add the new proj.
 * @return if the tower shoot or not.
 */
static bool _tower_shoot(Tower tower, DynamicArray* mobs,
                         DynamicArray* projs) {
    const Mob* mob = NULL;
    int index_target = -1;
    int hp_target = 0;

    // iterate over mobs to find the biggest hp
    for (int i = 0; i < mobs->real_len; i++) {
        mob = mobs->arr[i].mob;
        if (mob->current_hp > hp_target &&
            Utils_coord_f_distance(Utils_coord_i_to_f_center(tower.coord),
                                   mob->pos) < TOWER_RANGE) {
            index_target = i;
            hp_target = mob->current_hp;
        }
    }
    // if a target is found, shoot
    if (index_target != -1) {
        Projectile proj = Proj_init(Utils_coord_i_to_f_center(tower.coord),
                                    tower.gem, (mobs->arr[index_target].mob));
        DA_add(projs, (DynamicArray_Union){.proj = proj}, PROJECTILE);
    }
    // if the tower shoot or not
    return index_target != -1;
}

/* Make all towers shoot if possible. */
void Map_towers_shoot(Map* map) {
    for (int i = 0; i < map->towers.real_len; i++) {
        Tower tower = map->towers.arr[i].tower;
        if (Time_is_after(tower.available_at, Time_get()) && tower.has_gem &&
            _tower_shoot(map->towers.arr[i].tower, &map->mobs.mob_list,
                         &map->projs)) {
            // change available_at time
            map->towers.arr[i].tower.available_at =
                Time_add_ms(Time_get(), TOWER_SHOT_COOLDOWN_MS);
        }
    }
}

/**
 * @brief Deals pyro damage to neighbors.
 *
 * @param wave Wave to look in. (neighbors)
 * @param origin Mob hit by the pyro effect.
 * @param original_dmg Damage to spead.
 * @param dmg Pointer to the dmg to add.
 */
static void _pyro_spread(Wave* wave, const Mob* origin, int original_dmg,
                         int* dmg) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        Mob* mob = wave->mob_list.arr[i].mob;
        if (Utils_coord_f_distance(origin->pos, mob->pos) < PYRO_RADIUS &&
            mob != origin) {
            // compute the new dmg and store it in dmg for stats
            int damage = mob->current_hp < original_dmg ? mob->current_hp
                                                        : original_dmg;
            if (dmg) {
                *dmg += damage;
            }
            mob->current_hp -= damage;
        }
    }
}

/**
 * @brief Apply spraying element and damage to neighbors.
 *
 * @param wave Wave to look in. (neighbors)
 * @param origin Mob hit by the spraying.
 * @param original_dmg Damage to spead.
 * @param dmg Pointer to the dmg to add.
 */
static void _spraying_spread(Wave* wave, const Mob* origin, int original_dmg,
                             int* dmg) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        Mob* mob = wave->mob_list.arr[i].mob;
        if (Utils_coord_f_distance(origin->pos, mob->pos) < SPRAYING_RADIUS &&
            mob != origin) {
            // apply slow on neighbors
            mob->elem.second = SPRAYING;
            mob->elem.end_apply_second =
                Time_add_ms(Time_get(), SPRAYING_DURATION_MS);
            // compute the new dmg and store it in dmg for stats
            int damage = mob->current_hp < original_dmg ? mob->current_hp
                                                        : original_dmg;
            if (dmg) {
                *dmg += damage;
            }
            mob->current_hp -= damage;
        }
    }
}

/* Projectile move and apply damage when hit the mob */
void Map_actualise_proj(Map* map, Stats* stats) {
    int dmg_stats = 0;
    for (int i = 0; i < map->projs.real_len; i++) {
        if (!Proj_next_step(&(map->projs.arr[i].proj))) {
            int dmg = Proj_damage(&(map->projs.arr[i].proj));
            dmg_stats += dmg;
            if (map->projs.arr[i].proj.target->elem.main == PYRO) {
                long pyro_dmg = (long)(dmg * PYRO_DMG_PERCENT);
                _pyro_spread(&(map->mobs), map->projs.arr[i].proj.target,
                             pyro_dmg > INT_MAX ? INT_MAX : (int)pyro_dmg,
                             &dmg_stats);
                map->projs.arr[i].proj.target->elem.main = NONE;
            } else if (map->projs.arr[i].proj.target->elem.main == SPRAYING) {
                _spraying_spread(&(map->mobs), map->projs.arr[i].proj.target,
                                 dmg, &dmg_stats);
            }
            DA_remove_index(&map->projs, i);
            i--;
            // to check new placed proj
            // DA_remove_index move last to index
        }
    }
    stats->total_damage += dmg_stats;
}

/* Print a map (debug function) */
void Map_print(Map map) {
    printf("------------------------------\n");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map.board[y][x].is_path) {
                printf("#");
            } else {
                printf("*");
            }
        }
        printf("|\n");
    }
    printf("------------------------------\n");
}

/* Free a map with all his DA */
void Map_free(Map* map) {
    DA_free(map->towers);
    DA_free(map->projs);
    DA_free(map->mobs.mob_list);
    DA_free(map->map_turns);
    map->projs = (DynamicArray){0};
    map->towers = (DynamicArray){0};
    map->map_turns = (DynamicArray){0};
    map->mobs.mob_list = (DynamicArray){0};
    map = NULL;
}

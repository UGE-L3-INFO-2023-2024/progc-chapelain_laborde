/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 15-11-2023
 *
 */

#include "Map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"
#include "Element.h"
#include "Error.h"
#include "Projectile.h"
#include "TimeManager.h"
#include "Utils.h"

// TODO 0 : make static function of init

Error Map_init(Map* map) {
    Error err = NO_ERROR;
    Map_init_board(map);
    map->nest = (Coord_i){-1, -1};
    map->castle = (Coord_i){-1, -1};
    err.type = Map_init_towers(map).type;
    if (err.type)
        return err;
    err.type = Map_init_projs(map).type;
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

/**
 * @brief Initialize a Cell.
 *
 * @param coord Coord of the Cell.
 * @return Cell cell.
 */
static Cell _init_cell(Coord_i coord) {
    return (Cell){
        .is_path = false,
        .have_tower = false,
    };
}

void Map_init_board(Map* map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->board[y][x] = _init_cell((Coord_i){x, y});
        }
    }
}

Error Map_init_towers(Map* map) {
    Error err = DA_init(&map->towers, 10, TOWER);
    err.func = __func__;
    return err;
}

Error Map_init_projs(Map* map) {
    Error err = DA_init(&map->projs, 40, PROJECTILE);
    err.func = __func__;
    return err;
}

Error Map_add_tower(Map* map, Tower tower) {
    map->board[tower.coord.y][tower.coord.x].have_tower = true;
    Error err = DA_add(&map->towers, (DA_Union){.tower = tower}, TOWER);
    err.func = __func__;
    return err;
}

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
bool static _tower_shoot(Tower tower, DynamicArray* mobs,
                         DynamicArray* projs) {
    Mob* mob = NULL;
    int index_target = -1, hp_target = 0;

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
                                    &tower.gem, (mobs->arr[index_target].mob));
        DA_add(projs, (DynamicArray_Union){.proj = proj}, PROJECTILE);
    }
    // if the tower shoot or not
    return index_target != -1;
}

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

void _pyro_spread(Wave* wave, Mob* origin, int dmg) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        Mob* mob = wave->mob_list.arr[i].mob;
        if (Utils_coord_f_distance(origin->pos, mob->pos) < PYRO_RADIUS &&
            mob != origin) {
            mob->current_hp < dmg ? mob->current_hp = 0
                                  : (mob->current_hp -= dmg);
        }
    }
}

void _spraying_spread(Wave* wave, Mob* origin) {
    for (int i = 0; i < wave->mob_list.real_len; i++) {
        Mob* mob = wave->mob_list.arr[i].mob;
        if (Utils_coord_f_distance(origin->pos, mob->pos) < SPRAYING_RADIUS &&
            mob != origin) {
            mob->elem.second = SPRAYING;
            mob->elem.end_apply_second =
                Time_add_ms(Time_get(), SPRAYING_DURATION_MS);
        }
    }
}

void Map_actualise_proj(Map* map) {
    for (int i = 0; i < map->projs.real_len; i++) {
        if (!Proj_next_step(&(map->projs.arr[i].proj))) {
            int dmg = Proj_damage_raw(&(map->projs.arr[i].proj));
            if (map->projs.arr[i].proj.target->elem.main == PYRO) {
                _pyro_spread(&(map->mobs), map->projs.arr[i].proj.target,
                             dmg * PYRO_DMG_PERCENT);
                map->projs.arr[i].proj.target->elem.main = NONE;
            } else if (map->projs.arr[i].proj.target->elem.main == SPRAYING) {
                _spraying_spread(&(map->mobs), map->projs.arr[i].proj.target);
            }
            DA_remove_index(&map->projs, i);
            --i;  // to check new placed proj
            // DA_remove_index move last to index
        }
    }
}

void Map_print(Map* map) {
    printf("------------------------------\n");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map->board[y][x].is_path) {
                printf("#");
            } else {
                printf("*");
            }
        }
        printf("|\n");
    }
    printf("------------------------------\n");
}

void Map_free(Map* map) {
    DA_free(map->towers);
    DA_free(map->projs);
    DA_free(map->mobs.mob_list);
    DA_free(map->map_turns);
    map->projs = (DynamicArray){0};
    map->towers = (DynamicArray){0};
    map->map_turns = (DynamicArray){0};
    map->mobs = (Wave){0};
    map = NULL;
}

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
#include "Error.h"
#include "Projectile.h"
#include "TimeManager.h"
#include "Utils.h"

// temp to remove when gem initialized
#include "Gemstone.h"

Map Map_init(void) {
    return (Map){
        .nest = (Coord_i){-1, -1},
        .castle = (Coord_i){-1, -1},
    };
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
    return err;
}

Error Map_init_projs(Map* map) {
    Error err = DA_init(&map->projs, 40, PROJECTILE);
    return err;
}

Error Map_add_tower(Map* map, Tower tower) {
    map->board[tower.coord.y][tower.coord.x].have_tower = true;
    return DA_add(&map->towers, (DA_Union){.tower = tower}, TOWER);
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
        // to remove when gem initialized in tower
        Gemstone gem = Gemstone_init(1);
        Projectile proj = Proj_init(Utils_coord_i_to_f_center(tower.coord),
                                    &gem, (mobs->arr[index_target].mob));
        DA_add(projs, (DynamicArray_Union){.proj = proj}, PROJECTILE);
    }
    // if the tower shoot or not
    return index_target != -1;
}

void Map_towers_shoot(Map* map) {
    for (int i = 0; i < map->towers.real_len; i++) {
        Tower tower = map->towers.arr[i].tower;
        //  add after check tower.gem
        // is available and at range and got a gem
        if (Time_is_after(tower.available_at, Time_get()) &&
            _tower_shoot(map->towers.arr[i].tower, &map->mobs.mob_list,
                         &map->projs)) {
            // change available_at time
            map->towers.arr[i].tower.available_at =
                Time_add_ms(Time_get(), TOWER_SHOT_COOLDOWN_MS);
        }
    }
}

void Map_actualise_proj(Map* map) {
    for (int i = 0; i < map->projs.real_len; i++) {
        if (!Proj_next_step(&(map->projs.arr[i].proj))) {
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
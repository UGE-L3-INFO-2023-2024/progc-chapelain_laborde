/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"
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

void Map_init_board(Map* map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->board[y][x] = Map_init_cell((Coord_i){x, y});
        }
    }
}

Cell Map_init_cell(Coord_i coord) {
    return (Cell){
        .is_path = false,
        .have_tower = false,
    };
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

bool static _tower_shoot(Tower tower, DynamicArray* mobs, DynamicArray* projs) {
    Mob* mob = NULL;
    int index_target = -1, hp_target = 0;
    for (int i = 0; i < mobs->real_len; i++) {
        mob = mobs->arr[i].mob;
        if (mob->current_hp >= hp_target &&
            Utils_coord_f_distance(Utils_coord_i_to_f_center(tower.coord), mob->pos) < TOWER_RANGE) {
            index_target = i;
            hp_target = mob->current_hp;
        }
    }
    if (index_target != -1) {
        Gemstone gem = Gemstone_init();
        Projectile proj = Proj_init(Utils_coord_i_to_f_center(tower.coord),
                                    &gem, (mobs->arr[index_target].mob));
        DA_add(projs, (DynamicArray_Union){.proj = proj}, PROJECTILE);
    }
    return index_target != -1;
}

void Map_towers_shoot(Map* map) {
    for (int i = 0; i < map->towers.real_len; i++) {
        Tower tower = map->towers.arr[i].tower;
        //  add after check tower.gem
        if (Time_is_after(tower.available_at, Time_get()) &&
            _tower_shoot(map->towers.arr[i].tower, &map->mobs.mob_list, &map->projs)) {
            fprintf(stderr, "tower %d shoot -> change cooldown\n", i);
            map->towers.arr[i].tower.available_at = Time_add_ms(Time_get(), TOWER_SHOT_COOLDOWN_MS);
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

// Direction Map_got_next_path(Map* map, Coord_i pos, Direction ignore) {
//     Direction dir = NO_DIR;
//     static int Dir_point[4][2] = {
//         {0, -1},
//         {1, 0},
//         {0, 1},
//         {-1, 0},
//     };
//     for (int i = 0; i < 4; i++) {
//         if (map->board[pos.y + Dir_point[i][1]][pos.x + Dir_point[i][0]]
//                 .is_path &&
//             i != ignore) {
//             if (dir != NO_DIR) {
//                 fprintf(stderr,
//                         "Error in Map_got_next_path: more than one path\n");
//                 return NONE;
//             }
//             dir = i;
//         }
//     }
//     return dir;
// }
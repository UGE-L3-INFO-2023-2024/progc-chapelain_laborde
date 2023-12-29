/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Map.h"

#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"
#include "Utils.h"

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
        .coord = coord,
        .is_path = false,
        .tower = NULL,
    };
}

Error Map_init_towers(Map* map) {
    Error err = DA_init(&map->towers, 10, TOWER);
    return err;
}

Error Map_add_tower(Map* map, Tower tower) {
    Error err = DA_add(&map->towers, (DA_Union){.tower = tower}, TOWER);
    if (err) {
        return err;
    }
    map->board[tower.coord.y][tower.coord.x].tower =
        &map->towers.arr[map->towers.real_len - 1].tower;
    return CLEAR;
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

Direction Map_got_next_path(Map* map, Coord_i pos, Direction ignore) {
    Direction dir = NO_DIR;
    static int Dir_point[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
    };
    for (int i = 0; i < 4; i++) {
        if (map->board[pos.y + Dir_point[i][1]][pos.x + Dir_point[i][0]]
                .is_path &&
            i != ignore) {
            if (dir != NO_DIR) {
                fprintf(stderr,
                        "Error in Map_got_next_path: more than one path\n");
                return NONE;
            }
            dir = i;
        }
    }
    return dir;
}
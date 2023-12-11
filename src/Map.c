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

#include "Utils.h"

Map Map_init(void) {
    return (Map){
        .towers = NULL,
        .traps = NULL,
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
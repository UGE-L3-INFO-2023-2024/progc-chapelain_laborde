/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "../include/Map.h"

#include <stdio.h>
#include <stdlib.h>

#include "Mana.h"
#include "Utils.h"

Map Map_init(void) {
    return (Map){
        .mana = Init_mana(),
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
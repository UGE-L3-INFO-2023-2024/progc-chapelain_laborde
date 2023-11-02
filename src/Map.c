/**
 * @file Map.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */

#include "../include/Map.h"

#include <stdlib.h>

#include "../include/Mana.h"

Map Map_init(void) {
    Map map = {
        .mana = Init_mana(),
        .towers = NULL,
        .traps = NULL,
    };
    Map_init_board(&map);
    return map;
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

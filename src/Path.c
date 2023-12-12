/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 2023-11-15
 *
 */

#include "Path.h"

#include <stdbool.h>
#include <stdlib.h>

#include "DynamicArray.h"
#include "Map.h"
#include "Utils.h"

static int Path_manatan_dist(Coord_i a, Coord_i b) {
    return ABS(a.x - b.x) + ABS(a.y - b.y);
}

static int Path_forward_3_4(int max) {
    int acc = 0;
    for (int i = 0; i < max; i++) {
        if (rand() % 4) {
            acc++;
        }
    }
    return acc < 3 ? 3 : acc;
}

static void Path_apply_path(Map* map, Coord_i origin, Direction dir, int len) {
    static int Dir_point[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
    };

    for (int i = 0; i < len; i++) {
        map->board[origin.y + Dir_point[dir][1] * i]
                  [origin.x + Dir_point[dir][0] * i]
                      .is_path = true;
        map->board[origin.y + Dir_point[dir][1] * i]
                  [origin.x + Dir_point[dir][0] * i]
                      .trap = NULL;
    }
}

static Error Path_add_turn(DynamicArray* da, Coord_i origin, Direction dir, int len) {
    static int Dir_point[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
    };

    Coord_i coord = {
        .x = origin.x + Dir_point[dir][0] * len,
        .y = origin.y + Dir_point[dir][1] * len,
    };
    return DA_add(da, (DynamicArray_Union){.path = coord}, PATH);
}

static bool Path_manatan_etentu_cell(Map* map, Coord_i origin,
                                     Direction ignore) {
    if (origin.x < 2 || origin.x > MAP_WIDTH - 3 || origin.y < 2 ||
        origin.y > MAP_HEIGHT - 3) {
        return false;
    }

    // diagonale surement inutile
    // clang-format off
    static int neighbour[26][2] = {
    {-2,-2}, {-1,-2}, {0,-2}, {1,-2}, {2,-2},
    {-2,-1}, {-1,-1}, {0,-1}, {1,-1}, {2,-1},
    {-2, 0}, {-1, 0},         {1, 0}, {2, 0},
    {-2, 1}, {-1, 1}, {0, 1}, {1, 1}, {2, 1},
    {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2},
    };
    // clang-format on

    for (int i = 0; i < 26; i++) {
        if ((ignore == NORTH && neighbour[i][1] > 0) ||
            (ignore == EAST && neighbour[i][0] < 0) ||
            (ignore == SOUTH && neighbour[i][1] < 0) ||
            (ignore == WEST && neighbour[i][0] > 0)) {
            if (map->board[origin.y + neighbour[i][1]]
                          [origin.x + neighbour[i][0]]
                              .is_path == true) {
                return false;
            }
        }
    }
    return true;
}

static int Path_max_dir(Map* map, Coord_i start, Direction dir) {
    int acc = 0;
    static int Dir_point[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
    };

    // +2 to look oposite for ignore.
    while (Path_manatan_etentu_cell(map, start, (dir + 2) % 4)) {
        acc++;
        start.x += Dir_point[dir][0];
        start.y += Dir_point[dir][1];
    }
    return acc;
}

static void Path_gen_step(Map* map, Coord_i coord, Direction dir,
                          Direction* new_dir, int* new_len) {
    Direction arr_dir[2] = {
        Utils_modulo((dir + 1), 4),
        Utils_modulo((dir - 1), 4),
    };

    int arr_pos[2] = {
        Path_max_dir(map, coord, arr_dir[0]),
        Path_max_dir(map, coord, arr_dir[1]),
    };

    int dir_index = Utils_weighted_select(
        arr_pos, rand() % (Utils_sum_arr_i(arr_pos, 2) + 1), 2);
    if (dir_index == -1) {
        // Error in weighted_select
        return;
    }

    *new_dir = arr_dir[dir_index];
    *new_len = arr_pos[dir_index];
}

bool Path_gen(Map* map, DynamicArray* da) {
    int total_len = 0, total_turn = 0;
    // 1
    Map_init_board(map);

    // 2
    Coord_i origin = {
        .x = (rand() % (MAP_WIDTH - 4)) + 2,
        .y = (rand() % (MAP_HEIGHT - 4)) + 2,
    };
    map->nest = origin;

    // 3
    int nest_to_borders[4] = {
        Path_manatan_dist(origin, (Coord_i){origin.x, 0}),              // NORTH
        Path_manatan_dist(origin, (Coord_i){MAP_WIDTH - 1, origin.y}),  // EAST
        Path_manatan_dist(origin,
                          (Coord_i){origin.x, MAP_HEIGHT - 1}),  // SOUTH
        Path_manatan_dist(origin, (Coord_i){0, origin.y}),       // WEST
    };

    int rand_nb = rand() % (Utils_sum_arr_i(nest_to_borders, 4) + 1);
    Direction dir = Utils_weighted_select(nest_to_borders, rand_nb, 4);

    if (dir == -1) {
        // Error in weighted_select
        return false;
    }

    // 4
    if (nest_to_borders[dir] <= 2) {
        return false;
    }

    int foward_len = Path_forward_3_4(nest_to_borders[dir]);

    // 5
    Path_apply_path(map, origin, dir, foward_len);
    Error err = Path_add_turn(da, origin, dir, foward_len);
    if (err != CLEAR) {
        Error_print(err, "Path_gen");
        return false;
    }
    total_len += foward_len;

    origin = Utils_coord_from_dir_len(origin, dir, foward_len);

    while (1) {
        Direction new_dir;
        int new_len;

        Path_gen_step(map, origin, dir, &new_dir, &new_len);
        if (new_len <= 2) {
            return (total_turn >= 7 && total_len >= 75);
        }

        foward_len = Path_forward_3_4(new_len);
        Path_apply_path(map, origin, new_dir, foward_len);
        Error err = Path_add_turn(da, origin, new_dir, foward_len);
        if (err != CLEAR) {
            Error_print(err, "Path_gen");
            return false;
        }
        total_len += foward_len;
        total_turn++;

        dir = new_dir;
        origin = Utils_coord_from_dir_len(origin, new_dir, foward_len);
        map->castle = origin;
    }
    return true;
}
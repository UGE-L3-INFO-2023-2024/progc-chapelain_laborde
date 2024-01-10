/**
 * @file Main.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 15-11-2023
 *
 */

#include "Path.h"

#include <stdbool.h>
#include <stdlib.h>

#include "DynamicArray.h"
#include "Map.h"
#include "Utils.h"

/**
 * @brief Return the manatan distance between two Coord_i.
 *
 * @param a Coord_i
 * @param b Coord_i
 * @return int
 */
static int Path_manatan_dist(Coord_i a, Coord_i b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

/**
 * @brief Return the len of the path forward.
 * Use random to go a random number of cell forward.
 * Minimum of distance : 3.
 *
 * @param max max length.
 * @return int
 */
static int Path_forward_3_4(int max) {
    int acc = 0;
    for (int i = 0; i < max; i++) {
        if (rand() % 4) {  // 0 not forward, 1,2,3 forward
            acc++;
        }
    }
    // min dist of 3
    return acc < 3 ? 3 : acc;
}

/**
 * @brief Modify the map to apply the path. ().is_path = true)
 *
 * @param map Map to modify.
 * @param origin point of origin.
 * @param dir Direction of the path.
 * @param len Length of the path.
 */
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
    }
}

/**
 * @brief Add a turn to the DynamicArray.
 *
 * @param da  DynamicArray to modify.
 * @param origin Point of origin.
 * @param dir Direction of the path.
 * @param len Length of the path.
 * @return Error (if realloc failed)
 */
static Error Path_add_turn(DynamicArray* da, Coord_i origin, Direction dir,
                           int len) {
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
    return (Error){DA_add(da, (DynamicArray_Union){.path = coord}, PATH).type,
                   __func__};
}

/**
 * @brief Check if the cell as a path around it.
 *
 * @param map Map to check.
 * @param origin Point of origin.
 * @param ignore Direction to ignore. (in order to not check behind
 * because there is the previous path)
 * @return true if the cell is valid.
 */
static bool Path_manatan_etentu_cell(Map* map, Coord_i origin,
                                     Direction ignore) {
    // too close to the border
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
        // check if we look in the right direction
        if ((ignore == NORTH && neighbour[i][1] > 0) ||
            (ignore == EAST && neighbour[i][0] < 0) ||
            (ignore == SOUTH && neighbour[i][1] < 0) ||
            (ignore == WEST && neighbour[i][0] > 0)) {
            // check if the cell is a path
            if (map->board[origin.y + neighbour[i][1]]
                          [origin.x + neighbour[i][0]]
                              .is_path == true) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Return the max possible length of the path in a direction.
 * (check manatan distance)
 *
 * @param map Map to check.
 * @param start Point of origin.
 * @param dir Direction to check.
 * @return int
 */
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
    // -1 cause last one is an error cell.
    return acc - 1;
}

/**
 * @brief Generate a step of the path.
 *
 * @param map Map to modify.
 * @param coord Point of origin.
 * @param dir Direction of the path.
 * @param new_dir Pointer to the new direction.
 * @param new_len Pointer to the new length.
 */
static void Path_gen_step(Map* map, Coord_i coord, Direction dir,
                          Direction* new_dir, int* new_len) {
    // rotation left and right
    Direction arr_dir[2] = {
        Utils_modulo((dir + 1), 4),
        Utils_modulo((dir - 1), 4),
    };

    // get max dir for each
    int arr_pos[2] = {
        Path_max_dir(map, coord, arr_dir[0]),
        Path_max_dir(map, coord, arr_dir[1]),
    };

    // make a random choice (more len = more chance)
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
    Error err = {CLEAR, __func__};
    int total_len = 0, total_turn = 0;
    // 1
    Map_init_board(map);

    // 2
    Coord_i origin = {
        .x = (rand() % (MAP_WIDTH - 4)) + 2,
        .y = (rand() % (MAP_HEIGHT - 4)) + 2,
    };
    map->nest = origin;
    err.type = Path_add_turn(da, origin, NORTH,
                             0)
                   .type;  //  dir not important because len = 0
    if (err.type) {
        Error_print(err);
        return false;
    }

    // 3
    int nest_to_borders[4] = {
        Path_manatan_dist(origin, (Coord_i){origin.x, 0}),  // NORTH
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
        // nest too close to the border
        return false;
    }

    int foward_len = Path_forward_3_4(nest_to_borders[dir]);

    // 5
    Path_apply_path(map, origin, dir, foward_len);
    err.type = Path_add_turn(da, origin, dir, foward_len).type;
    if (err.type != CLEAR) {
        Error_print(err);
        return false;
    }
    // add to total
    total_len += foward_len;

    // new origin (end of 1st turn)
    origin = Utils_coord_from_dir_len(origin, dir, foward_len);

    while (1) {
        Direction new_dir = NO_DIR;
        int new_len = 0;

        // new dir and new len
        Path_gen_step(map, origin, dir, &new_dir, &new_len);

        if (new_len <= 2) {
            return (total_turn >= 7 && total_len >= 75);
        }

        // new real len
        foward_len = Path_forward_3_4(new_len);

        // apply to map
        Path_apply_path(map, origin, new_dir, foward_len);
        err.type = Path_add_turn(da, origin, new_dir, foward_len).type;
        if (err.type != CLEAR) {
            Error_print(err);
            return false;
        }

        // uptade total
        total_len += foward_len;
        total_turn++;

        // new origin and dir
        dir = new_dir;
        origin = Utils_coord_from_dir_len(origin, new_dir, foward_len);

        // update end path (castle)
        map->castle = origin;
    }
    return true;
}
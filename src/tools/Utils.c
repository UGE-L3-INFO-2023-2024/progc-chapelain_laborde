/**
 * @file Utils.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief Multifunction module
 * (random, modulo, coord, weighted select, angle, direction)
 * @date 16-11-2023
 *
 */

#include "Utils.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/* Modulo works for negative number */
int Utils_modulo(int a, int b) {
    return ((a % b) + b) % b;
}

/* Sum an int array */
int Utils_sum_arr_i(int arr[], int len) {
    int acc = 0;
    for (int i = 0; i < len; i++) {
        acc += arr[i];
    }
    return acc;
}

/* Make a weighted select
https://www.educative.io/answers/what-is-the-weighted-random-selection-algorithm*/
int Utils_weighted_select(int arr[], int val, int len) {
    int acc = 0;
    for (int i = 0; i < len; i++) {
        acc += arr[i];
        if (acc >= val) {
            return i;
        }
    }
    return -1;
}

/* Compute the new coord in the given direction  */
Coord_i Utils_coord_from_dir_len(Coord_i origin, Direction dir, int len) {
    static int Dir_point[4][2] = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
    };
    return (Coord_i){
        .x = origin.x + (Dir_point[dir][0] * len),
        .y = origin.y + (Dir_point[dir][1] * len),
    };
}

/* Is close enough to a coord with margin */
bool Utils_is_in_middle(Coord_f coord_mid, Coord_f coord_other, float margin) {
    return ((coord_other.x > coord_mid.x - margin &&
             coord_other.x < coord_mid.x + margin &&
             coord_other.y > coord_mid.y - margin &&
             coord_other.y < coord_mid.y + margin));
}

Direction Utils_get_dir(Coord_f coord_mid, Coord_f coord_other, float margin) {
    // Direction (Priority: EAST, WEST, SOUTH, NORTH)
    if (coord_other.x < coord_mid.x - margin) {
        return EAST;
    }
    if (coord_other.x > coord_mid.x + margin) {
        return WEST;
    }
    if (coord_other.y < coord_mid.y) {
        return SOUTH;
    }
    if (coord_other.y > coord_mid.y) {
        return NORTH;
    }
    // to close to coord_mid with the margin
    return NO_DIR;
}

/* Convert coord int to float (int.5) */
Coord_f Utils_coord_i_to_f_center(Coord_i coord) {
    return (Coord_f){.x = coord.x + .5, .y = coord.y + .5};
}

/* Convert coord float to int */
Coord_i Utils_coord_f_to_i(Coord_f coord) {
    return (Coord_i){.x = (int)coord.x, .y = (int)coord.y};
}

/* Euclidean distance between 2 point */
double Utils_coord_f_distance(Coord_f from, Coord_f to) {
    return sqrt((to.x - from.x) * (to.x - from.x) +
                (to.y - from.y) * (to.y - from.y));
}

/* Random a number between 0 and 1 */
double Utils_random_0_1() {
    return rand() / (double)RAND_MAX;
}

/* Random an number between a and b */
double Utils_random_uniform(double a, double b) {
    return a + (b - a) * Utils_random_0_1();
}

/* COnvert deg to rad */
double Utils_deg_to_rad(double deg) {
    return deg * HOME_PI / 180;
}

/* Compare coord_i */
bool Coord_i_equal(Coord_i a, Coord_i b) {
    return a.x == b.x && a.y == b.y;
}

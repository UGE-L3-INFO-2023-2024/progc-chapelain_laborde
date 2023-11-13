/**
 * @file Utils.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 11/11/2023
 *
 */

#include "../include/Utils.h"

#include <stdlib.h>

int Utils_modulo(int a, int b) {
    return ((a % b) + b) % b;
}

int Utils_sum_arr_i(int arr[], int len) {
    int acc = 0;
    for (int i = 0; i < len; i++) {
        acc += arr[i];
    }
    return acc;
}

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
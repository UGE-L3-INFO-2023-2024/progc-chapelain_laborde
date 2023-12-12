/**
 * @file Utils.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30/10/2023
 *
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

#define ABS(x) (((x) < 0) ? -(x) : x)

#define FRAMERATE 60

typedef struct {
    int x;
    int y;
} Coord_i;

typedef struct {
    float x;
    float y;
} Coord_f;

typedef enum {
    NO_DIR = -1,
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
} Direction;

int Utils_modulo(int a, int b);
int Utils_sum_arr_i(int arr[], int len);
Coord_i Utils_coord_from_dir_len(Coord_i origin, Direction dir, int len);
int Utils_weighted_select(int arr[], int val, int len);
Coord_f Utils_coord_i_to_f_center(Coord_i coord);
Coord_i Utils_coord_f_to_i(Coord_f coord);
bool Utils_is_in_middle(Coord_f coord_other, Coord_f coord_mid, float margin);
Direction Utils_get_dir(Coord_f coord_mid, Coord_f coord_other, float margin);

#endif  // __UTILS_H__
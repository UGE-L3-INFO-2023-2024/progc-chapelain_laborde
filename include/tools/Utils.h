/**
 * @file Utils.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 30-10-2023
 *
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

#define FRAMERATE 60

#define HOME_PI 3.14159265

/**************/
/* Structures */
/**************/

typedef struct {
    int x;
    int y;
} Coord_i, Point;

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

/*************/
/* Functions */
/*************/

/**
 * @brief Modulo for negative numbers (a%b).
 *
 * @param a int
 * @param b int
 * @return int
 */
int Utils_modulo(int a, int b);

/**
 * @brief Sum all the elements of an array.
 *
 * @param arr int array
 * @param len array length
 * @return int sum
 */
int Utils_sum_arr_i(int arr[], int len);

/**
 * @brief
 *
 * @param arr int array
 * @param val value to select
 * @param len array length
 * @return index where the value <= sum(val) // -1 not obtained
 */
int Utils_weighted_select(int arr[], int val, int len);

/**
 * @brief Return the coordinate of the end of a line of length len
 *
 * @param origin Coord_i origin
 * @param dir Direction
 * @param len wanted length
 * @return Coord_i
 */
Coord_i Utils_coord_from_dir_len(Coord_i origin, Direction dir, int len);

/**
 * @brief Check if coord_other is in the middle of coord_mid with a margin.
 * (check if coord_other is equal coord_mid with a margin)
 *
 * @param coord_other other coordinate
 * @param coord_mid middle coordinate (point of reference)
 * @param margin margin of error (using double)
 * @return if coord_other is equal coord_mid with a margin
 */
bool Utils_is_in_middle(Coord_f coord_other, Coord_f coord_mid, float margin);

/**
 * @brief Return the direction of coord_other from coord_mid with a margin.
 * (margin is used to check if coord_other is equal coord_mid)
 * Direction (Priority: EAST, WEST, SOUTH, NORTH)
 *
 * @param coord_mid middle coordinate (point of reference)
 * @param coord_other other coordinate
 * @param margin margin of error (using double)
 * @return Direction (Priority: EAST, WEST, SOUTH, NORTH)
 * if nothing is found return NO_DIR (to close to coord_mid)
 */
Direction Utils_get_dir(Coord_f coord_mid, Coord_f coord_other, float margin);

/**
 * @brief Convert a Coord_i to a Coord_f in the center of the tile.
 *
 * @param coord Coord_i
 * @return Coord_f centered (0.5, 0.5)
 */
Coord_f Utils_coord_i_to_f_center(Coord_i coord);

/**
 * @brief Convert a Coord_f to a Coord_i. using cast (int).
 *
 * @param coord Coord_f
 * @return Coord_i
 */
Coord_i Utils_coord_f_to_i(Coord_f coord);

/**
 * @brief Return the distance between two Coord_f.
 *
 * @param from origin coord_f
 * @param to destination coord_f
 * @return double distance
 */
double Utils_coord_f_distance(Coord_f from, Coord_f to);

/**
 * @brief Return a random number in the range 0.0 <= N < 1.0.
 *
 * @return double
 */
double Utils_random_0_1();

/**
 * @brief Return a floating point number N such that
 *        a <= N <= b for a <= b and b <= N <= a for b < a.
 *
 * @param a double border
 * @param b double border
 * @return double between a and b
 */
double Utils_random_uniform(double a, double b);

/**
 * @brief Return the radian's angle of a degree's angle.
 *
 * @param deg double degree
 * @return double radian
 */
double Utils_deg_to_rad(double deg);

/**
 * @brief Return if the two Coord_i are equals.
 * (x and y are equal)
 *
 * @param a Coord_i
 * @param b Coord_i
 * @return true if coordinates are equals
 */
bool Coord_i_equal(Coord_i a, Coord_i b);

#endif  // __UTILS_H__